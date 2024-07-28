#include "inputs/day11.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

using Grid = std::vector<std::string>;

struct Galaxy
{
	int64_t row{};
	int64_t col{};
};

using Galaxies = std::vector<Galaxy>;

std::vector<int64_t> getEmptyRows(const Grid& grid)
{
	return grid | vw::enumerate | vw::filter([](const auto& p) {
		const auto& [index, line] = p;
		return !line.contains('#');
	}) | vw::keys
		| rng::to<std::vector>();
}

std::vector<int64_t> getEmptyColumns(const Grid& grid)
{
	return vw::iota(0z, ssize(grid.at(0))) | vw::filter([&](std::size_t col) {
		return !rng::any_of(grid, [col](const std::string& line) { return line.at(col) == '#'; });
	}) | rng::to<std::vector>();
}

Galaxies getGalaxies(const Grid& grid)
{
	Galaxies result;
	for (const auto& [row, line] : grid | vw::enumerate)
	{
		for (const auto& [col, c] : line | vw::enumerate)
		{
			if (c == '#')
				result.emplace_back(row, col);
		}
	}

	return result;
}

int64_t getDistance(
	int64_t lhs, int64_t rhs, const std::vector<int64_t>& empty, int64_t emptyMultiplier)
{
	const auto min = std::min(lhs, rhs);
	const auto max = std::max(lhs, rhs);

	return max - min + (emptyMultiplier - 1) * rng::count_if(empty, [&](int64_t x) {
		return x >= min && x <= max;
	});
}

int64_t calculate(std::string_view input, int64_t emptyMultiplier)
{
	const Grid grid = input | vw::split('\n') | rng::to<Grid>();

	const auto galaxies = getGalaxies(grid);
	const auto emptyRows = getEmptyRows(grid);
	const auto emptyColumns = getEmptyColumns(grid);

	int64_t result = 0;
	for (const auto& [leftGalaxy, rightGalaxy] : vw::cartesian_product(galaxies, galaxies))
	{
		result += getDistance(leftGalaxy.row, rightGalaxy.row, emptyRows, emptyMultiplier);
		result += getDistance(leftGalaxy.col, rightGalaxy.col, emptyColumns, emptyMultiplier);
	}

	return result / 2;
}

int64_t solvePart1(std::string_view input)
{
	return calculate(input, 2);
}

int64_t solvePart2(std::string_view input)
{
	constexpr int emptyMultiplier = 1000000;
	return calculate(input, emptyMultiplier);
}

TEST(day11, test)
{
	EXPECT_EQ(solvePart1(day11::sample), 374);
	EXPECT_EQ(solvePart1(day11::input), 9795148);

	EXPECT_EQ(solvePart2(day11::sample), 82000210);
	EXPECT_EQ(solvePart2(day11::input), 650672493820);
}

} // anonymous namespace
