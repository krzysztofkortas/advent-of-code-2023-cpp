#include "inputs/day15.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <optional>
#include <ranges>
#include <regex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

constexpr int multiplier = 17;
constexpr int modulo = 256;

template<typename R, typename V>
concept RangeOf = rng::range<R> && std::same_as<rng::range_value_t<R>, V>;

constexpr auto getHash = [](RangeOf<char> auto&& range) {
	return rng::fold_left(
		range, 0, [](int64_t result, char c) { return (multiplier * (result + c)) % modulo; });
};

int64_t solvePart1(std::string_view input)
{
	return Utils::sum(input | vw::split(',') | vw::transform(getHash));
}

enum class Operation
{
	dash,
	equal,
};

Operation makeOperation(char c)
{
	switch (c)
	{
		case '-':
			return Operation::dash;
		case '=':
			return Operation::equal;
		default:
			std::unreachable();
	}
}

struct Step
{
	std::string label;
	Operation operation{};
	std::optional<int64_t> focalLength;
};

using Steps = std::vector<Step>;
using HashMap = std::array<Steps, modulo>;

Step makeStep(const std::string& step)
{
	static const std::regex regex{R"((\w+)([-=])(\w*))"};
	if (std::smatch match; std::regex_match(step, match, regex))
	{
		return Step{
			.label = match.str(1),
			.operation = makeOperation(match.str(2).at(0)),
			.focalLength =
				match.str(3).empty() ? std::nullopt : std::optional{std::stoll(match.str(3))}};
	}
	std::unreachable();
}

HashMap getHashMap(const Steps& steps)
{
	HashMap hashMap;

	for (const Step& step : steps)
	{
		auto& vec = hashMap.at(getHash(step.label));
		const Operation op = step.operation;

		auto it = rng::find(vec, step.label, &Step::label);
		if (op == Operation::dash)
		{
			if (it != vec.end())
				vec.erase(it);
		}
		else
		{
			if (it != vec.end())
				*it = step;
			else
				vec.push_back(step);
		}
	}

	return hashMap;
}

int64_t solvePart2(std::string_view input)
{
	const Steps steps = input | vw::split(',')
		| vw::transform([](auto&& step) { return makeStep(step | rng::to<std::string>()); })
		| rng::to<Steps>();
	const HashMap hashMap = getHashMap(steps);

	int64_t result = 0;
	for (const auto& [boxNumber, vec] : hashMap | vw::enumerate)
	{
		for (const auto& [index, step] : vec | vw::enumerate)
		{
			assert(step.focalLength);
			result += (boxNumber + 1) * (index + 1) * step.focalLength.value();
		}
	}
	return result;
}

TEST(day15, test)
{
	EXPECT_EQ(solvePart1(day15::sample), 1320);
	EXPECT_EQ(solvePart1(day15::input), 517015);

	EXPECT_EQ(solvePart2(day15::sample), 145);
	EXPECT_EQ(solvePart2(day15::input), 286104);
}

} // anonymous namespace
