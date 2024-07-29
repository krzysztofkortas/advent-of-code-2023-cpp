#include "inputs/day14.h"

#include <algorithm>
#include <cstdint>
#include <map>
#include <ranges>
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

using Grid = std::vector<std::string>;

int64_t calculateLoad(const Grid& grid)
{
	return Utils::sum(grid | vw::transform([](const std::string& line) {
		return line | vw::enumerate
			| vw::filter([](const auto& p) { return std::get<1>(p) == 'O'; })
			| vw::transform([&line](const auto& p) { return ssize(line) - std::get<0>(p); });
	}) | vw::join);
}

Grid moveRocks(const Grid& grid)
{
	return grid | vw::transform([](const std::string& line) {
		std::string resultLine = line;
		for (int64_t freeSlot = 0; const auto& [index, c] : line | vw::enumerate)
		{
			if (c == 'O')
				std::swap(resultLine[freeSlot++], resultLine[index]);
			else if (c == '#')
				freeSlot = index + 1;
		}
		return resultLine;
	}) | rng::to<Grid>();
}

Grid rotateRight(const Grid& grid)
{
	return vw::iota(0z, ssize(grid.at(0))) | vw::transform([&grid](int64_t col) {
		return vw::iota(0z, ssize(grid)) | vw::reverse
			| vw::transform([&grid, col](int64_t row) { return grid[row][col]; });
	}) | rng::to<Grid>();
}

Grid rotateLeft(const Grid& grid)
{
	return rotateRight(rotateRight(rotateRight(grid)));
}

Grid readGrid(std::string_view input)
{
	return input | vw::split('\n') | rng::to<Grid>();
}

int64_t solvePart1(std::string_view input)
{
	Grid grid = readGrid(input);
	grid = moveRocks(rotateLeft(grid));
	return calculateLoad(grid);
}

Grid makeStep(Grid grid)
{
	grid = moveRocks(rotateLeft(grid));
	grid = moveRocks(rotateRight(grid));
	grid = moveRocks(rotateRight(grid));
	grid = moveRocks(rotateRight(grid));
	grid = rotateRight(rotateRight(grid));

	return grid;
}

int64_t solvePart2(std::string_view input)
{
	Grid grid = readGrid(input);
	std::map<Grid, int64_t> visited;
	std::vector<int64_t> results;
	constexpr int64_t numberOfSteps = 1000000000;

	for (const int64_t i : vw::iota(0, numberOfSteps + 1))
	{
		if (const auto it = visited.find(grid); it != visited.end())
		{
			const int64_t cycleLen = i - it->second;
			const int64_t resIndex = it->second + ((numberOfSteps - i) % cycleLen);
			return results.at(resIndex);
		}
		else
		{
			visited.emplace(grid, i);
			results.push_back(calculateLoad(rotateLeft(grid)));
			grid = makeStep(grid);
		}
	}

	return results.back();
}

TEST(day14, test)
{
	EXPECT_EQ(solvePart1(day14::sample), 136);
	EXPECT_EQ(solvePart1(day14::input), 113424);

	EXPECT_EQ(solvePart2(day14::sample), 64);
	EXPECT_EQ(solvePart2(day14::input), 96003);
}

} // anonymous namespace
