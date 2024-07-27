#include "inputs/day17.h"

#include <cstdint>
#include <functional>
#include <map>
#include <queue>
#include <ranges>
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

using Grid = std::vector<std::vector<int64_t>>;
using Direction = std::pair<int64_t, int64_t>;
using Position = std::pair<int64_t, int64_t>;
using Key = std::pair<Position, Direction>;

bool isValid(const Position& pos, int64_t width, int64_t height)
{
	return pos.first > 0 && pos.first <= height && pos.second > 0 && pos.second <= width;
}

int64_t getHeatLoss(const Grid& grid, int64_t minDistance, int64_t maxDistance)
{
	const int64_t height = std::ssize(grid);
	const int64_t width = std::ssize(grid.at(0));
	std::map<Key, int64_t> distMap;
	using QueueKey = std::pair<int64_t, Key>;
	std::priority_queue<QueueKey, std::vector<QueueKey>, std::greater<>> pq;
	pq.push({0, {{0, 0}, {0, 0}}});

	while (!pq.empty())
	{
		const auto [cost, key] = pq.top();
		pq.pop();
		const auto [pos, dir] = key;
		if (pos == Position{height - 1, width - 1})
			return cost;

		for (const auto& d : {Direction{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
		{
			if (dir == d || dir == Direction{-d.first, -d.second})
				continue;
			int64_t nextCost = cost;

			for (const int64_t distance : vw::iota(1, maxDistance + 1))
			{
				const Position nextPos{
					pos.first + (distance * d.first), pos.second + (distance * d.second)};
				if (!isValid(nextPos, width, height))
					continue;

				nextCost += grid.at(nextPos.first).at(nextPos.second);
				if (distance < minDistance)
					continue;

				const Key nextKey{nextPos, d};
				if (auto it = distMap.find(nextKey); it == distMap.end() || nextCost < it->second)
				{
					distMap.emplace(nextKey, nextCost);
					pq.emplace(nextCost, nextKey);
				}
			}
		}
	}

	std::unreachable();
}

int64_t solve(std::string_view input, int64_t minDistance, int64_t maxDistance)
{
	const Grid grid = input | vw::split('\n') | vw::transform([](auto&& line) {
		return line | vw::transform([](char c) { return static_cast<int64_t>(c - '0'); });
	}) | std::ranges::to<Grid>();

	return getHeatLoss(grid, minDistance, maxDistance);
}

int64_t solvePart1(std::string_view input)
{
	constexpr int minDistance = 1;
	constexpr int maxDistance = 3;
	return solve(input, minDistance, maxDistance);
}

int64_t solvePart2(std::string_view input)
{
	constexpr int minDistance = 4;
	constexpr int maxDistance = 10;
	return solve(input, minDistance, maxDistance);
}

TEST(day17, test)
{
	EXPECT_EQ(solvePart1(day17::sample), 102);
	EXPECT_EQ(solvePart1(day17::input), 1260);

	EXPECT_EQ(solvePart2(day17::sample), 94);
	EXPECT_EQ(solvePart2(day17::input), 1416);
}

} // anonymous namespace
