#include "inputs/day16.h"

#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

using Grid = std::vector<std::string>;

enum class Direction
{
	top,
	bottom,
	left,
	right,
};

struct Position
{
	int64_t row{};
	int64_t col{};

	friend auto operator<=>(const Position&, const Position&) = default;
};

struct Beam
{
	Position position;
	Direction direction;

	friend auto operator<=>(const Beam&, const Beam&) = default;
};

Position getPosDiff(Direction direction)
{
	static const std::unordered_map<Direction, Position> diff{
		{Direction::top, {.row = -1, .col = 0}},
		{Direction::bottom, {.row = 1, .col = 0}},
		{Direction::left, {.row = 0, .col = -1}},
		{Direction::right, {.row = 0, .col = 1}}};

	return diff.at(direction);
}

Direction getNewDirection(Direction dir, char c)
{
	static const std::unordered_map<Direction, std::pair<Direction, Direction>> directions{
		{Direction::top, {Direction::right, Direction::left}},
		{Direction::bottom, {Direction::left, Direction::right}},
		{Direction::left, {Direction::bottom, Direction::top}},
		{Direction::right, {Direction::top, Direction::bottom}},
	};

	const auto newDir = directions.at(dir);
	return c == '/' ? newDir.first : newDir.second;
}

class EnergizedTilesCounter
{
public:
	explicit EnergizedTilesCounter(Grid grid)
		: grid_{std::move(grid)}
		, gridSize_{ssize(grid_)}
	{
	}

	int64_t countEnergizedTiles(const Beam& startBeam)
	{
		visited_.clear();
		moveBeam(startBeam);

		return ssize(visited_ | vw::transform(&Beam::position) | rng::to<std::set>());
	}

private:
	[[nodiscard]] bool isValid(const Position& pos) const
	{
		return pos.row >= 0 && pos.row < gridSize_ && pos.col >= 0 && pos.col < gridSize_;
	}

	[[nodiscard]] std::optional<Beam> getNewBeam(const Beam& beam, Direction direction) const
	{
		const Position diff = getPosDiff(direction);
		const Position pos{
			.row = beam.position.row + diff.row, .col = beam.position.col + diff.col};
		if (!isValid(pos))
			return {};

		return Beam{.position = pos, .direction = direction};
	}

	void split(const Beam& beam, Direction dir1, Direction dir2)
	{
		if (beam.direction == dir1 || beam.direction == dir2)
		{
			moveBeam(getNewBeam(beam, beam.direction));
		}
		else
		{
			moveBeam(getNewBeam(beam, dir1));
			moveBeam(getNewBeam(beam, dir2));
		}
	}

	void moveBeam(const std::optional<Beam>& beam)
	{
		if (!beam || visited_.contains(*beam))
			return;

		visited_.insert(*beam);
		const auto c = grid_.at(beam->position.row).at(beam->position.col);

		if (c == '.')
			moveBeam(getNewBeam(*beam, beam->direction));
		else if (c == '/' || c == '\\')
			moveBeam(getNewBeam(*beam, getNewDirection(beam->direction, c)));
		else if (c == '|')
			split(*beam, Direction::top, Direction::bottom);
		else if (c == '-')
			split(*beam, Direction::left, Direction::right);
	}

	Grid grid_;
	int64_t gridSize_;
	std::set<Beam> visited_;
};

int64_t countEnergizedTiles(const Grid& grid, const Beam& startBeam)
{
	return EnergizedTilesCounter{grid}.countEnergizedTiles(startBeam);
}

Grid readGrid(std::string_view input)
{
	return input | vw::split('\n') | rng::to<Grid>();
}

int64_t solvePart1(std::string_view input)
{
	const Grid grid = readGrid(input);

	return countEnergizedTiles(
		grid, Beam{.position = {.row = 0, .col = 0}, .direction = Direction::right});
}

int64_t solvePart2(std::string_view input)
{
	const Grid grid = readGrid(input);
	const int64_t maxLen = ssize(grid);

	return rng::max(vw::iota(0z, maxLen) | vw::transform([&grid, maxLen](int64_t i) {
		const auto beams = {
			Beam{.position = {.row = i, .col = 0}, .direction = Direction::right},
			Beam{.position = {.row = i, .col = maxLen - 1}, .direction = Direction::left},
			Beam{.position = {.row = 0, .col = i}, .direction = Direction::bottom},
			Beam{.position = {.row = maxLen - 1, .col = i}, .direction = Direction::top},
		};

		return rng::max(beams | vw::transform([&grid](const Beam& beam) {
			return countEnergizedTiles(grid, beam);
		}));
	}));
}

TEST(day16, test)
{
	EXPECT_EQ(solvePart1(day16::sample), 46);
	EXPECT_EQ(solvePart1(day16::input), 8146);

	EXPECT_EQ(solvePart2(day16::sample), 51);
	EXPECT_EQ(solvePart2(day16::input), 8358);
}

} // anonymous namespace
