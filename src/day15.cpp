#include "inputs/day15.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <optional>
#include <ranges>
#include <regex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

constexpr auto getHash = [](std::ranges::input_range auto&& range) {
	int64_t result = 0;
	for (auto c : range)
		result = (17 * (result + c)) % 256;

	return result % 256;
};

int64_t solvePart1(std::string_view input)
{
	return std::ranges::fold_left(input | vw::split(',') | vw::transform(getHash), 0z, std::plus{});
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
	}
	std::unreachable();
}

struct Step
{
	std::string label;
	Operation operation;
	std::optional<int64_t> focalLength;
};

using Steps = std::vector<Step>;
using HashMap = std::array<Steps, 256>;

Step makeStep(const std::string& step)
{
	static const std::regex regex(R"((\w+)([-=])(\w*))");
	std::smatch match;
	if (std::regex_match(step, match, regex))
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

		auto it = std::ranges::find(vec, step.label, &Step::label);
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
		| vw::transform([](auto&& step) { return makeStep(step | std::ranges::to<std::string>()); })
		| std::ranges::to<Steps>();
	const HashMap haspMap = getHashMap(steps);

	int64_t result = 0;
	for (const auto& [boxNumber, vec] : haspMap | vw::enumerate)
	{
		for (const auto& [index, step] : vec | vw::enumerate)
			result += (boxNumber + 1) * (index + 1) * step.focalLength.value();
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
