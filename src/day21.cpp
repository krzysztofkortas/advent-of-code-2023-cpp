#include "inputs/day21.h"

#include <algorithm>
#include <cstdint>
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

using Grid = std::vector<std::string>;
using Position = std::pair<int64_t, int64_t>;
using Positions = std::set<Position>;
using Direction = std::pair<int64_t, int64_t>;

constexpr auto directions = {Direction{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int64_t getEuclideanRemainder(int64_t val, int64_t modulo)
{
	return (val % modulo + modulo) % modulo;
}

class PlotsCounter
{
public:
	explicit PlotsCounter(Grid grid)
		: grid_{std::move(grid)}
		, gridSize_{ssize(grid_)}
	{
	}

	[[nodiscard]] int64_t countPlots(int64_t steps) const
	{
		const int64_t modulo = steps % gridSize_;
		const int64_t precalculatedSteps = std::min(steps, (modulo + (2 * gridSize_)));
		const std::vector<int64_t> answers = getPrecalculatedAnswers(precalculatedSteps);

		if (steps <= precalculatedSteps)
			return answers[steps];

		return extrapolate(
			{answers[modulo], answers[modulo + gridSize_], answers[modulo + (2 * gridSize_)]},
			steps);
	}

private:
	[[nodiscard]] Position getStartingPosition() const
	{
		for (const auto& [rowIndex, row] : grid_ | vw::enumerate)
			for (const auto& [colIndex, c] : row | vw::enumerate)
				if (c == 'S')
					return {rowIndex, colIndex};

		std::unreachable();
	}

	[[nodiscard]] char getTile(const Position& pos) const
	{
		return grid_.at(getEuclideanRemainder(pos.first, gridSize_))
			.at(getEuclideanRemainder(pos.second, gridSize_));
	}

	[[nodiscard]] std::vector<int64_t> getPrecalculatedAnswers(int64_t precalculatedSteps) const
	{
		const Position start = getStartingPosition();
		Positions visited{start};
		Positions plots{start};
		std::vector<int64_t> answers(precalculatedSteps + 1, 0);
		answers[0] = 1;

		for (const int64_t distance : vw::iota(1, precalculatedSteps + 1))
		{
			plots = getNewPlots(plots, visited);
			visited.insert(plots.cbegin(), plots.cend());

			answers[distance] = ssize(plots);
			if (distance >= 2)
				answers[distance] += answers[distance - 2];
		}

		return answers;
	}

	[[nodiscard]] Positions getNewPlots(const Positions& plots, const Positions& visited) const
	{
		return vw::cartesian_product(plots, directions) | vw::transform([&](const auto& p) {
			const auto& [plot, dir] = p;
			return Position{plot.first + dir.first, plot.second + dir.second};
		}) | vw::filter([&](const Position& plot) {
			return !visited.contains(plot) && getTile(plot) != '#';
		}) | rng::to<Positions>();
	}

	[[nodiscard]] int64_t extrapolate(std::vector<int64_t> answers, int64_t steps) const
	{
		const int64_t neededSteps = (steps + gridSize_ - 1) / gridSize_;
		const int64_t diff = answers.at(2) - (2 * answers.at(1)) + answers.at(0);

		for (const int64_t answersSize : vw::iota(ssize(answers), neededSteps))
			answers.push_back(diff + (2 * answers[answersSize - 1]) - answers[answersSize - 2]);

		return answers.back();
	}

	Grid grid_;
	int64_t gridSize_;
};

int64_t solve(std::string_view input, int64_t steps)
{
	const Grid grid = input | vw::split('\n') | rng::to<Grid>();
	return PlotsCounter{grid}.countPlots(steps);
}

TEST(day21, test)
{
	EXPECT_EQ(solve(day21::sample, 1), 2);
	EXPECT_EQ(solve(day21::sample, 2), 4);
	EXPECT_EQ(solve(day21::sample, 3), 6);
	EXPECT_EQ(solve(day21::sample, 6), 16);
	EXPECT_EQ(solve(day21::input, 64), 3762);

	EXPECT_EQ(solve(day21::sample, 6), 16);
	EXPECT_EQ(solve(day21::sample, 10), 50);
	EXPECT_EQ(solve(day21::input, 26501365), 621944727930768);
}

} // anonymous namespace
