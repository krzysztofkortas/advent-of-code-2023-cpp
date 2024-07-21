#include "inputs/day23.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <ranges>
#include <set>
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

using Grid = std::vector<std::string>;
using Position = std::pair<int64_t, int64_t>;
using Visited = std::set<Position>;
using Direction = std::pair<int64_t, int64_t>;
using Directions = std::unordered_map<char, std::vector<Direction>>;

Position getStartPosition(const Grid& grid)
{
	for (const auto& [colIndex, c] : grid.front() | vw::enumerate)
		if (c == '.')
			return {0z, colIndex};

	std::unreachable();
}

Position getEndPosition(const Grid& grid)
{
	for (const auto& [colIndex, c] : grid.back() | vw::enumerate)
		if (c == '.')
			return {std::ssize(grid) - 1, colIndex};

	std::unreachable();
}

int64_t dfs(
	const Grid& grid,
	const Position& pos,
	const Position& end,
	const Directions& directions,
	Visited& visited)
{
	if (pos == end)
		return 0;

	const int64_t height = std::ssize(grid);
	const int64_t width = std::ssize(grid.front());
	const char c = grid.at(pos.first).at(pos.second);

	int64_t distance = std::numeric_limits<int64_t>::min();
	for (const Direction& dir : directions.at(c))
	{
		const Position newPos{pos.first + dir.first, pos.second + dir.second};
		if (std::min(newPos.first, newPos.second) < 0 || newPos.first > height
			|| newPos.second > width)
		{
			continue;
		}

		if (visited.contains(newPos))
			continue;

		visited.insert(newPos);
		distance = std::max(distance, dfs(grid, newPos, end, directions, visited) + 1);
		visited.erase(newPos);
	}

	return distance;
}

int64_t calculate(std::string_view input, const Directions& directions)
{
	const Grid grid = input | vw::split('\n') | std::ranges::to<Grid>();
	const Position start = getStartPosition(grid);
	const Position end = getEndPosition(grid);

	Visited visited{start};
	return dfs(grid, start, end, directions, visited);
}

int64_t solvePart1(std::string_view input)
{
	const Directions directions{
		{'^', {{-1, 0}}},
		{'v', {{1, 0}}},
		{'<', {{0, -1}}},
		{'>', {{0, 1}}},
		{'.', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
		{'#', {}},
	};

	return calculate(input, directions);
}

int64_t solvePart2(std::string_view input)
{
	const std::vector<Direction> dir{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	const Directions directions{
		{'^', dir},
		{'v', dir},
		{'<', dir},
		{'>', dir},
		{'.', dir},
		{'#', {}},
	};

	return calculate(input, directions);
}

TEST(day23, test)
{
	EXPECT_EQ(solvePart1(day23::sample), 94);
	EXPECT_EQ(solvePart1(day23::input), 2010);

	EXPECT_EQ(solvePart2(day23::sample), 154);
	EXPECT_EQ(solvePart2(day23::input), 621944727930768);
}

} // anonymous namespace
