#include "inputs/day18.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <optional>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

using Direction = std::pair<int64_t, int64_t>;
using Position = std::pair<int64_t, int64_t>;

Direction getDir(char c)
{
	static const std::unordered_map<char, Direction> directions{
		{'R', {1, 0}},
		{'L', {-1, 0}},
		{'D', {0, -1}},
		{'U', {0, 1}},
		{'0', {1, 0}},
		{'2', {-1, 0}},
		{'1', {0, -1}},
		{'3', {0, 1}},
	};

	return directions.at(c);
}

int64_t solvePart1(std::string_view input)
{
	Position previousPoint{0, 0};
	int64_t circuit = 1;
	int64_t area = 0;

	for (auto&& line : input | vw::split('\n'))
	{
		const auto v = line | vw::split(' ') | std::ranges::to<std::vector<std::string>>();
		assert(v.size() == 3);
		const Direction dir = getDir(v[0].front());
		const int64_t meters = std::stoll(v[1]);
		circuit += meters;
		const Position currentPoint{
			previousPoint.first + meters * dir.first, previousPoint.second + meters * dir.second};
		area +=
			previousPoint.first * currentPoint.second - previousPoint.second * currentPoint.first;

		previousPoint = currentPoint;
	}

	return (std::abs(area) + circuit + 2) / 2;
}

int64_t solvePart2(std::string_view input)
{
	Position previousPoint{0, 0};
	int64_t circuit = 1;
	int64_t area = 0;

	for (auto&& line : input | vw::split('\n'))
	{
		const std::string code =
			(line | vw::split(' ') | std::ranges::to<std::vector<std::string>>()).at(2);

		const Direction dir = getDir(code.at(std::ssize(code) - 2));
		const std::string encodedMeters = code.substr(2, std::ssize(code) - 4);
		const int64_t meters = std::stoll(encodedMeters, nullptr, 16);
		circuit += meters;
		const Position currentPoint{
			previousPoint.first + meters * dir.first, previousPoint.second + meters * dir.second};
		area +=
			previousPoint.first * currentPoint.second - previousPoint.second * currentPoint.first;

		previousPoint = currentPoint;
	}

	return (std::abs(area) + circuit + 2) / 2;
}

TEST(day18, test)
{
	EXPECT_EQ(solvePart1(day18::sample), 62);
	EXPECT_EQ(solvePart1(day18::input), 70026);

	EXPECT_EQ(solvePart2(day18::sample), 952408144115);
	EXPECT_EQ(solvePart2(day18::input), 68548301037382);
}

} // anonymous namespace
