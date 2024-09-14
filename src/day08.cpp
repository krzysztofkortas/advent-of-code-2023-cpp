#include "inputs/day08.h"

#include <algorithm> // NOLINT(misc-include-cleaner)
#include <cstdint>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

struct Node
{
	std::string name;
	std::string left;
	std::string right;
};

using Nodes = std::map<std::string, Node>;

struct Input
{
	std::string instructions;
	Nodes nodes;
};

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	std::string instructions;
	Nodes nodes;
	Node tempNode;
};

struct StringRule : pegtl::plus<pegtl::alnum>
{};

struct InstructionsRule : StringRule
{};

struct NodeNameRule : StringRule
{};

struct LeftNodeNameRule : StringRule
{};

struct RightNodeNameRule : StringRule
{};

struct NodeRule
	: pegtl::seq<
		  NodeNameRule,
		  pegtl::pad<pegtl::one<'='>, pegtl::blank>,
		  pegtl::one<'('>,
		  LeftNodeNameRule,
		  pegtl::pad<pegtl::one<','>, pegtl::blank>,
		  RightNodeNameRule,
		  pegtl::one<')'>,
		  pegtl::eolf>
{};

struct Grammar
	: pegtl::must<InstructionsRule, pegtl::eol, pegtl::eol, pegtl::until<pegtl::eof, NodeRule>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<InstructionsRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.instructions = in.string();
	}
};

template<>
struct Action<NodeNameRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempNode.name = in.string();
	}
};

template<>
struct Action<LeftNodeNameRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempNode.left = in.string();
	}
};

template<>
struct Action<RightNodeNameRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempNode.right = in.string();
	}
};

template<>
struct Action<NodeRule>
{
	static void apply0(State& state)
	{
		state.nodes.emplace(state.tempNode.name, state.tempNode);
	}
};

Input parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return Input{.instructions = state.instructions, .nodes = state.nodes};
}

} // namespace Parsing

int64_t getSteps(
	const std::string& instructions,
	const Nodes& nodes,
	const std::string& start,
	const std::string& endsWith)
{
	int64_t steps = 0;
	for (std::string current = start; !current.ends_with(endsWith);)
	{
		const Node& node = nodes.at(current);
		current = instructions[steps % ssize(instructions)] == 'L' ? node.left : node.right;
		++steps;
	}
	return steps;
}

int64_t solvePart1(std::string_view input)
{
	const auto [instructions, nodes] = Parsing::parse(input);
	return getSteps(instructions, nodes, "AAA", "ZZZ");
}

int64_t solvePart2(std::string_view input)
{
	const auto [instructions, nodes] = Parsing::parse(input);

	// NOLINTNEXTLINE(misc-include-cleaner)
	return rng::fold_left_first(nodes | vw::values | vw::filter([](const Node& node) {
		return node.name.ends_with('A');
	}) | vw::transform([&](const Node& node) {
		return getSteps(instructions, nodes, node.name, "Z");
	}),
			   [](int64_t x, int64_t y) {
		return std::lcm(x, y);
	}).value_or(0);
}

TEST(day08, test)
{
	EXPECT_EQ(solvePart1(day08::samplePart1), 2);
	EXPECT_EQ(solvePart1(day08::input), 14429);

	EXPECT_EQ(solvePart2(day08::samplePart2), 6);
	EXPECT_EQ(solvePart2(day08::input), 10921547990923);
}

} // anonymous namespace
