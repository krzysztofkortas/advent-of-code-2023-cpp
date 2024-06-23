#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "inputs/day16.h"

namespace {

namespace vw = std::ranges::views;

using std::int64_t;

using Map = std::vector<std::string>;

enum class Direction {
  top,
  bottom,
  left,
  right,
};

struct Position {
  int64_t row{};
  int64_t col{};

  auto operator<=>(const Position &) const = default;
};

struct Beam {
  Position position;
  Direction direction;

  auto operator<=>(const Beam &) const = default;
};

using Visited = std::set<Beam>;

Position getPosDiff(Direction direction) {
  static const std::unordered_map<Direction, Position> diff{
      {Direction::top, {-1, 0}},
      {Direction::bottom, {1, 0}},
      {Direction::left, {0, -1}},
      {Direction::right, {0, 1}}};

  return diff.at(direction);
}

std::optional<Beam> getNewBeam(const Beam &beam, Direction direction,
                               int64_t maxSize) {
  const auto diff = getPosDiff(direction);
  const Position position{beam.position.row + diff.row,
                          beam.position.col + diff.col};
  if (std::min(position.row, position.col) < 0 ||
      std::max(position.row, position.col) >= maxSize) {
    return std::nullopt;
  }

  return Beam{.position = position, .direction = direction};
}

Direction getNewDirection(Direction dir, char c) {
  static const std::unordered_map<Direction, std::pair<Direction, Direction>>
      directions{
          {Direction::top, {Direction::right, Direction::left}},
          {Direction::bottom, {Direction::left, Direction::right}},
          {Direction::left, {Direction::bottom, Direction::top}},
          {Direction::right, {Direction::top, Direction::bottom}},
      };

  const auto newDir = directions.at(dir);
  return c == '/' ? newDir.first : newDir.second;
}

void moveBeam(const Map &map, const std::optional<Beam> &beam,
              Visited &visited) {
  if (!beam || visited.contains(*beam))
    return;

  const int64_t mapLen = std::ssize(map);

  visited.insert(*beam);
  const auto c = map.at(beam->position.row).at(beam->position.col);
  if (c == '.') {
    const auto newBeam = getNewBeam(*beam, beam->direction, mapLen);
    moveBeam(map, newBeam, visited);
  } else if (c == '/' || c == '\\') {
    const Direction dir = getNewDirection(beam->direction, c);
    const auto newBeam = getNewBeam(*beam, dir, mapLen);
    moveBeam(map, newBeam, visited);
  } else {
    auto visitSplitter = [&](Direction dir1, Direction dir2) {
      if (beam->direction == dir1 || beam->direction == dir2) {
        const auto newBeam = getNewBeam(*beam, beam->direction, mapLen);
        moveBeam(map, newBeam, visited);
      } else {
        const auto newBeam1 = getNewBeam(*beam, dir1, mapLen);
        const auto newBeam2 = getNewBeam(*beam, dir2, mapLen);
        moveBeam(map, newBeam1, visited);
        moveBeam(map, newBeam2, visited);
      }
    };
    if (c == '|')
      visitSplitter(Direction::top, Direction::bottom);
    else if (c == '-') {
      visitSplitter(Direction::left, Direction::right);
    }
  }
}

int64_t getEnergizedTiles(const Map &map, const Beam &startBeam) {
  Visited visited;
  moveBeam(map, startBeam, visited);

  return std::ssize(
      visited | vw::transform([](const Beam &beam) { return beam.position; }) |
      std::ranges::to<std::set>());
}

Map readMap(std::string_view input) {
  return input | vw::split('\n') | std::ranges::to<Map>();
}

int64_t solvePart1(std::string_view input) {
  const Map map = readMap(input);

  return getEnergizedTiles(
      map, Beam{.position = {0, 0}, .direction = Direction::right});
}

int64_t solvePart2(std::string_view input) {
  const Map map = readMap(input);
  const int64_t maxLen = std::ssize(map);

  return std::ranges::max(
      vw::iota(0z, maxLen) | vw::transform([&](int64_t i) {
        const auto beams = {
            Beam{.position = {i, 0}, .direction = Direction::right},
            Beam{.position = {i, maxLen - 1}, .direction = Direction::left},
            Beam{.position = {0, i}, .direction = Direction::bottom},
            Beam{.position = {maxLen - 1, i}, .direction = Direction::top},
        };

        return std::ranges::max(beams | vw::transform([&](const Beam &beam) {
                                  return getEnergizedTiles(map, beam);
                                }));
      }));
}

TEST(day16, test) {
  EXPECT_EQ(solvePart1(day16::sample), 46);
  EXPECT_EQ(solvePart1(day16::input), 8146);

  EXPECT_EQ(solvePart2(day16::sample), 51);
  EXPECT_EQ(solvePart2(day16::input), 8358);
}

} // anonymous namespace