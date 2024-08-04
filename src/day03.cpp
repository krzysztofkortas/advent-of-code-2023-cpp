#include "inputs/day03.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <regex>
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

using Grid = std::vector<std::string>;

struct Pos
{
	int64_t row{};
	int64_t col{};
};

using Positions = std::vector<Pos>;

struct Number
{
	Pos pos;
	std::string value;
};

using Numbers = std::vector<Number>;

Numbers getNumbers(const Grid& grid)
{
	Numbers numbers;
	const std::regex regex{R"(\d+)"};
	for (const auto& [row, line] : grid | vw::enumerate)
	{
		using Iter = std::regex_iterator<decltype(std::cbegin(line))>;
		for (auto it = Iter{line.cbegin(), line.cend(), regex}; it != Iter{}; ++it)
			numbers.emplace_back(Pos{.row = row, .col = it->position()}, it->str());
	}

	return numbers;
}

Positions getSymbolPositions(const Grid& grid, std::predicate<char> auto isSymbol)
{
	Positions positions;
	for (const auto& [row, line] : grid | vw::enumerate)
	{
		for (const auto& [col, c] : line | vw::enumerate)
		{
			if (isSymbol(c))
				positions.emplace_back(row, col);
		}
	}

	return positions;
}

bool isAdjacent(const Number& number, const Pos& symbolPos)
{
	const Pos& numberPos = number.pos;
	return std::abs(symbolPos.row - numberPos.row) <= 1 && symbolPos.col >= numberPos.col - 1
		&& symbolPos.col <= numberPos.col + ssize(number.value);
}

Grid readGrid(std::string_view input)
{
	return input | vw::split('\n') | rng::to<Grid>();
}

int solvePart1(std::string_view input)
{
	const Grid grid = readGrid(input);
	constexpr auto isSymbol = [](char c) { return !"0123456789."sv.contains(c); };
	const Positions symbolPositions = getSymbolPositions(grid, isSymbol);
	const Numbers numbers = getNumbers(grid);
	return Utils::sum(numbers | vw::filter([&symbolPositions](const Number& number) {
		return rng::any_of(symbolPositions, [&number](const Pos& symbolPos) {
			return isAdjacent(number, symbolPos);
		});
	}) | vw::transform([](const Number& number) { return std::stoi(number.value); }));
}

int solvePart2(std::string_view input)
{
	const Grid grid = readGrid(input);
	const Positions asterisks = getSymbolPositions(grid, [](char c) { return c == '*'; });

	return Utils::sum(
		asterisks | vw::transform([numbers = getNumbers(grid)](const Pos& asteriskPos) {
		return numbers | vw::filter([&asteriskPos](const Number& number) {
			return isAdjacent(number, asteriskPos);
		}) | rng::to<Numbers>();
	}) | vw::filter([](const Numbers& adjacentNumbers) { return adjacentNumbers.size() == 2; })
		| vw::transform([](const Numbers& adjacentNumbers) {
		return std::stoi(adjacentNumbers[0].value) * std::stoi(adjacentNumbers[1].value);
	}));
}

TEST(day03, test)
{
	EXPECT_EQ(solvePart1(day03::sample), 4361);
	EXPECT_EQ(solvePart1(day03::input), 530849);

	EXPECT_EQ(solvePart2(day03::sample), 467835);
	EXPECT_EQ(solvePart2(day03::input), 84900879);
}

} // anonymous namespace
