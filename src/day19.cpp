#include "inputs/day19.h"

#include <cstdint>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

struct Range
{
	int64_t start{};
	int64_t end{};
};

using Rating = std::unordered_map<char, int64_t>;
using Ratings = std::vector<Rating>;
using RatingRange = std::unordered_map<char, Range>;

enum class Operator
{
	less,
	greater,
};

struct Condition
{
	char category{};
	Operator op{};
	int64_t value{};
};

struct Rule
{
	std::optional<Condition> condition;
	std::string consequent;
};

using Rules = std::vector<Rule>;
using Workflows = std::unordered_map<std::string, Rules>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	Workflows workflows;
	Ratings ratings;
	std::string tempWorkflowName;
	Rule tempRule;
	Rules tempRules;
	Condition tempCondition;
	char tempRatingCategory{};
	int64_t tempRatingValue{};
	Rating tempRating;
};

struct Result
{
	Workflows workflows;
	Ratings ratings;
};

struct Separator : pegtl::one<','>
{};

struct NumberRule : pegtl::plus<pegtl::digit>
{};

struct NameRule : pegtl::plus<pegtl::alpha>
{};

struct WorkflowNameRule : NameRule
{};

struct ConsequentRule : NameRule
{};

struct CategoryRule : pegtl::alpha
{};

struct OperatorRule : pegtl::one<'<', '>'>
{};

struct ValueRule : NumberRule
{};

struct ConditionRule : pegtl::seq<CategoryRule, OperatorRule, ValueRule>
{};

struct RuleRule : pegtl::seq<pegtl::opt<ConditionRule, pegtl::one<':'>>, ConsequentRule>
{};

struct WorkflowRule
	: pegtl::
		  seq<WorkflowNameRule, pegtl::one<'{'>, pegtl::list<RuleRule, Separator>, pegtl::one<'}'>>
{};

struct RatingCategoryRule : CategoryRule
{};

struct RatingValueRule : ValueRule
{};

struct RatingItemRule : pegtl::seq<RatingCategoryRule, pegtl::one<'='>, RatingValueRule>
{};

struct RatingRule
	: pegtl::seq<pegtl::one<'{'>, pegtl::list<RatingItemRule, Separator>, pegtl::one<'}'>>
{};

struct Grammar
	: pegtl::must<
		  pegtl::list<WorkflowRule, pegtl::eol>,
		  pegtl::eol,
		  pegtl::eol,
		  pegtl::list<RatingRule, pegtl::eol>,
		  pegtl::eof>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<WorkflowNameRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempWorkflowName = in.string();
	}
};

template<>
struct Action<CategoryRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCondition.category = in.string().at(0);
	}
};

template<>
struct Action<OperatorRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCondition.op = getOperator(in.string().at(0));
	}

	static Operator getOperator(char c)
	{
		switch (c)
		{
			case '<':
				return Operator::less;
			case '>':
				return Operator::greater;
			default:
				std::unreachable();
		}
	}
};

template<>
struct Action<ValueRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCondition.value = std::stoll(in.string());
	}
};

template<>
struct Action<ConditionRule>
{
	static void apply0(State& state)
	{
		state.tempRule.condition = state.tempCondition;
	}
};

template<>
struct Action<ConsequentRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempRule.consequent = in.string();
	}
};

template<>
struct Action<RuleRule>
{
	static void apply0(State& state)
	{
		state.tempRules.push_back(state.tempRule);
		state.tempRule.condition = std::nullopt;
	}
};

template<>
struct Action<WorkflowRule>
{
	static void apply0(State& state)
	{
		state.workflows.emplace(state.tempWorkflowName, state.tempRules);
		state.tempRules.clear();
	}
};

template<>
struct Action<RatingCategoryRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempRatingCategory = in.string().at(0);
	}
};

template<>
struct Action<RatingValueRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempRatingValue = std::stoll(in.string());
	}
};

template<>
struct Action<RatingItemRule>
{
	static void apply0(State& state)
	{
		state.tempRating[state.tempRatingCategory] = state.tempRatingValue;
	}
};

template<>
struct Action<RatingRule>
{
	static void apply0(State& state)
	{
		state.ratings.push_back(state.tempRating);
		state.tempRating.clear();
	}
};

Result parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return Result{.workflows = state.workflows, .ratings = state.ratings};
}

} // namespace Parsing

bool isConditionTrue(const Condition& condition, const Rating& rating)
{
	switch (condition.op)
	{
		case Operator::less:
			return rating.at(condition.category) < condition.value;
		case Operator::greater:
			return rating.at(condition.category) > condition.value;
	}
	std::unreachable();
}

bool isWorkflowAccepted(const Rules& rules, const Workflows& workflows, const Rating& rating)
{
	for (const Rule& rule : rules)
	{
		if (!rule.condition || isConditionTrue(*rule.condition, rating))
		{
			const std::string& consequent = rule.consequent;
			if (consequent == "A")
				return true;
			else if (consequent == "R")
				return false;
			else
				return isWorkflowAccepted(workflows.at(consequent), workflows, rating);
		}
	}

	return true;
}

int64_t solvePart1(std::string_view input)
{
	const auto [workflows, ratings] = Parsing::parse(input);
	const Rules& startWorkflow = workflows.at("in");

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
	return Utils::sum(
		ratings | vw::filter([&](const Rating& rating) {
		return isWorkflowAccepted(startWorkflow, workflows, rating);
	}) | vw::transform(vw::values)
		| vw::join);
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
}

std::pair<RatingRange, RatingRange> crossCondition(
	const Condition& condition, const RatingRange& ratings)
{
	const auto [range1, range2] = [&]() -> std::pair<Range, Range> {
		const auto& [start, end] = ratings.at(condition.category);
		switch (condition.op)
		{
			case Operator::less:
				return {
					Range{.start = start, .end = condition.value},
					Range{.start = condition.value, .end = end}};
			case Operator::greater:
				return {
					Range{.start = condition.value + 1, .end = end},
					Range{.start = start, .end = condition.value + 1}};
		}
		std::unreachable();
	}();

	auto ratings1 = ratings;
	auto ratings2 = ratings;
	ratings1[condition.category] = range1;
	ratings2[condition.category] = range2;

	return {ratings1, ratings2};
}

int64_t countRatings(const RatingRange& ratings)
{
	return Utils::multiply(ratings | vw::values | vw::transform([](const Range& range) {
		return range.end - range.start;
	}));
}

int64_t countAccepted(const Rules& rules, const Workflows& workflows, RatingRange ratings)
{
	auto count = [&workflows](const std::string& consequent, const RatingRange& ratingsToCount) {
		if (consequent == "A")
			return countRatings(ratingsToCount);
		else if (consequent == "R")
			return 0z;
		else
			return countAccepted(workflows.at(consequent), workflows, ratingsToCount);
	};

	return Utils::sum(rules | vw::transform([&](const Rule& rule) {
		if (!rule.condition)
			return count(rule.consequent, ratings);

		const auto [ratings1, ratings2] = crossCondition(*rule.condition, ratings);
		ratings = ratings2;
		return count(rule.consequent, ratings1);
	}));
}

int64_t solvePart2(std::string_view input)
{
	const auto [workflows, _] = Parsing::parse(input);
	const Range range{.start = 1, .end = 4001};
	const RatingRange ratings = vw::zip("xmas", vw::repeat(range, 4)) | rng::to<RatingRange>();

	return countAccepted(workflows.at("in"), workflows, ratings);
}

TEST(day19, test)
{
	EXPECT_EQ(solvePart1(day19::sample), 19114);
	EXPECT_EQ(solvePart1(day19::input), 399284);

	EXPECT_EQ(solvePart2(day19::sample), 167409079868000);
	EXPECT_EQ(solvePart2(day19::input), 121964982771486);
}

} // namespace
