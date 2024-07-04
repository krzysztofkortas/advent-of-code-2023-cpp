#include "inputs/day10.h"

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <ranges>
#include <set>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;
using std::size_t;
using std::operator""sv;

struct Position
{
	int64_t row{};
	int64_t col{};
	auto operator<=>(const Position&) const = default;
};

struct Connection
{
	Position begin;
	Position end;
	auto operator<=>(const Connection&) const = default;
};

using Grid = std::vector<std::string>;
using Path = std::vector<Connection>;

// using Position = std::pair<int64_t, int64_t>;
// using Connection = std::pair<Position, Position>;

class Graph
{
public:
	explicit Graph(Grid grid)
		: grid_{std::move(grid)}
	{
		makeConnections();
	}

	Path getCycle(const Position& start)
	{
		Path cycle;
		Position lastPos = start;
		Position currentPos = start;
		do
		{
			bool anyConnected = false;
			for (const auto& direction : {Position{-1, 0}, {0, -1}, {0, 1}, {1, 0}})
			{
				const Position newPos{
					currentPos.row + direction.row, currentPos.col + direction.col};
				if (newPos != lastPos && connections_.contains({currentPos, newPos}))
				{
					cycle.emplace_back(currentPos, newPos);
					lastPos = currentPos;
					currentPos = newPos;
					anyConnected = true;
					break;
				}
			}
			if (!anyConnected)
				return {};

		} while (currentPos != start);

		return cycle;
	}

private:
	void makeConnections()
	{
		for (const auto& [rowIndex, row] : grid_ | vw::enumerate)
		{
			for (const auto& [colIndex, _] : row | vw::enumerate)
			{
				const Position pos{rowIndex, colIndex};
				makeVerticalConnections(pos);
				makeHorizontalConnections(pos);
			}
		}
	}

	void makeVerticalConnections(const Position& pos)
	{
		const Position bottomPos{pos.row + 1, pos.col};
		if (bottomPos.row >= std::ssize(grid_))
			return;
		const char topTile = grid_.at(pos.row).at(pos.col);
		const char bottomTile = grid_.at(bottomPos.row).at(bottomPos.col);
		if ("|7F"sv.contains(topTile) && "|LJ"sv.contains(bottomTile))
		{
			connections_.emplace(pos, bottomPos);
			connections_.emplace(bottomPos, pos);
		}
	}

	void makeHorizontalConnections(const Position& pos)
	{
		const Position rightPos{pos.row, pos.col + 1};
		if (rightPos.col >= std::ssize(grid_.at(0)))
			return;
		const char leftTile = grid_.at(pos.row).at(pos.col);
		const char rightTile = grid_.at(rightPos.row).at(rightPos.col);
		if ("-LF"sv.contains(leftTile) && "-J7"sv.contains(rightTile))
		{
			connections_.emplace(pos, rightPos);
			connections_.emplace(rightPos, pos);
		}
	}

	Grid grid_;
	std::set<Connection> connections_;
};

Position getStartingPosition(const Grid& grid)
{
	for (const auto& [rowIndex, row] : grid | vw::enumerate)
	{
		for (const auto& [colIndex, c] : row | vw::enumerate)
		{
			if (c == 'S')
				return {rowIndex, colIndex};
		}
	}

	std::unreachable();
}

std::pair<Path, Grid> getMaxCycle(std::string_view input)
{
	Grid grid = input | vw::split('\n') | std::ranges::to<Grid>();
	const Position s = getStartingPosition(grid);
	return std::ranges::max(
		"|-LJ7F"sv | vw::transform([&](char pipe) {
			grid.at(s.row).at(s.col) = pipe;
			return std::make_pair(Graph{grid}.getCycle(s), grid);
		}),
		std::less{},
		[](const auto& p) { return p.first.size(); });
}

int64_t solvePart1(std::string_view input)
{
	return (getMaxCycle(input).first.size() + 1) / 2;
}

bool isInsideCycle(const Position& pos, const Grid& grid, const std::set<Connection>& cycle)
{
	if (pos.row == 0 || pos.row + 1 == std::ssize(grid))
		return false;

	int64_t intersections = 0;

	for (int64_t y : vw::iota(pos.col + 1, std::ssize(grid[0])))
	{
		const Connection con = {{pos.row, y}, {pos.row - 1, y}};
		const Connection conRev = {con.end, con.begin};

		if (cycle.contains(con) || cycle.contains(conRev))
			++intersections;
	}

	return intersections % 2 == 1;
}

bool isOnCycle(const Position& pos, const Path& cycle)
{
	return std::ranges::any_of(
		cycle, [&](const Connection& c) { return c.begin == pos || c.end == pos; });
}

int64_t solvePart2(std::string_view input)
{
	const auto [maxCycle, grid] = getMaxCycle(input);
	const std::set<Connection> maxCycleSet(maxCycle.cbegin(), maxCycle.cend());
	int64_t enclosedTiles = 0;

	for (const auto& [rowIndex, row] : grid | vw::enumerate)
	{
		for (const auto& [colIndex, _] : row | vw::enumerate)
		{
			const Position pos{rowIndex, colIndex};
			if (!isOnCycle(pos, maxCycle) && isInsideCycle(pos, grid, maxCycleSet))
				++enclosedTiles;
		}
	}

	return enclosedTiles;
}

TEST(day10, test)
{
	EXPECT_EQ(solvePart1(day10::sample1), 4);
	EXPECT_EQ(solvePart1(day10::sample2), 4);
	EXPECT_EQ(solvePart1(day10::sample3), 8);
	EXPECT_EQ(solvePart1(day10::sample4), 8);
	EXPECT_EQ(solvePart1(day10::input), 7107);

	EXPECT_EQ(solvePart2(day10::sample1Part2), 4);
	EXPECT_EQ(solvePart2(day10::sample2Part2), 4);
	EXPECT_EQ(solvePart2(day10::sample3Part2), 8);
	EXPECT_EQ(solvePart2(day10::sample4Part2), 10);
	EXPECT_EQ(solvePart2(day10::input), 281);
}

} // anonymous namespace
