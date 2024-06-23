#include <string_view>

namespace day14 {

using namespace std::literals;

inline constexpr auto sample =
    R"(O....#....
O.OO#....#
.....##...
OO.#O....O
.O.....O#.
O.#..O.#.#
..O..#O..O
.......O..
#....###..
#OO..#....)"sv;

inline constexpr auto input =
    R"(..#OO..OO...#..O.OO....OO##O#...O..##.......O.OO..#.O.O#O....#.#O#O####...#.#..#.......O.O..O....#..
.O....#.........OO........O...........#O##O.OOO..O..O.#.#O#O......O..O.O......#O.....###...O..#O....
......O.....OO.O...O.O.O.#...#O...O.O#...O#.O.O.O##.O.....##...OO..#O.O....#.#....O.#O.....##....O..
.##O##...#..###.....O..O#O...........O.##O#OO.O#..OO..OO.#.....OO.O..#.....O..........O..O..O#.O.O..
...O.......O.#O.....OO.#.###....#O.O.##.O..O....O...#.O#O.#.#.O#......O.....#.........O..O##..O.O...
......O#....O..O..O...#..#........#.#..#........O.O#O.OO.O#.OO...#O.O#.O....#O.O.O#....O...O.#.O....
#O#.O....O.O...O..O#..O#..O##O#...........#....O...#.O....OO...O..O..O..OO..#.O...#......##...OO....
..OO#O....#O.O##...O#.OOO..O.O.O...#O#...O.#.OO....#....O..O#O....#..#...#..##.#....O.#...O.....O.O#
...##.#O#..O#..#....O#..OO...#..#......OO##O..O.#..##.#...#.O#..O...O....#....OO#...#..O.O....O.#..#
.#....#O..O...O.#OOO#..OO...O.O..##..#....##O..#....O....O.....#.#..O..#..#.O#...O#O....O....O.O....
...O.O##.OO.O.#O..O....##...O....O.##O##.O#.....#..#.....O.OO#O.O...#...#.O..#.#O...#O.#...O..OOO.OO
.......##......#.O.#.....#.....OO..O.....O#O.O....OO.O...OOO...#O..#O.O...##..O.O.#...O....O...O....
....OOO..#.#OO..O...#..#..OO.O.#.O..#...O....OOO.O.#.OO#.#......#..#.O.O.........O#...O.#.....##.O..
.....#.O..O#..O...O.#..#.......#..OO#.#.....O#O..O...O.O....OO.#OO..O........O.#.O....O....O....OOO.
#...O.O#OO#.....OO..#......O.O..O...##.O#.O.#.OOO#.#...#.......O..O..O...#.O...O.O....#....O....#...
O.O..#...O..O......##.O....O#.O.O..O#.###OOO....#.O....#.#..##O..#..##..O..#O.....O#.O##...#....#O..
#.......O#.#.#O....#...O.O##.....#O##.#OO.O.#.....OO.....O.OO.O..O...O....#.O.O#.OO#.O#..##......#.#
..##.O.O....O..#.O..O.#......#..#O....O...##...#.O.....O.....OO#.......#..OO##.....#......OO...O.O.O
.....O#....#..#......O#.....#O.O#........#...O.#...O.#.O#.O........O.O#OO.O..O..OO#O....#..#..OOO.O.
.#.....OO...OO......OO.OO.O.......#.O#O.......O##...O.#.#......O#.......O.#.....O.....O#...O...#..OO
..#O.O.O..#...........O.O.....O..#..O#..O...#O...#..OO.O##.O...O.....O.#..OOO....O.O....O...OO#.O...
.O.O..O#.....##..O.....O#...#..O.#O....#...............O...O.....OOO.OOO...O.O...O.#OO#.#...#O.....#
O#OO......#.O#..O#OOO.OO..O.O..OO.O.#O...#..O.#OO.O..O....OO#..#.#O....O..O#OO....O...O.OOO.O#O.....
..##O..O.O#..OO.##O#O.O..O.......OO.#....O..O.OO#O..O.O.OOO.##..#...O#......O....#..O.O#..O.......#.
.##.O.....##.OOO..O.#..O.....OO.#.....O#..#.O.#.....#.#OOOO.O...#...OO..#.......OO#O......#O..O.#...
#.#O.O.O....O..OO...#......O.#O#.#....#...OO.....#O.O#OO.#......#..#...#....OOO#OOO.....O.##O......#
...##O.#.O...O.O...#O......O.......O............#.O.#....#......#.OO..OO.O..O..##.....#OO..OO.#OO...
.........#.O..#..OO.O##..O.....#.....O..#.O#O....O.##..#....O#O.O..OO#.O..........OO....#.....O..#O.
.#....#OOO.#....#.........#.#.O.O##.....#O.OO#O#OO...#...O.......#......#..O..O.OO.O...#.##.O..##.#.
##...O#.#...O..O....O...#...OO.......#...#...O##....#.#..###....O.O##..#.......O....#......O#.O...O#
O.##...#O...O...O.#O.#.#.........O...O..O#.OO....O.#....O...O...#......O...#..O##.O..##O..O...#..#.#
.##..O....O..O#.OOO.O.#O#...###.O.......O##..O###.#........O..OO..O#O...O.OOO.#O.O..#O.#..#......O.O
..#O.OO#..#.#...O##...#...O#..O#O..O.O.......#.O#...#...##..O.#..O..O...#..O.O#.O.#...O...#...#.OO#.
.#O...#O.#.#...#.O.##...#O.O.....OO....O...#.....#.#.O..#..#.O...O.O....OO.OO.O...#......#.#..#..O.#
..O..O#..O....OOO..O.....#..#.#.....O....O..O#O..#..#.......O.....#O.#..OO#..#.....#O##....O#.#.O...
..#.O#O.##O#OO...OO....O...OO......O....O###...#...O..O#OOOO...#OO.O.#.O...#.#.O..O.O#.#..O.#O#.O...
O#O...#........O.#........OOO.....O#.....O.O#...#..O........#.O.....#..#...#...OOO.###.O..##....O..#
..#O#O..........#O....O..O.....O...#.O.O..##..OO.O...#O.#.#O#OO.......#...O...O.O...O...#O..#..O##..
#.O.O#OO#O..#O#.O......O...##..#.#.O.....#....#....O#..O...O..O..#O#....O.#O..O#.....#.O#OO.O....O..
....#O...#...#.#..O.#.O.#.O.....OO#O.OO.#O..##...O..#......#.OO...O..O##O.......OO.#O....O#....O...#
O.O..#O.O.O.O.#.O##...O#.OOOO.......O..O.##.O#.O.#OO...OO.........#.#.OO.O.#O.#O..#.#..O..O..O.#O#..
.O..#..OO..O##.....O...##.#.O.O..###O......O.###......#...#....OOO.....O..O......O..O.O..#O##.O...#.
O..#..O...#..O..O.#..#.O....O.#.##.#..#..OO#..O......OO###..O#O##O..O#............##.OO...O...OO#.#.
..O#.....O...#....O#.O....#.O#.....O.O....OO.##.O..#O.OO.O.O..#..#..O#O#.OO...#...........O..O...#.O
#..#.OO........O.....O.....O..O..O.#O#....O..OO..#....O..O.#..#.......O#..O....OOO...O#O.O.....O....
.#......O.......#O#....OO...O#..OOOOO.#..O..#.OO#O.##....#....#.#...#...##..#O..O#......#......O....
..O....OOOO#.#O.##O.O....#.O..O.O...OO..O...#...#...#..OOO#O........O.#O#..#..O..OOO..##...#..#O..O.
O.O#...#O#......#.O#.OO.#.O.O....#..O......O.##O.O...###.............OO.#OO.......O....O.#O..O.O##.O
O.OO.O#...#OOO..#....O..OO.#O#.OO..##O.OO.O....#.#...O...#O..OO......O.O.O........O...O.OOO.#..OO...
..OOOOO.#....#O.OO.O...O###..#O#O.#.....#OO.O......#O...#.#.#...O#.O.O.#OOO#...#O....##.............
#..O.O.#..O..........O..#..OOO#..O.......O.OO....#.#...O....O....O..O.O...O....O.O.#O#..#.....#.##.O
OOO#O...#....O#.....O.....#...#..O....O..........O.....OOO..#..O.........O.#....###..#......#....#..
....O...O.##.O.....#....O......##.....#OO...O#....O........###O.O.#O......O.#..O..#.#...#......OOO..
#O#..OO.O...#...OO....O..O.O.O..O#..#....O....#....#...OO.O#....OOO....#.O.##....#.....O.O.#O.O..O..
.......O..#.O.#...........O..O.....O#OO...O.O#.#...O....#.#.O#..O......O..........#.O.O.#..#.......O
..O.O....O....O#....#...O...#.OO........#....#O.O.O.....OO#.#.O##..OO.#.O..#..#...O#..O.#.O...O.#...
..#..#O#O..............O..O#..O...#..#.O.O.....##.....#OO#O...#.O.....###.OOO.##..O.......O....O.OO#
.OOO.....O#...O.OO....#.......O...#..#OO...#O.#....O....#...#..O...O...##..OOO#..........O.O#..#..OO
.O.#.O.O.............O..O#..##O.#..#O#O....##O#...OO.O.#.#......OO.O...#OO.##.O#O....O.#O...#......O
..#.O...OOOOO##.......O..#.......#.....O..#..O.....O......##...O#.O......#..........#.O..###..O.O.O.
...#...OO#..O.....O.O....OO.......O.O..OO..#O#..O..O...#....#.OO......O.O##.#.....O.......O...O..O..
....##.##.O......#O.#.O...OO...O.#...##.#.#.....O......#..O.O..#.....#..#.OO....O#..O....#.OOO#..O##
...O.O#...O..O..#.O..##.O....#OO.....O.O..O....O....#O...#.O.#.O.O..#O.O...#.#O...O..#O.#O.##...OO..
.O...........O...#O..#.O.O#.......O...O.O.#.O.O......O.O#..OO.#O.O...##...O.#..O...O#..O..OOO#.#....
.......O.#O#O..OO......O...O.#.O..##.#O#..O.O...O......O.......#......O##.O........##O.#....O#......
....O..O..#...O....O.OO...O#.#....O....O..#..#...O...O...#....O.........#.O..O..O.O..#.O............
#.O...#...O..#.......OO..#.O...##...#.....##.O.OOO...............O.#.O#..O..O#...O.O...#OO..O...#O.O
#..OO#.O...#.O....O.....O#...#....#.#O....#.#O.O..O...O.O..#O...#....O..OOO.#.O#.#...#O#.O#.O..O..#.
#...#.O......O#O.#O......#......OOO..O....#..O.#O...######.O#O.....O...#..O...OO..#......O....O.....
...##.O.....O#O...O.#O...##........OOO#O.#O.#....O..OO.#O.##O.O.###.......##.OO...#.....###........#
#..#.......OO..OOO..........OO...O#...OO......#.#.#..#..#.#...O#.O......O....O.#..O.#....#....O.OOOO
#O....O....#.O...O..#.#.O....OO..........#O.#O#..O.....#O.....#O.O..O..#.O##.OO##...O....#O..OO...O.
....#O##.OOO#...O.......OO.OO....O#.O...#.O..#..#..#....O..#.O....O#......O..O.O....O#...#O...#..#O.
..OO#OO..##....O.O.OOO......O....OOOO..#...#...O......#.####.O.....O....##O..#...O.#.O#O........#...
O#.##O#..#....O..O.OO#.##.......O......#...OO..O#.....#...O#O.O..O.....O...O.#..#.O..#O..#..#...#.O#
#.O#.O.....O.##...OO......O.O...O.O.....O...#...............#.O#.#.OOOOO#....##..O..##....OO.##.....
..#...O#.......#...O...O..##....#..O......#...O..O.....O.#.O.O......#O......#....#O..O..#.....O.....
...OO.OO.OOO..O..#O.......O##..#.O.#...O...O..O.O#.......#.#.O.#...O..#.O..O#.OOO..O........O.#..###
#O.......##.O..#.#...O.O#..#.#....#......#O#..#.#..#.#....OO...O.#...O..O#....#.#.#O...........##..#
..#O.O.........#.....#.O..O.O.....#OOO..OO.O.........OOO.#....#.......OO#.#.....O.O..#..#...#.O..O.O
..#..#...O.....#OO.#.....O..OO.#..O..#O...O..O....O..#O.O#O...........OO.O.#.....#..........#.OO.OO.
.O#OO.OO.O.....#....OO#...#O#.#...O.O..O#..OO......O#...#.......OO.#.O.O..#.#.#O.O...O#.#..#.#.##.O#
#.OO.O.#..O..OO#O#.#...O...O#...OO#......#....##OO...O..O..O.O.##...#...##.O.#....#....#..##.OOO..O.
..#....O.....#...O....OO...O...#.#..O..#.O#OO.#..##.....O..#....O..#...#.#.O.O.O.#........#.....#.O.
....##.#......O..O#.##.#........O.........#.##.#.#.#.#.O...O..O.#O#.....#.#...#..O..#O..#...OOOO#O##
...#.#....O..O##O..OO...OOOO##..O.......O.##.OO##.#.....#...O....#.O.#O.O##O..O...#....#O...#...O.#O
.....OO..#.O.O##.OO...#..OO.#.#.##...OO.#...O.O.O....O...O.#.#.#O.........#.OO.....O..###O...O..#..O
.#..#....O...O#O......OO.........O#O#....#.O.#...O..OOO..O.#.O........O.......O..........O...#.#.OO.
.O##...O#...#.O...#......#.#O...##..#O.#.##...#..O.#.OOO..O.OO#O.......##....#O.O.O..#.#....O##.....
.O.O....#.O.##.....#......#...........O........OO.O.O..#O.O#.OO...#.O.#....#..O..O.O.#..O...#O#..#O#
..##O.O#.O.#....#....O...#.##..#..OO..OO.O..O.....#....#.#.O........#O...##.OO.#..#..O.#.......#....
#.........OO....O#.#..O.#..#.O#.#..#.O.....O......###.........O#O.O.O..#......#..#..OO...O..O#...O.#
...O....#...OO#...O..#......#.O........O....#..##OO#.O...O.O...O.#............#...#O.O....O#O......O
...O.#.OO.#....O.......#..O....O#.O...#.OO.#..O....OO..#..OO..O..O.###OO...O.O.#.......OO..OO#...O..
...O.#..#O..OO#...O....#O....#OO.#OO..........#O.OO.O#...##...OO#O..#O..#.#.........#.O.#.........##
O..O.O...O.......O...#O#...OO.#OO...#........#.OO...O..........#...O......O....O..#...O.....#OO....#
O.O.#.#O.O.O.O..#.....OOO....#.#.O#O#...O.#OO.#....#..#..#.OO.OOO#O#........O.....O.#........#.#O...
O..#.O........OO..O..O#.#..O..#..O#....#O#....#O.O.O..OO...O#.O.#O#..#OOO..O..#...#...O.#.OO.O#OO.OO
.#.O..O..O...#.....#...O.O...#.#....OO.O.#.O.O..#O..O#..O#O..O.O#.....O#.O...O..OOO......OO.O.#.#.O.
.O.O.O....OO....OOO....O..#O#O..#....O#....O..O.O...O....O....#..O..#..#.O#.OOO..#.......#.....#..O.)"sv;

} // namespace day14
