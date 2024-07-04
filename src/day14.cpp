#include "inputs/day14.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <ranges>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

using Map = std::vector<std::string>;

int64_t calculateLoad(const Map& map)
{
	return std::ranges::fold_left(
		map | vw::transform([](const std::string& line) {
			int64_t result = 0;
			for (const auto& [index, c] : line | vw::enumerate)
			{
				if (c == 'O')
					result += std::ssize(line) - index;
			}
			return result;
		}),
		0,
		std::plus{});
}

Map moveRocks(const Map& map)
{
	Map result;
	for (const std::string& line : map)
	{
		std::string resultLine = line;
		int64_t lastIndex = 0;
		for (const auto& [index, c] : line | vw::enumerate)
		{
			if (c == 'O')
				std::swap(resultLine[lastIndex++], resultLine[index]);
			else if (c == '#')
				lastIndex = index + 1;
		}
		result.push_back(resultLine);
	}
	return result;
}

Map rotateRight(const Map& map)
{
	return vw::iota(0z, std::ssize(map.at(0))) | vw::transform([&](int64_t col) {
			   return vw::iota(0z, std::ssize(map)) | vw::reverse
				   | vw::transform([&map, col](int64_t row) { return map[row][col]; });
		   })
		| std::ranges::to<Map>();
}

Map rotateLeft(const Map& map)
{
	return rotateRight(rotateRight(rotateRight(map)));
}

Map readMap(std::string_view input)
{
	return input | vw::split('\n') | std::ranges::to<Map>();
}

int64_t solvePart1(std::string_view input)
{
	Map map = readMap(input);
	map = moveRocks(rotateLeft(map));
	return calculateLoad(map);
}

Map makeStep(Map map)
{
	map = moveRocks(rotateLeft(map));
	map = moveRocks(rotateRight(map));
	map = moveRocks(rotateRight(map));
	map = moveRocks(rotateRight(map));
	map = rotateRight(rotateRight(map));

	return map;
}

int64_t solvePart2(std::string_view input)
{
	Map map = readMap(input);
	std::map<Map, int64_t> visited;
	std::vector<int64_t> results;
	const int64_t numberOfSteps = 1000000000;

	for (int64_t i : vw::iota(0, numberOfSteps + 1))
	{
		if (auto it = visited.find(map); it != visited.end())
		{
			const int64_t cycleLen = i - it->second;
			const int64_t resIndex = it->second + (numberOfSteps - i) % cycleLen;
			return results.at(resIndex);
		}
		else
		{
			visited.emplace(map, i);
			results.push_back(calculateLoad(rotateLeft(map)));
			map = makeStep(map);
		}
	}

	return calculateLoad(map);
}

TEST(day14, test)
{
	EXPECT_EQ(solvePart1(day14::sample), 136);
	EXPECT_EQ(solvePart1(day14::input), 113424);

	EXPECT_EQ(solvePart2(day14::sample), 64);
	EXPECT_EQ(solvePart2(day14::input), 96003);
}

} // anonymous namespace
