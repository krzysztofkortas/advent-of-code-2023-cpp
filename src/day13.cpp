#include "inputs/day13.h"

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <optional>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;
using std::operator""sv;

using Pattern = std::vector<std::string>;

int64_t getHorizontalReflectionImpl(
	const Pattern& pattern, int multiplier, std::optional<int64_t> ignore = std::nullopt)
{
	for (const auto row : vw::iota(1z, ssize(pattern)))
	{
		const auto size = std::min(row, ssize(pattern) - row);
		const auto upper = std::span{pattern}.subspan(row - size, size);
		const auto bottom = std::span{pattern}.subspan(row, size);
		if (rng::equal(upper, bottom | vw::reverse) && multiplier * row != ignore)
			return multiplier * row;
	}

	return 0;
}

int64_t getHorizontalReflection(
	const Pattern& pattern, std::optional<int64_t> ignore = std::nullopt)
{
	constexpr int multiplier = 100;
	return getHorizontalReflectionImpl(pattern, multiplier, ignore);
}

int64_t getVerticalReflection(const Pattern& pattern, std::optional<int64_t> ignore = std::nullopt)
{
	const auto transposed = vw::iota(0z, ssize(pattern.at(0))) | vw::transform([&](int64_t col) {
		return pattern | vw::transform([col](const std::string& line) { return line.at(col); });
	}) | rng::to<Pattern>();

	return getHorizontalReflectionImpl(transposed, 1, ignore);
}

int64_t solve(std::string_view input, std::invocable<Pattern> auto getReflection)
{
	return Utils::sum(input | vw::split("\n\n"sv) | vw::transform([&](auto&& pattern) {
		return getReflection(pattern | vw::split('\n') | rng::to<Pattern>());
	}));
}

int64_t getReflection(const Pattern& pattern)
{
	return getHorizontalReflection(pattern) + getVerticalReflection(pattern);
}

int64_t solvePart1(std::string_view input)
{
	return solve(input, &getReflection);
}

int64_t getReflectionPart2(const Pattern& pattern)
{
	const auto oldResult = getReflection(pattern);
	auto patternCopy = pattern;

	for (const auto& [rowIndex, row] : pattern | vw::enumerate)
	{
		for (const auto& [colIndex, c] : row | vw::enumerate)
		{
			patternCopy[rowIndex][colIndex] = (c == '.' ? '#' : '.');
			if (const int64_t horizontalResult = getHorizontalReflection(patternCopy, oldResult))
				return horizontalResult;
			if (const int64_t verticalResult = getVerticalReflection(patternCopy, oldResult))
				return verticalResult;

			patternCopy[rowIndex][colIndex] = c;
		}
	}

	return 0;
}

int64_t solvePart2(std::string_view input)
{
	return solve(input, &getReflectionPart2);
}

TEST(day13, test)
{
	EXPECT_EQ(solvePart1(day13::sample), 405);
	EXPECT_EQ(solvePart1(day13::input), 31265);

	EXPECT_EQ(solvePart2(day13::sample), 400);
	EXPECT_EQ(solvePart2(day13::input), 39359);
}

} // anonymous namespace
