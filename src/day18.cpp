#include "inputs/day18.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <ranges>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

using Direction = std::pair<int64_t, int64_t>;
using Position = std::pair<int64_t, int64_t>;
using Positions = std::vector<Position>;

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

struct Instruction
{
	Direction direction;
	int64_t meters{};
};

using Instructions = std::vector<Instruction>;

int64_t shoelaceFormula(const Positions& positions)
{
	return std::abs(
		Utils::sum(positions | vw::pairwise_transform([](const Position& p1, const Position& p2) {
		return (p1.first * p2.second) - (p1.second * p2.first);
	})) / 2);
}

int64_t perimeter(const Instructions& instructions)
{
	return Utils::sum(instructions | vw::transform(&Instruction::meters));
}

int64_t integerPointsFromPickTheorem(int64_t area, int64_t perimeter)
{
	return area + (perimeter / 2) + 1;
}

Positions getPositions(const Instructions& instructions)
{
	Position previousPoint{0, 0};
	Positions positions{previousPoint};
	for (const auto& [dir, meters] : instructions)
	{
		const Position currentPoint{
			previousPoint.first + (meters * dir.first),
			previousPoint.second + (meters * dir.second)};
		positions.push_back(currentPoint);
		previousPoint = currentPoint;
	}

	return positions;
}

int64_t solve(const Instructions& instructions)
{
	return integerPointsFromPickTheorem(
		shoelaceFormula(getPositions(instructions)), perimeter(instructions));
}

int64_t solvePart1(std::string_view input)
{
	const Instructions instructions = input | vw::split('\n') | vw::transform([](auto&& line) {
		const auto v = line | vw::split(' ') | rng::to<std::vector<std::string>>();
		assert(v.size() == 3);
		return Instruction{.direction = getDir(v[0].at(0)), .meters = std::stoll(v[1])};
	}) | rng::to<Instructions>();

	return solve(instructions);
}

int64_t solvePart2(std::string_view input)
{
	const Instructions instructions = input | vw::split('\n')
		| vw::transform(rng::to<std::string>()) | vw::transform([](const std::string& line) {
		static const std::regex regex(R"(\w \d+ \(#(\w{5})(\d)\))");
		if (std::smatch match; std::regex_match(line, match, regex))
		{
			const Direction dir = getDir(match.str(2).at(0));
			const int64_t meters = std::stoll(match.str(1), nullptr, 16);
			return Instruction{.direction = dir, .meters = meters};
		}
		std::unreachable();
	}) | rng::to<Instructions>();

	return solve(instructions);
}

TEST(day18, test)
{
	EXPECT_EQ(solvePart1(day18::sample), 62);
	EXPECT_EQ(solvePart1(day18::input), 70026);

	EXPECT_EQ(solvePart2(day18::sample), 952408144115);
	EXPECT_EQ(solvePart2(day18::input), 68548301037382);
}

} // anonymous namespace
