#include "inputs/day23.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <map>
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

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

using Grid = std::vector<std::string>;
using Position = std::pair<int64_t, int64_t>;
using Visited = std::set<Position>;
using Direction = std::pair<int64_t, int64_t>;
using Directions = std::unordered_map<char, std::vector<Direction>>;

bool isValid(const Position& pos, int64_t width, int64_t height)
{
	return pos.first >= 0 && pos.first < height && pos.second >= 0 && pos.second < width;
}

class Graph
{
public:
	Graph(const Grid& grid, const Directions& directions)
	{
		makeGraph(grid, directions);
		compressGraph();
	}

	[[nodiscard]] int64_t getLongestPath(const Position& startPos, const Position& endPos) const
	{
		Visited visited;
		return getLongestPath(startPos, endPos, visited);
	}

private:
	void makeGraph(const Grid& grid, const Directions& directions)
	{
		const int64_t height = ssize(grid);
		const int64_t width = ssize(grid.front());

		for (const auto& [rowIndex, row] : grid | vw::enumerate)
		{
			for (const auto& [colIndex, c] : row | vw::enumerate)
			{
				for (const Position pos{rowIndex, colIndex};
					 const Direction& dir : directions.at(c))
				{
					const Position newPos{pos.first + dir.first, pos.second + dir.second};
					if (isValid(newPos, width, height)
						&& grid.at(newPos.first).at(newPos.second) != '#')
					{
						graph_[pos].emplace_back(newPos, 1);
					}
				}
			}
		}
	}

	void compressGraph()
	{
		constexpr auto hasTwoNeighbors = [](const auto& item) { return ssize(item.second) == 2; };
		while (rng::any_of(graph_, hasTwoNeighbors))
		{
			const auto& [pos, neighbours] = *rng::find_if(graph_, hasTwoNeighbors);
			const auto& [pos1, dist1] = neighbours.at(0);
			const auto& [pos2, dist2] = neighbours.at(1);

			erase(graph_[pos1], std::pair{pos, dist1});
			erase(graph_[pos2], std::pair{pos, dist2});
			graph_[pos1].emplace_back(pos2, dist1 + dist2);
			graph_[pos2].emplace_back(pos1, dist1 + dist2);
			graph_.erase(pos);
		}
	}

	int64_t getLongestPath(const Position& startPos, const Position& endPos, Visited& visited) const
	{
		if (startPos == endPos)
			return 0;

		visited.insert(startPos);

		auto distance = std::numeric_limits<int64_t>::min();
		for (const auto& [newPos, dist] : graph_.at(startPos))
		{
			if (!visited.contains(newPos))
				distance = std::max(distance, getLongestPath(newPos, endPos, visited) + dist);
		}

		visited.erase(startPos);
		return distance;
	}

	std::map<Position, std::vector<std::pair<Position, int64_t>>> graph_;
};

int64_t calculate(std::string_view input, const Directions& directions)

{
	const Grid grid = input | vw::split('\n') | rng::to<Grid>();
	const Position start{0, grid.front().find('.')};
	const Position end{ssize(grid) - 1, grid.back().find('.')};

	return Graph(grid, directions).getLongestPath(start, end);
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
	EXPECT_EQ(solvePart2(day23::input), 6318);
}

} // anonymous namespace
