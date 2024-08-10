#include "inputs/day12.h"

#include <cstdint>
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

struct Row
{
	std::string springs;
	std::vector<int> counts;
};

Row getPrependedRow(const Row& row)
{
	return Row{.springs = '.' + row.springs, .counts = row.counts};
}

int64_t getArrangements(const Row& row)
{
	const auto [springs, counts] = getPrependedRow(row);
	std::vector dp(springs.size() + 1, std::vector<int64_t>(counts.size() + 1));
	dp[0][0] = 1;
	for (const auto& [i, _] :
		 springs | vw::take_while([](char c) { return c != '#'; }) | vw::enumerate)
	{
		dp[i + 1][0] = 1;
	}

	for (const auto& [j, count] : counts | vw::enumerate)
	{
		for (int chunk = 0; const auto& [i, spring] : springs | vw::enumerate)
		{
			chunk = (spring != '.' ? chunk + 1 : 0);
			if (spring != '#')
				dp[i + 1][j + 1] = dp[i][j + 1];
			if (chunk >= count && springs.at(i - count) != '#')
				dp[i + 1][j + 1] += dp[i - count][j];
		}
	}

	return dp.back().back();
}

std::vector<Row> readInput(std::string_view input)
{
	return input | vw::split('\n') | vw::transform([](auto&& line) {
		auto splitted = line | vw::split(' ') | rng::to<std::vector<std::string>>();
		auto counts = splitted.at(1) | vw::split(',')
			| vw::transform([](auto&& count) { return std::stoi(count | rng::to<std::string>()); })
			| rng::to<std::vector>();
		return Row{.springs = splitted.at(0), .counts = counts};
	}) | rng::to<std::vector>();
}

int64_t solvePart1(std::string_view input)
{
	return Utils::sum(readInput(input) | vw::transform(getArrangements));
}

Row unfold(const Row& row)
{
	return Row{
		.springs = vw::repeat(row.springs, 5) | vw::join_with('?') | rng::to<std::string>(),
		.counts = vw::repeat(row.counts, 5) | vw::join | rng::to<std::vector>()};
}

int64_t solvePart2(std::string_view input)
{
	return Utils::sum(readInput(input) | vw::transform(unfold) | vw::transform(getArrangements));
}

TEST(day12, test)
{
	EXPECT_EQ(solvePart1(day12::sample), 21);
	EXPECT_EQ(solvePart1(day12::input), 7032);

	EXPECT_EQ(solvePart2(day12::sample), 525152);
	EXPECT_EQ(solvePart2(day12::input), 1493340882140);
}

} // anonymous namespace
