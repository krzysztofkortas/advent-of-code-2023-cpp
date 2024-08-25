#include "inputs/day22.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <queue>
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

struct Point
{
	int x{};
	int y{};
	int z{};
};

struct Brick
{
	Point low;
	Point high;
};

using Bricks = std::vector<Brick>;
using AdjacentBricks = std::vector<std::vector<int64_t>>;

Bricks parseInput(std::string_view input)
{
	constexpr auto getPoint = [](auto&& point) {
		auto v = point | vw::split(',') | vw::transform([](auto&& number) {
			return std::stoi(number | rng::to<std::string>());
		}) | rng::to<std::vector>();
		assert(ssize(v) == 3);
		return Point{.x = v[0], .y = v[1], .z = v[2]};
	};

	return input | vw::split('\n') | vw::transform([&](auto&& line) {
		auto points = line | vw::split('~') | vw::transform(getPoint) | rng::to<std::vector>();
		assert(ssize(points) == 2);
		return Brick{.low = points[0], .high = points[1]};
	}) | rng::to<std::vector>();
}

bool overlapXY(const Brick& lhs, const Brick& rhs)
{
	return lhs.low.x <= rhs.high.x && rhs.low.x <= lhs.high.x && lhs.low.y <= rhs.high.y
		&& rhs.low.y <= lhs.high.y;
}

Brick settleBrick(Bricks settledBricks, const Brick& brick)
{
	rng::sort(settledBricks, rng::greater(), [](const Brick& b) { return b.high.z; });
	const auto it = rng::find_if(
		settledBricks, [&](const Brick& settledBrick) { return overlapXY(brick, settledBrick); });
	const int z = (it != settledBricks.cend() ? it->high.z + 1 : 1);

	Brick result = brick;
	const int diff = result.low.z - z;
	result.low.z -= diff;
	result.high.z -= diff;
	return result;
}

Bricks getSettledBricks(Bricks bricks)
{
	rng::sort(bricks, rng::less(), [](const Brick& brick) { return brick.low.z; });
	Bricks settledBricks;
	for (const Brick& brick : bricks)
		settledBricks.push_back(settleBrick(settledBricks, brick));
	return settledBricks;
}

AdjacentBricks getSupportedBricks(const Bricks& bricks)
{
	AdjacentBricks supportedBricks(bricks.size());

	for (const auto& [brick1Index, brick1] : bricks | vw::enumerate)
		for (const auto& [brick2Index, brick2] : bricks | vw::enumerate)
			if (brick1.high.z + 1 == brick2.low.z && overlapXY(brick1, brick2))
				supportedBricks[brick1Index].push_back(brick2Index);

	return supportedBricks;
}

int getFallingBricks(const Bricks& bricks, const AdjacentBricks& adjacentBricks, int64_t brickIndex)
{
	std::vector<int> in(bricks.size(), 0);
	for (const auto& [i, _] : bricks | vw::enumerate)
		for (const int64_t adjacent : adjacentBricks[i])
			++in[adjacent];

	int result = -1;
	for (std::queue<int64_t> q{{brickIndex}}; !q.empty(); ++result)
	{
		for (const int64_t adjacent : adjacentBricks[q.front()])
			if (--in[adjacent] == 0)
				q.push(adjacent);
		q.pop();
	}

	return result;
}

std::vector<int> getFallingBricks(std::string_view input)
{
	const Bricks bricks = getSettledBricks(parseInput(input));
	const AdjacentBricks adjacentBricks = getSupportedBricks(bricks);

	return vw::iota(0, ssize(bricks)) | vw::transform([&](int64_t brickIndex) {
		return getFallingBricks(bricks, adjacentBricks, brickIndex);
	}) | rng::to<std::vector>();
}

int64_t solvePart1(std::string_view input)
{
	return rng::count(getFallingBricks(input), 0);
}

int64_t solvePart2(std::string_view input)
{
	return Utils::sum(getFallingBricks(input));
}

TEST(day22, test)
{
	EXPECT_EQ(solvePart1(day22::sample), 5);
	EXPECT_EQ(solvePart1(day22::input), 524);

	EXPECT_EQ(solvePart2(day22::sample), 7);
	EXPECT_EQ(solvePart2(day22::input), 77070);
}

} // anonymous namespace
