#include <string_view>

namespace day11 {

using namespace std::literals;

inline constexpr auto sample =
    R"(...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....)"sv;

inline constexpr auto input =
    R"(...#...................#.......................#.......................................................#....................................
........................................................#...................................................................................
...............................#..........#..........................#.....#......................#.........................................
......#.................................................................................#.............................#..............#......
...........................................................................................................................................#
.................#........#.........................#...........#................#....................#......#..............................
........................................#................#....................................#..............................#..............
......................#.....................................................................................................................
..#.........#.......................#..............................#...............................................................#........
.............................................................#..................................................#...........................
...................#...........#...................#....................#...............................................#...................
...........................................#...................................#.....................#......#...............................
....#.........................................................................................................................#.............
........................................................................................#..........................#........................
...........#........................#..........................#............#...............................................................
.#...........................#..............................................................................................................
...............#..........................#................#.......................#.......................#................................
.....................#...........................................................................................#..........................
.........#.......................................#..................#..........#............#..........#..................#.................
.......................................................................................................................................#....
....................................#........................#..........................#...................................................
.....#.....................................#................................................................................................
...............#......................................#......................................................#....................#.........
....................#................................................................#.......#...............................#..............
...........#................................................................................................................................
.........................#......................#...........................................................................................
...#..............................#....................................#...........................#........................................
..................................................................#..................................................................#......
..........................................#..........#......................#............................................#..................
...............#......................................................................#..........................#........................#.
.....................#......................................................................................................................
..................................................#.............#.................................#.........................................
#..........................#.........................................................................................#......................
.....................................#......#................................#..............#...............#..................#............
........#............................................................................................#................................#.....
................................................................................................................#...........................
...............................#.......................#..................#................................................#................
..................................................................................................#...................#....................#
............................................................................................................................................
................#..........#....................#..................#..........................................#.............................
........#.................................#........................................#.....#.....................................#............
.......................#............................................................................................#.......................
.........................................................................................................................#.........#........
........................................................................................................#...................................
....#.......#...............#........................................#......................................................................
...........................................#.....#.............................................................#..............#.........#...
............................................................................................................................................
.....................#................#..................#....................#..............#..............................................
......#.....................................................................................................................................
...............#......................................................................................#.........................#...........
........................#...........................#..........#......................................................#.....................
.........................................#...........................#.................#......................#.............................
............................................................................................................................................
............................#.............................#.................................#..............................#...........#....
.#...........#......................#.........#...........................#.................................................................
............................................................................................................................................
.................#..................................................................#...........#.........#......................#..........
............................................................................................................................................
............................................................................................................................................
.........#...................#.................................#.............#..............................................................
...............#....................................................#...............................................#.....#.................
..........................................#..............................................#...........#.......#..............................
..#..................................................................................................................................#......
..........................................................................#.........#.......................................................
....................................#.........................#.........................................................#...................
...............................#................................................................#...........................................
...........#.............................................#............................................#............#........................
...........................................................................................................................#............#...
................#...........................#......................#..........#.......#.....................................................
#......................................................................................................................#............#.......
........................................................................#..................................#................................
..............................................................#...........................#.....#.........................................#.
......#.......#.....#.............#.........................................................................................................
.............................#.........#..................#.................................................................................
..........#.........................................................................................................#.......................
......................................................#................................................#...................#................
....#....................#.........................................#.........................................#..............................
....................................#.........#...............#...............#..............#...................................#..........
............................................................................................................................................
.............................#..................................................................................#.......#...................
........................................#................#...............#..................................................................
............................................................................................................................................
.............................................................#.........................#................#...................................
..........#......#............................#..................................#...............#..............................#.........#.
..................................#.................................................................................#.......................
....................................................#.......................#...............#.................#.......................#.....
.#...........#........................#..............................................#......................................................
................................................................#.......#..............................#....................................
..................................................................................................#...........................#.............
............................................................#............................................................#..............#...
......#.....................#......................................#...........#............................................................
.....................................................#.............................................................#.............#..........
.......................#.............#.....................................................................................................#
...........#.................................#............................#...........................#.....................................
.#...............................#....................................................................................#.....................
...................#...................................#..........................................#..............#..........................
.........................#.......................................#.............#............................................................
..........................................#.......#.....................#................#..................................#...............
...#.......................................................................................................#............................#...
............#.............................................#..................................#...................................#..........
............................#..........#.............................................................#.............#........................
......................#.....................................................................................................................
.............................................................................................................#..............................
....#........................................#.....................................#.......................................#................
.....................................................#..............#...................................................................#...
#....................................#....................#.......................................................................#.........
................................................................................................#...........................................
...........#.........#....................#...............................#.............#................................#..................
............................................................................................................................................
......#..........................#...........................#...........................................#...........#......................
.#.............#.........#.........................................#...........#.....#..................................................#...
.....................................#...................#.....................................................................#............
...........................................................................................#................................................
...................#................................................................................#..............#........................
...........................................#......#........................................................................................#
..#........................#..................................#.........................#...................................................
........#.............................#...............................................................................#.....................
...............................#........................#...............#..............................#....................................
.................................................................#..........................................#...............................
....................................................#........................#........#....................................#.........#......
....#.........#....................................................................................#.......................................#
......................#.....#.............................................................#.................................................
#......................................#......#....................................#...............................#.............#..........
.......................................................#..................................................#.................................
.........................................................................#......................#...........................................
...............................................................................#............................................#...............
....#........#................#...............................#.......................................................................#.....
.......................#.................................................................#..................#...............................
.....................................#.............#........................................................................................
...................................................................................................#......................................#.
..#.........................................................................................................................................
........#.................................#.............#...........#................#......................................................
...............................................................................................#............................#...............
.................#....................#.........................#..................................................................#........
....#.............................................#........................................................#........#.......................
.........................#.............................................#............................#.......................................
......................................................#.................................#................................................#..
.............................#...............#.................................#............................................................
.........#....................................................................................#........................#........#...........
..................#...........................................#.................................................#...........................)"sv;

} // namespace day11
