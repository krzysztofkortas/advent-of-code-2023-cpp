#include "inputs/day10.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;
using std::operator""sv;

struct Position
{
	int64_t row{};
	int64_t col{};
	friend auto operator<=>(const Position&, const Position&) = default;
};

struct Connection
{
	Position begin;
	Position end;
	friend auto operator<=>(const Connection&, const Connection&) = default;
};

using Grid = std::vector<std::string>;
using Path = std::set<Connection>;

constexpr auto directions = {
	Position{.row = -1, .col = 0},
	{.row = 0, .col = -1},
	{.row = 0, .col = 1},
	{.row = 1, .col = 0}};

class Graph
{
public:
	explicit Graph(Grid grid)
		: grid_{std::move(grid)}
		, width_{ssize(grid_.at(0))}
		, height_{ssize(grid_)}
		, connections_{makeConnections()}
	{
	}

	Path getCycle(const Position& start)
	{
		Path cycle;
		Position previousPos = start;
		Position currentPos = start;
		while (currentPos != start || cycle.empty())
		{
			bool anyConnected = false;
			for (const auto& direction : directions)
			{
				const Position newPos{
					.row = currentPos.row + direction.row, .col = currentPos.col + direction.col};
				const Connection connection{.begin = currentPos, .end = newPos};
				if (newPos != previousPos && connections_.contains(connection))
				{
					cycle.insert(connection);
					previousPos = currentPos;
					currentPos = newPos;
					anyConnected = true;
					break;
				}
			}
			if (!anyConnected)
				return {};
		}

		return cycle;
	}

private:
	[[nodiscard]] std::set<Connection> makeConnections() const
	{
		std::set<Connection> connections;
		for (const auto [rowIndex, colIndex] :
			 vw::cartesian_product(vw::iota(0z, height_), vw::iota(0z, width_)))
		{
			const Position pos{.row = rowIndex, .col = colIndex};
			makeVerticalConnections(connections, pos);
			makeHorizontalConnections(connections, pos);
		}

		return connections;
	}

	void makeVerticalConnections(std::set<Connection>& connections, const Position& pos) const
	{
		const Position bottomPos{.row = pos.row + 1, .col = pos.col};
		if (bottomPos.row >= height_)
			return;
		const char topTile = grid_.at(pos.row).at(pos.col);
		const char bottomTile = grid_.at(bottomPos.row).at(bottomPos.col);
		if ("|7F"sv.contains(topTile) && "|LJ"sv.contains(bottomTile))
		{
			connections.emplace(pos, bottomPos);
			connections.emplace(bottomPos, pos);
		}
	}

	void makeHorizontalConnections(std::set<Connection>& connections, const Position& pos) const
	{
		const Position rightPos{.row = pos.row, .col = pos.col + 1};
		if (rightPos.col >= width_)
			return;
		const char leftTile = grid_.at(pos.row).at(pos.col);
		const char rightTile = grid_.at(rightPos.row).at(rightPos.col);
		if ("-LF"sv.contains(leftTile) && "-J7"sv.contains(rightTile))
		{
			connections.emplace(pos, rightPos);
			connections.emplace(rightPos, pos);
		}
	}

	Grid grid_;
	int64_t width_;
	int64_t height_;
	std::set<Connection> connections_;
};

Position getStartingPosition(const Grid& grid)
{
	for (const auto& [rowIndex, row] : grid | vw::enumerate)
	{
		if (auto pos = row.find('S'); pos != std::string::npos)
			return {.row = rowIndex, .col = static_cast<int64_t>(pos)};
	}

	std::unreachable();
}

Grid getGrid(std::string_view input)
{
	return input | vw::split('\n') | rng::to<Grid>();
}

Path getMaxCycle(Grid grid)
{
	const Position s = getStartingPosition(grid);
	return rng::max(
		"|-LJ7F"sv | vw::transform([&](char pipe) {
		grid.at(s.row).at(s.col) = pipe;
		return Graph{grid}.getCycle(s);
	}),
		{},
		&Path::size);
}

int64_t solvePart1(std::string_view input)
{
	return (ssize(getMaxCycle(getGrid(input))) + 1) / 2;
}

bool isInsideCycle(const Position& pos, const std::set<Connection>& cycle, int64_t gridWidth)
{
	const auto intersections = rng::count_if(vw::iota(pos.col + 1, gridWidth), [&](int64_t col) {
		const Connection conn{
			.begin = Position{.row = pos.row, .col = col},
			.end = Position{.row = pos.row - 1, .col = col}};
		const Connection connRev{.begin = conn.end, .end = conn.begin};
		return cycle.contains(conn) || cycle.contains(connRev);
	});

	return intersections % 2 == 1;
}

int64_t solvePart2(std::string_view input)
{
	const Grid grid = getGrid(input);
	const int64_t gridWidth = ssize(grid.at(0));
	const int64_t gridHeight = ssize(grid);
	const Path maxCycle = getMaxCycle(grid);
	const std::set<Connection> cycleConnections(maxCycle.cbegin(), maxCycle.cend());
	const std::set<Position> cyclePositions =
		maxCycle | vw::transform(&Connection::begin) | rng::to<std::set>();

	return rng::count_if(
		vw::cartesian_product(vw::iota(0, gridHeight), vw::iota(0, gridWidth)), [&](const auto& p) {
		const auto& [rowIndex, colIndex] = p;
		const Position pos{.row = rowIndex, .col = colIndex};
		return !cyclePositions.contains(pos) && isInsideCycle(pos, cycleConnections, gridWidth);
	});
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
