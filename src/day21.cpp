#include "inputs/day21.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
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
using Direction = std::pair<int64_t, int64_t>;

Position getStartPosition(const Grid& grid)
{
	for (const auto& [rowIndex, row] : grid | vw::enumerate)
		for (const auto& [colIndex, c] : row | vw::enumerate)
			if (c == 'S')
				return {rowIndex, colIndex};

	std::unreachable();
}

int64_t solvePart1(std::string_view input, int64_t steps)
{
	const Grid grid = input | vw::split('\n') | std::ranges::to<Grid>();
	const int64_t height = std::ssize(grid);
	const int64_t width = std::ssize(grid.front());

	const Position start = getStartPosition(grid);
	std::set<Position> plots{start};

	for (int i = 0; i < steps; ++i)
	{
		std::set<Position> newPlots;
		for (const auto& plot : plots)
		{
			for (const auto& dir : {Direction{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
			{
				const Position newPlot{plot.first + dir.first, plot.second + dir.second};
				if (std::min(newPlot.first, newPlot.second) < 0 || newPlot.first > height
					|| newPlot.second > width)
				{
					continue;
				}
				const char c = grid.at(newPlot.first).at(newPlot.second);
				if (c == '.' || c == 'S')
					newPlots.insert(newPlot);
			}
		}
		plots = newPlots;
	}

	return std::ssize(plots);
}

int64_t getEuclideanRemainder(int64_t val, int64_t modulo)
{
	return (val % modulo + modulo) % modulo;
}

int64_t solvePart2(std::string_view input, int64_t steps)
{
	const Grid grid = input | vw::split('\n') | std::ranges::to<Grid>();
	const int64_t height = std::ssize(grid);
	const int64_t width = std::ssize(grid.front());
	assert(height == width);

	const Position start = getStartPosition(grid);
	std::set<Position> visited{start};
	std::set<Position> plots{start};
	int64_t distance = 0;
	std::vector<int64_t> answers(steps + 1, 0);
	answers[0] = 1;

	const int64_t modulo = steps % width;
	const int64_t precalculatedSteps = std::min(steps, (modulo + (3 * width)));

	while (distance < precalculatedSteps)
	{
		std::set<Position> newPlots;
		for (const auto& plot : plots)
		{
			for (const auto& dir : {Direction{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
			{
				const Position newPlot{plot.first + dir.first, plot.second + dir.second};
				if (visited.contains(newPlot))
					continue;
				const char c = grid.at(getEuclideanRemainder(newPlot.first, height))
								   .at(getEuclideanRemainder(newPlot.second, width));
				if (c == '.' || c == 'S')
				{
					newPlots.insert(newPlot);
					visited.insert(newPlot);
				}
			}
		}
		plots = newPlots;
		++distance;
		answers[distance] = std::ssize(plots);
		if (distance >= 2)
			answers[distance] += answers[distance - 2];
	}

	if (steps <= precalculatedSteps)
		return answers[steps];

	answers = {answers[modulo], answers[modulo + width], answers[modulo + (2 * width)]};

	int64_t answersSize = 3;
	const int64_t neededSteps = (steps + width - 1) / width;
	const int64_t diff = answers[2] - (2 * answers[1]) + answers[0];

	while (answersSize < neededSteps)
	{
		answers.push_back(diff + (2 * answers[answersSize - 1]) - answers[answersSize - 2]);
		++answersSize;
	}

	return answers.back();
}

TEST(day21, test)
{
	EXPECT_EQ(solvePart1(day21::sample, 1), 2);
	EXPECT_EQ(solvePart1(day21::sample, 2), 4);
	EXPECT_EQ(solvePart1(day21::sample, 3), 6);
	EXPECT_EQ(solvePart1(day21::sample, 6), 16);
	EXPECT_EQ(solvePart1(day21::input, 64), 3762);

	EXPECT_EQ(solvePart2(day21::sample, 6), 16);
	EXPECT_EQ(solvePart2(day21::sample, 10), 50);
	EXPECT_EQ(solvePart2(day21::input, 26501365), 621944727930768);
}

} // anonymous namespace
