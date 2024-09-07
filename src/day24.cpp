#include "inputs/day24.h"

#include <cstdint>
#include <format>
#include <iterator>
#include <optional>
#include <ranges>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <z3++.h>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

struct Position
{
	int64_t x{};
	int64_t y{};
	int64_t z{};
};

struct Velocity
{
	int64_t x{};
	int64_t y{};
	int64_t z{};
};

struct Hailstone
{
	Position position;
	Velocity velocity;
};

using Hailstones = std::vector<Hailstone>;

Hailstones parseInput(std::string_view input)
{
	return input | vw::split('\n') | vw::transform(rng::to<std::string>())
		| vw::transform([](const std::string& line) {
		static const std::regex regex{
			R"((\d+),\s*(\d+),\s*(\d+)\s*@\s*(-?\d+),\s*(-?\d+),\s*(-?\d+))"};
		if (std::smatch match; std::regex_match(line, match, regex))
		{
			const Position position{
				.x = std::stoll(match.str(1)),
				.y = std::stoll(match.str(2)),
				.z = std::stoll(match.str(3))};
			const Velocity velocity{
				.x = std::stoll(match.str(4)),
				.y = std::stoll(match.str(5)),
				.z = std::stoll(match.str(6))};
			return Hailstone{.position = position, .velocity = velocity};
		}
		std::unreachable();
	}) | rng::to<Hailstones>();
}

std::optional<Position> getIntersecion2D(const Hailstone& lhs, const Hailstone& rhs)
{
	const auto lhsSlope = static_cast<long double>(lhs.velocity.y) / lhs.velocity.x;
	const auto rhsSlope = static_cast<long double>(rhs.velocity.y) / rhs.velocity.x;

	if (lhsSlope == rhsSlope)
		return std::nullopt;

	const Position& lhsPos = lhs.position;
	const Position& rhsPos = rhs.position;
	const auto xIntersection = static_cast<int64_t>(
		(rhsPos.y - lhsPos.y + lhsSlope * lhsPos.x - rhsSlope * rhsPos.x) / (lhsSlope - rhsSlope));
	const auto yIntersection =
		static_cast<int64_t>((lhsSlope * (xIntersection - lhsPos.x)) + lhsPos.y);

	return Position{.x = xIntersection, .y = yIntersection};
}

bool isValidIntersection(const Hailstone& hailstone, const Position& intersection)
{
	return hailstone.velocity.x > 0 ? intersection.x >= hailstone.position.x
									: intersection.x <= hailstone.position.x;
}

bool intersects(const Hailstone& lhs, const Hailstone& rhs, int64_t min, int64_t max)
{
	const auto intersection = getIntersecion2D(lhs, rhs);
	if (!intersection)
		return false;

	if (!isValidIntersection(lhs, *intersection) || !isValidIntersection(rhs, *intersection))
		return false;

	return intersection->x >= min && intersection->x <= max && intersection->y >= min
		&& intersection->y <= max;
}

int64_t solvePart1(std::string_view input, int64_t min, int64_t max)
{
	const Hailstones hailstones = parseInput(input);

	return rng::distance(
			   vw::cartesian_product(hailstones, hailstones) | vw::filter([&](const auto& p) {
		const auto& [lhs, rhs] = p;
		return intersects(lhs, rhs, min, max);
	})) / 2;
}

int64_t solvePart2(std::string_view input)
{
	const Hailstones hailstones = parseInput(input);

	z3::context c;
	const z3::expr x = c.int_const("x");
	const z3::expr y = c.int_const("y");
	const z3::expr z = c.int_const("z");
	const z3::expr vx = c.int_const("vx");
	const z3::expr vy = c.int_const("vy");
	const z3::expr vz = c.int_const("vz");

	z3::solver solver{c};
	for (const auto& [i, hailstone] : hailstones | vw::take(3) | vw::enumerate)
	{
		const z3::expr t = c.int_const(std::format("t{}", i).c_str());
		solver.add(
			x == c.int_val(hailstone.position.x) - t * (vx - c.int_val(hailstone.velocity.x)));
		solver.add(
			y == c.int_val(hailstone.position.y) - t * (vy - c.int_val(hailstone.velocity.y)));
		solver.add(
			z == c.int_val(hailstone.position.z) - t * (vz - c.int_val(hailstone.velocity.z)));
	}

	if (solver.check() != z3::sat)
		throw std::runtime_error{"Failed to find a solution"};

	const z3::model m = solver.get_model();
	return m.eval(x).as_int64() + m.eval(y).as_int64() + m.eval(z).as_int64();
}

TEST(day24, test)
{
	EXPECT_EQ(solvePart1(day24::sample, 7, 27), 2);
	EXPECT_EQ(solvePart1(day24::input, 200000000000000, 400000000000000), 18651);

	EXPECT_EQ(solvePart2(day24::sample), 47);
	EXPECT_EQ(solvePart2(day24::input), 546494494317645);
}

} // anonymous namespace
