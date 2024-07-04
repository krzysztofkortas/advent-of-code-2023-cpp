#include "inputs/day03.h"

#include <algorithm>
#include <cctype>
#include <concepts>
#include <cstddef>
#include <functional>
#include <ranges>
#include <regex>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

struct Pos
{
	std::int64_t row{};
	std::int64_t col{};
};

using Positions = std::vector<Pos>;

struct Number
{
	Pos pos;
	std::string value;
};

using Numbers = std::vector<Number>;

Numbers getNumbers(std::string_view input)
{
	Numbers numbers;
	const std::regex regex(R"(\d+)");
	for (auto&& [row, line] : input | vw::split('\n') | vw::enumerate)
	{
		using Iter = std::regex_iterator<decltype(std::cbegin(line))>;
		for (auto it = Iter{line.cbegin(), line.cend(), regex}; it != Iter{}; ++it)
		{
			numbers.push_back({.pos = {.row = row, .col = it->position()}, .value = it->str()});
		}
	}

	return numbers;
}

Positions getSymbolPositions(std::string_view input, std::predicate<char> auto isSymbol)
{
	Positions positions;
	for (auto&& [row, line] : input | vw::split('\n') | vw::enumerate)
	{
		for (auto&& [col, c] : line | vw::enumerate)
		{
			if (isSymbol(c))
				positions.push_back({.row = row, .col = col});
		}
	}

	return positions;
}

bool isAdjacent(const Number& number, const Pos& symbolPos)
{
	const Pos& numberPos = number.pos;
	return std::llabs(symbolPos.row - numberPos.row) <= 1 && symbolPos.col + 1 >= numberPos.col
		&& symbolPos.col <= numberPos.col + ssize(number.value);
}

int solvePart1(std::string_view input)
{
	const Numbers numbers = getNumbers(input);
	constexpr auto isSymbol = [](unsigned char c) { return !std::isdigit(c) && c != '.'; };
	const Positions symbolPositions = getSymbolPositions(input, isSymbol);
	return std::ranges::fold_left(
		numbers | vw::filter([&symbolPositions](const Number& number) {
			return std::ranges::any_of(symbolPositions, [&number](const Pos& symbolPos) {
				return isAdjacent(number, symbolPos);
			});
		}) | vw::transform([](const Number& number) { return std::stoi(number.value); }),
		0,
		std::plus<>{});
}

int solvePart2(std::string_view input)
{
	const Numbers numbers = getNumbers(input);
	const Positions asterisks = getSymbolPositions(input, [](char c) { return c == '*'; });

	return std::ranges::fold_left(
		asterisks | vw::transform([&numbers](const Pos& asteriskPos) {
			return numbers | vw::filter([&asteriskPos](const Number& number) {
					   return isAdjacent(number, asteriskPos);
				   })
				| std::ranges::to<Numbers>();
		}) | vw::filter([](const Numbers& adjacentNumbers) { return adjacentNumbers.size() == 2; })
			| vw::transform([](const Numbers& adjacentNumbers) {
				  return std::stoi(adjacentNumbers[0].value) * std::stoi(adjacentNumbers[1].value);
			  }),
		0,
		std::plus<>{});
}

TEST(day03, test)
{
	EXPECT_EQ(solvePart1(day03::sample), 4361);
	EXPECT_EQ(solvePart1(day03::input), 530849);

	EXPECT_EQ(solvePart2(day03::sample), 467835);
	EXPECT_EQ(solvePart2(day03::input), 84900879);
}

} // anonymous namespace
