#include "inputs/day17.h"

#include <cstdint>
#include <functional>
#include <map>
#include <queue>
#include <ranges>
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

using Grid = std::vector<std::vector<int64_t>>;
using Direction = std::pair<int64_t, int64_t>;
using Position = std::pair<int64_t, int64_t>;
using Key = std::pair<Position, Direction>;

constexpr auto directions = {Direction{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class HeatLossSolver
{
public:
	HeatLossSolver(Grid grid, int64_t minConsecutive, int64_t maxConsecutive)
		: grid_{std::move(grid)}
		, minConsecutive_{minConsecutive}
		, maxConsecutive_{maxConsecutive}
		, width_{ssize(grid_.at(0))}
		, height_{ssize(grid_)}
	{
	}

	[[nodiscard]] int64_t getHeatLoss() const
	{
		const Position destination{height_ - 1, width_ - 1};
		std::map<Key, int64_t> distMap;
		std::priority_queue<QueueKey, std::vector<QueueKey>, std::greater<>> pq;
		pq.push({0, {{0, 0}, {0, 0}}});

		for (; !pq.empty(); pq.pop())
		{
			const auto [cost, key] = pq.top();
			const auto& [pos, dir] = key;
			if (pos == destination)
				return cost;

			for (const auto [nextCost, nextKey] : getNextPositions(key, cost))
			{
				if (auto it = distMap.find(nextKey); it == distMap.end() || nextCost < it->second)
				{
					distMap.insert_or_assign(nextKey, nextCost);
					pq.emplace(nextCost, nextKey);
				}
			}
		}

		std::unreachable();
	}

private:
	using QueueKey = std::pair<int64_t, Key>;

	[[nodiscard]] std::vector<QueueKey> getNextPositions(const Key& key, int64_t cost) const
	{
		const auto& [pos, dir] = key;
		return directions | vw::filter([&dir](const Direction& d) {
			return dir != d && dir != Direction{-d.first, -d.second};
		}) | vw::transform([&](const Direction& d) { return getNextPositions(pos, d, cost); })
			| vw::join | rng::to<std::vector>();
	}

	[[nodiscard]] std::vector<QueueKey> getNextPositions(
		const Position& pos, const Direction& dir, int64_t cost) const
	{
		std::vector<QueueKey> positions;
		for (int64_t nextCost = cost; const int64_t consecutive : vw::iota(1, maxConsecutive_ + 1))
		{
			const Position nextPos{
				pos.first + (consecutive * dir.first), pos.second + (consecutive * dir.second)};

			if (isValid(nextPos))
			{
				nextCost += grid_.at(nextPos.first).at(nextPos.second);
				if (consecutive >= minConsecutive_)
					positions.emplace_back(nextCost, Key{nextPos, dir});
			}
		}

		return positions;
	}

	[[nodiscard]] bool isValid(const Position& pos) const
	{
		return pos.first >= 0 && pos.first < height_ && pos.second >= 0 && pos.second < width_;
	}

	Grid grid_;
	int64_t minConsecutive_;
	int64_t maxConsecutive_;
	int64_t width_;
	int64_t height_;
};

int64_t solve(std::string_view input, int64_t minConsecutive, int64_t maxConsecutive)
{
	const Grid grid = input | vw::split('\n') | vw::transform([](auto&& line) {
		return line | vw::transform([](char c) { return static_cast<int64_t>(c - '0'); });
	}) | rng::to<Grid>();

	return HeatLossSolver{grid, minConsecutive, maxConsecutive}.getHeatLoss();
}

int64_t solvePart1(std::string_view input)
{
	constexpr int minConsecutive = 1;
	constexpr int maxConsecutive = 3;
	return solve(input, minConsecutive, maxConsecutive);
}

int64_t solvePart2(std::string_view input)
{
	constexpr int minConsecutive = 4;
	constexpr int maxConsecutive = 10;
	return solve(input, minConsecutive, maxConsecutive);
}

TEST(day17, test)
{
	EXPECT_EQ(solvePart1(day17::sample), 102);
	EXPECT_EQ(solvePart1(day17::input), 1260);

	EXPECT_EQ(solvePart2(day17::sample), 94);
	EXPECT_EQ(solvePart2(day17::input), 1416);
}

} // anonymous namespace
