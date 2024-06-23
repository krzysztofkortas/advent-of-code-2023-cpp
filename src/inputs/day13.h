#include <string_view>

namespace day13 {

using namespace std::literals;

inline constexpr auto sample =
    R"(#.##..##.
..#.##.#.
##......#
##......#
..#.##.#.
..##..##.
#.#.##.#.

#...##..#
#....#..#
..##..###
#####.##.
#####.##.
..##..###
#....#..#)"sv;

inline constexpr auto input =
    R"(#..#.##.#..
###.####.##
###.####.##
###.####.##
###.####.##
#..#.##.#..
.#..#..#..#
..#.####.#.
####....###
..#......#.
.#.........
#...#..#...
####....###
.##......##
#...####...
###.#..#.##
#.########.

..#....#.
..######.
..###.##.
####..###
...####..
###.##.##
##.####.#
...#..#..
..######.

.##......##...#
..########....#
##.#....#.####.
.#...##...#..#.
.##.####.##..##
#.###..###.##.#
....#..#.......
.....##........
##..#..#..####.
...#.##.#......
.##########..##
#.##....##.##.#
.#..####..#..#.

####..#.#####
.#.#.#.#.##..
..#.##....#.#
#...#..##....
###.####.#.#.
..#....#.#..#
..#....#.#..#
###.####.#.#.
#...#..##....
..#.##....#.#
.#.#.#.#.###.
####..#.#####
####..#.#####

.##.####.##.#
#..#.##.#..##
...#.##.#....
#..#....#..#.
#..#....#..#.
...#.##.#....
#..#.##.#..##
.##.####.##.#
.##########.#
####....####.
#.#......#.#.
.##.####.##..
..####.###..#

...#..##..#
#....####..
.#.##.##.##
.#.##.##.##
#....####..
...#..##..#
##.##....#.
####.####.#
#.#..####..

...#..##..#..
..#..####..#.
...###..###..
..##.####.##.
..##......##.
....######...
..##.....###.
######..#####
.....#..#....
##.#.#..#.#.#
...#......#..
....##..##...
..#.######.#.
##.#.####.#.#
...##.##.##..
##.#..##..#.#
..####..####.

#.#..##..#.##
.##.#..#.##..
##..####..###
.#..#..#..#..
..#.#....#...
.#.#.##.#.#..
##..####..###

#.#..#.#.#.
##.....#..#
#.#.####..#
...#...###.
##....###..
#.#.#.....#
.##..#..###
.##..#..###
#.#.#.....#
##....###..
...#...###.
#.######..#
##.....#..#
#.#..#.#.#.
#.#..#.#.#.

##.##.#.######.
....##.........
......##.####.#
....####......#
..##.#.#.#..#.#
.###...#.####.#
###.#.##......#
....###..#..#..
...##.##.#..#.#
..##.##.##..##.
..#..#.#.#..#.#
##.#..###....##
..##..#........
..#.#..........
##.#.#.#..##..#
#####..........
....#.....##...

#....##......##..
########.##.#####
#.##.##..##..##.#
#....#.######.#..
.#..#.##.##.##.#.
.#..#.##....##.#.
.####..##..##..##
.#..#.#.####.#.#.
#.##.##...#..##.#
#######.#..#.####
##..###.#..#.###.
#....##.####.##..
.#..#...#..#...#.

....#..##
..#.#..##
..#.#.##.
..#.#..#.
.......#.
#.....#.#
.#.######
.####..#.
.####..#.
.#.######
#.....#.#
.......#.
..#.#..#.
..#.#.##.
..#.#..##
....#..##
.##.###.#

#.##..#..####
..#..###.#.#.
.##.#.#..##.#
#...#..###...
#...#..###...
.##.#.#..##.#
..#..###.#.#.
#.##..#..####
###.#.###..##
.#.#....###.#
##..##....##.
##..##....###
.#.#....###.#
###.#.###..##
#.##..#..####
..#..###.#.#.
.##.#.#..##.#

####.#.........
####.##..#..#..
....##.#..##..#
.....#..#....#.
.##.#...#....#.
########..##..#
#..###...#..#..
.##.......###..
#..###.###..###
#..#.#.#..##..#
....##..##..##.
.##.##.#..##..#
####.#...####..

#.#.######.
.##.#....#.
##.########
.##.#.##.#.
.##.#.##.#.
##.########
.##.#....#.
#.#.######.
...#..##..#
.#..#..#.#.
.##.#....#.

###...##..##...##
##.#..........#.#
###.#.##..##.#..#
..#...######...#.
..##.##....##.##.
####.#.####.#.###
...#.#.#..#.#.#..
..##.##....##.##.
####..##..##..###
...##..#..#..##..
..###...##...###.

##.##....##...#
.####....####..
#####....####..
#...####.#.....
#..##..####...#
#..##......##..
.##...##..#..##
#.#...#.#.#..##
..##.#..####...
..##.#..####...
#.#...#.#.#..##
.##...##..#..##
#..##......##..
#..##..####...#
#...####.#.....
#####....####..
.####....####..

..#########..
#...##...#..#
#...#.#......
.##..##..#...
.##....##...#
..#..##.##..#
..#..##.##..#
.##....##...#
.##..##..#...
#...#.#......
#...##...#..#
..#########..
.#.......####
#.#.##.#....#
....###......
.......##...#
.......##.#.#

#..#.#..####..#.#
###.#.#......#.#.
..####..#..#..###
###.#.#.#..#.#.#.
..##..#......#..#
...#..######.#..#
##.#..#.#..#.#..#
.##....######....
.####...####...##
#######......####
##....##.##.##...
#.####...##...###
#.####...##...###

....#..
###.##.
#.###..
.#.#.##
.#.#.##
#.###..
###.##.
....#.#
.#.#..#
.#.#..#
....#.#

##..######.#.#.
##..######.#.##
..##...#..#.#.#
#....#..###.#..
#.##.#.#.####.#
.#..#.##.#...#.
..##..##.##..#.
#....###...####
#.##.######....
#.##.#.#..#.#.#
##..##.##.#####

.####...#.#..#.
.##.#..##.##..#
.####..##.##..#
.####...#.#..#.
###.#.#.###....
#.#..#.###..###
#.#..##..#.##..
....#..#..#.##.
#.#.#..#.##.#.#
#.#.#..#.##.#.#
....#..#..#.##.
#.#..##..#.##..
#.#..#.###..###
###.#.#.###....
.####...#.#..#.

##.....
##.....
#..####
#..#.#.
#.#..#.
.#..##.
.#..##.
#.#..#.
#..#.#.
#..#.##
##.....

###.#.###......
.##..#.....#...
.#.#..#.#...###
##.###.#####...
#....#......###
#...####.#..#..
....###.###.#..
#.####.##.##.##
#.####..#.##.##
....###.###.#..
#...####.#..#..
#....#......###
##.###.#####...

#..##.#..####..#.
#...#.#..####..#.
..#.......##.....
.#####..........#
##..#............
.#.#.#..........#
##..##..........#
.##.#.##########.
.#.#....#....#...
##.##.###.##.###.
##.#.####....####
.#.#.##.######.##
###.#.#.######.#.
.#.#.#.########.#
##.##.#.##..##.#.

###.##.#..#.#
..####..###..
###...#..##.#
##.#..##.#.##
##.#..##.#.##
###...#..##.#
..####..###..
###.##.#..#.#
##.##.#.#..#.
..##..##.....
...#..##.....
........##..#
##...#.#.#..#
.##.##.#.#.#.
###...###..#.
###.##.##..#.
##.#....#.#..

#..#...####
#..##.#####
.#.....####
##..#.#####
#..#.##....
.#.####....
#.##.##....
.###.#.####
#..#.##....
##...##....
#...##.....
..##..##..#
..#........
#.##.##....
.##.#.#####

#.#...##.##.#
..#..####..##
#####....##..
#####....##..
.....####..##
#.#...##.##.#
#.#####......
.#.##.#######
##..#.#.####.
###.##..#..#.
....##..####.
##.##........
#..#..###..##
#.##..#..##..
#####..##..##

####.#.#.#..###
.#..#.##..#..#.
##.##.#.##....#
#..##.#.#.....#
#..###..#....#.
#..###..#....#.
#..##.#.#.....#
##.##.#.##....#
.#..#.##..#..#.
####.#.#.##.###
..#.#.#.##.#...
..#.#.#.##.#...
####.#.#.##.###
.#..#.##..#..#.
##.##.#.##....#

#.#...#.##..#.#
....###..####.#
.###.#.#####...
.###.#.#####...
....###..####.#
#.#...#.###.#.#
...#..#.#.#....
..###....#.#.#.
##..##.#....###
##..##.#....###
..###....#.#.#.
...#..#.#.#....
#.#...#.###.#.#
....###..####.#
.###.#.#####...

##.#.#...#..####.
..#.###...#......
...###....#.#..#.
..####..#.##....#
##..#....##.####.
##.#....#...#..#.
###.....##.##..##
##.####.#.###..##
..##..#...#.####.
......#.#.##....#
##.#..#..#.#.##.#
.....#.#...##..##
....###....#....#
#.#.###..##.####.
##.######...####.

.####..#.##
.#####.####
.#.###.####
.####..#.##
.#......#.#
..#...#..##
#..###.##..
##..#..####
#####.#.#..
###..#.####
.###.#....#
.###.#....#
###..#.####
#####.#.#..
##..#..####

...#######.##...#
..#.#..#.#.#####.
##..####..#...##.
##..####..#...##.
..#.#..#.#.#####.
...#######.###..#
..#.#...#..#..#.#
..#.##.....#.##..
##.##..##..##..##
.....#####...#.#.
..#.###.#.##.##..
..#...##.##..##.#
..#..#.##...###..

#..#.#.###...##
#.##...#.###..#
.#.############
.##.....#...###
##.....#...#.#.
...##....#.#..#
..#.....#.#.#..
..#.....#.#.#..
..###....#.#..#
##.....#...#.#.
.##.....#...###
.#.############
#.##...#.###..#
#..#.#.###...##
#..#.#.###...##

.#.##.#....####..
#......#.########
###..####...##...
#..###.###......#
.##..##....#..#..
.#....#.#.#....#.
#.####.#....##...

##.##..##..
##.##..##..
...#.######
##..##..##.
.#.....#...
.#.######.#
.##....##.#
.##....##.#
.#.######..
.#.....#...
##..##..##.
...#.######
##.##..##..

..##...#..#....#.
..#.....##.....#.
..#..##.##.##..#.
..#...##..##...#.
#####..#..#..####
..#..#......#..#.
...##........##..
####..##..##..###
..#..#.####.#..#.

...##....#.
.....#.#..#
....#...#.#
########...
..####.##..
.#####...##
###.###.##.
###.###.##.
.###.#...##
..####.##..
########...
....#...#.#
.....#.#..#
...##....#.
##..#.#####
.......##.#
.......##.#

.#...#...###.#.##
##...#####.#.##..
.####....##.###..
##.#..##.###..#..
#.##.##.##....##.
#.###..#...##..##
..##..#######..##
..##..#######..##
#.###..#...##..##
#.##.##.##....##.
##.#..##.###..#..
.####....##.####.
##...#####.#.##..
.#...#...###.#.##
.#...#...###.#.##
##...#####.#.##..
.####....##.####.

#####....##
##.##.##.##
..#.#.#..#.
..#..####..
..###.##.##
...#.####.#
####......#
##.#.#..#.#
####......#
###.######.
...#..##..#
##.........
..##..##..#
....#.##.#.
####.#..#.#

#.######.######
.##....##.####.
.#..##..#.####.
##..##..###..##
#..#..#..######
##..##..##....#
###....########
.#.####.#......
#.#....########
###....###....#
##.####.##....#

##########..#..
.######.####...
.#.##.#.###.###
.######...#.#..
#..##..#.#....#
##....##.##.###
#..##..#.###..#
#..##..#.#.###.
#..##..#.#.###.
#..##..#.###..#
##....##.##.###
#..##..#.#....#
.######...###..
.#.##.#.###.###
.######.####...

...#####.##.#####
...#####.##.#####
...#..#.#..#.#..#
#...#..#....#..#.
####.####..####.#
#.#....#.##.#....
##.#...######.#.#

#####..####
###.###....
.......####
....#######
..#.###....
.#.#..#....
.######....
#....#..##.
.#..###....
.###.##....
#####.#####
#.#....####
###.#.#....
..##.#.....
.#..#..####

..#..#.
#####.#
..#.##.
#####..
..###.#
......#
##..#..
###..##
######.
#####..
###..##

......#...##.#.
#####.##.####..
...#.#.####.##.
...#.#.####.##.
#####.##.#####.
......#...##.#.
##.#.#.##..#..#
...#..#.#....#.
#...##.#.##..#.
.#...#..#.#####
.....###.##.##.
.....###.##.##.
.#...#..#.#####

..#.##.#..#.#
##...........
##.##.#....#.
..#.....##...
...#.##....##
..###.#....#.
##.#..######.
....###...###
##.####.##.##
####..#....#.
.....#......#

.##.##.####.#
##..####..###
.#..###.##.##
##.#..#.##.#.
#.##.#.####.#
.##.....##...
####.........
.###.###..###
.#...#..##..#
..#....#..#..
###.#.#....#.
.#..####..###
##..####..###

.##....#.##
.##.#.#.###
#####.##.##
....###.#..
.##..#..#..
#.###..#...
#..#.###...
.##..#..###
######.....

###..##..##..
..##.###....#
#..#..#.#..#.
..###.#..##..
.#...##.#..#.
.#...##.#..#.
..###.#..##..
#..#..#.#..#.
..##.###....#
.##..##..##..
..##.........
..##.##.#..#.
##.#...######
....#########
....#...#..#.

.#.#..#.#...#
..##..##....#
..##..##....#
.#.#..#.#..##
##..##..###..
............#
#.##..##.##..
.#.#..#.#..#.
#..####..#.#.
..#....#...##
.#......#.##.

.#...#.##
#..#.##..
#..#..###
#..#...##
######.##
#####....
#..##.#..
.##...#..
######.##
.##....##
....#####
....##...
.##.##...
.......##
#######..
.##.#.#..
######.##

.####..##..##
.#..#.####.#.
.####.#..#.##
#....#.##.#..
#....#....#..
.####.####..#
..##........#
..##..#..#..#
.#..#......#.
#....######..
######.##.###

###..###..#....
.##..##.....##.
##.##.###.#.##.
........#......
#.#..#.#..#####
.#.##.#.#...##.
..####....#.##.
##....###.#....
..#..#...######
..#..#...#.....
..#..#..##..##.
...##...##.#..#
.######.#......
#########.####.
.#.##.#.##.####
##.##.##.......
##....##.##.##.

######..#
...#.###.
.#.....##
.#.....##
...#.##..
######..#
######..#

...#.#...#...
...#.#...#...
###.###.#.##.
....#.####.##
.....##..#..#
##..#..##..##
....##....##.
..##......###
##...#...#..#
#....#.##....
#....#.#.....

###..#.#..#
...#.##..##
##..#..##..
##.#....##.
###..#...##
..##..###..
..#.....#..
...##.##..#
..####..##.
.....#.##..
..###.#.#..
..#.#.#..##
..#.#.#..##
..###.#.#..
....##.##..

.....##..#.
#..#.#...##
....###..##
.....####..
.##.##.#.##
.....#.###.
.....#....#
#..##...###
####...####
####.#....#
######..###
#..##.##.##
#####..####
#####..#..#
#####..#.##

#.....###.#
#.###...#..
#.###...#..
#..#..###.#
##.##.#..#.
#####.#...#
.#.###.####
#.##.###...
..#..#..#..
.#...##.#..
.#...##.#..
..#..#..#..
#.##.###...
.#.###.####
#####.#...#
##.##.#..#.
#..#..###.#

...#..#.#..
##.##....##
..#..##.###
.....#.#.##
..##...####
##.....#..#
####..#.##.
...#.###...
##...#..###
###.###.#.#
##..##.##..
..#...#.#.#
..#..##..#.
..#.#..#...
..#.#..#...
..#...#..#.
..#...#.#.#

....#..#.#..##.
####.#.#....###
#..#.###.#...#.
.##.####.####..
.......#.....##
#..#..##..#.#..
####....##..#.#
....##....##.#.
####.#.#...####
#..#.#.####.###
#######.#.#####
####.#..###..##
####.#..###..##
#######.#.#####
#..#.#.########
####.#.#...####
....##....##.#.

.#..##....#.###
#..##.#..##.#..
##.##.#..##.#..
.#..##....#.###
###.###.##.#..#
.#..##.##..###.
##.#.##.####...
##.#.##.####...
.#..##.##..###.
###.###.##.#..#
.#..##....#.###
##.##.#..##.#..
#..##.#..##.#..
.#..##....#.###
#.#..###..###.#
#.###.#..#.##.#
.##..#.#...#..#

..#......
...#.....
..#.#..##
...###.##
...###.##
..#.#..##
...#.....
..#......
##.#####.
##...#..#
.#..#....
##.#...##
###.##.#.
...###..#
......#..
.....#..#
...##..#.

...#...#..##..#.#
......#..###...##
#.##.####.####.##
.######.#....#...
...###.##..#....#
...###.##..#.....
.######.#....#...
#.##.####.####.##
......#..###...##
...#...#..##..#.#
....#...##..###.#
..#.###.##......#
..#.###.##......#

###.####....#
...##.#.#..#.
###..#...##..
..#.#########
.###.#..#..#.
#.#..........
.#.##.#.####.
....###..##..
..#.#..#....#
..#.#..#....#
....###..##..
.#.##.#.####.
###..........

##..#...###..
.####.#..#.##
..##...#..###
..##....###..
........#####
##..####.....
#######......
#....###...##
#######.#####
#######.###..
..##..###..##
######.......
..##...###.##
.####.##...##
..##....##...
#.##.#.....##
.#..#.#.#####

#####.#.#
#.#.##...
#.#.##...
#####.#.#
##.######
###..##.#
...####..
..#.###..
..#.##...

....##.###.
####.......
#..#.....#.
....#.####.
#..####.###
#..##...#.#
#..##.#.#.#

####..###...###
######.....##..
######.#.#..#.#
######.##.#.##.
#####....#...#.
.....#.##.###..
....#..####.##.
#######.##.....
#####.##.#.#.#.
......#..#..#..
####.#..#.##...
....#....#....#
..........##...
####..###....#.
#..#####.#.....

.#.##...#......
#.#..#..#......
....#.#..######
.#..#.#..######
#.#..#..#......
.#.##...#......
..##.#.#.#.##.#
#...#..#.#....#
..#.#.#.##.##.#

######.#.##.#..
....####.#.#.#.
##.#.#..#.###..
..###.#....###.
..#..#.....##.#
##.#.###....#.#
..##.#.#.......
...##..####.##.
...####..#.##..
###.#####.###..
#########.###..
...####..#.##..
...##..####.##.
..##.#.#.......
##.#.###....#.#

.#.######...#.###
...#....#...##...
##.#....#.###.#..
#.#.####.#.#.####
#..........#...##
..#.####.#..###.#
#..........#.#...
#...#..#...#..##.
###..##..######.#
#.##....##.##.###
.##.####.##.#.#.#
.....##.....#..##
#..#.##.#..#.##.#
#..#.##.#..#.##.#
.....##.....#..##

##..#####.#.#
####...#.#.##
####...#.#.##
##..#######.#
..##..#######
##..#........
##.###....#.#
##....####.#.
..###...#####
###.#####.###
...#.####.#..
##.##...#...#
..#..##....##
...##...###.#
..##.#...#.#.
##.###.#..##.
####..##..#..

.##.###.#.##.#..#
.##...#..##.#####
####...#...#..##.
####.......######
#.##.##.###.#.##.
....##.####..####
......#..########
.....#.###..#.##.
.##.#..#######..#
.##......###..##.
.....###.##.##..#
####....#..#.#..#
####...#.#.#.....
#..#....#..######
....##.##.###.##.
#..###.#...##.##.
.##.#...#########

..####...#.#..#
########.......
#......##.##.##
##....##..#.##.
.#.##.#.....###
#.####.###.####
#.####.#####..#
##....###.#.##.
........###.###
#########...#..
#########......

########.####
#.#..#.#.....
...##....####
###..###.#..#
.#.##.#.#.##.
#......###.##
########.....
##.##.##..##.
###..###.####

#######...#....
.##..#..##.#..#
#..######.#####
#..#...#.##...#
.....#..##...##
.##.#....#..#.#
.....##.#....##
.##...#...#...#
.##...#...#...#
.....##.#....##
.##.#....#..#.#
.....#..##..###
#..#...#.##...#
#..######.#####
.##..#..##.#..#

.###...
##....#
##.#..#
.###...
...####
.#..#..
##....#
#####.#
.##..##
...##.#
.#.....
.#.....
...##.#
.##..##
#####.#
##....#
.#..#..

#..#....#..##
#..#....#..##
.#........#.#
.#.##..##.#..
.##.#..#.#..#
..#.#..#.#..#
#####..#####.
#.########.#.
.#.##..##.#.#

#.##..##.
....#....
....#....
#.#...##.
.##.###..
##..#..##
##..#..##

.##...##...
##.##....##
#..########
#..########
#####....##
.##...##...
....##..##.
..#..#..#..
#..########
#.#........
.###..##..#
#...######.
..#..####..

#..#...#.###...#.
#....###.#..#..##
..###.##.#...#...
..##.####..#..###
.#..###...##.####
#..####.##.##.#.#
##.####.##.##.#.#
.#..###...##.####
..##.####..#..###
..###.##.#...#...
#....###.#..#..##
#..#...#.###...#.
#..#...#.###...#.
#....###.#..#..##
..###.##.#...#...
..##.####..#..###
.#..###...##.####

##.....#.
##.....#.
.....##.#
##...#.##
#........
.#.....##
...##....
.##.#....
.#....#.#
.#....#.#
.##.#....
...##....
.#.....##
#........
##...#..#
.....##.#
##.....#.

##.#..##.#..#.##.
.#.##.#.#.##.#.#.
##.#####..##..###
#.#.####.####.###
###.#.#.#.##.#.#.
...###..#.##.#..#
#..#.###.#..#.###
#..#.###.#..#.###
...###..#.##.#..#
###.#.#.#.##.#.#.
..#.####.####.###

##..#......##
##.#.#.....#.
#.#####.##.##
#.#####.##.##
##.#.#.....#.
##..#......##
#..#...##..#.
#..##...##...
..###.#.#.##.
..###.#.#.##.
#..##...##...
#..#...##..#.
##..#.#....##
##.#.#.....#.
#.#####.##.##

.##..####..##.###
##.#..##..#.##.##
##.#......#.#####
.##..####..##.###
..#.##..##.#..#..
##.##.##..#.#####
#.##..##..##.#...

#.##..#..##....
.#.##.#.#######
...#...#.#..###
...##.####...##
#.##.#.##.#####
#.##.#.########
...##.####...##
...#...#.#..###
.#.##.#.#######
#.##..#..##....
##...####.###..

#.####..##..#
.....#.######
.#.#.#.#.####
##...##.#.##.
##.##...#.##.
..###..#.#..#
#####.#.##..#
..##..#..####
.##......#..#
.###.....#..#
..##..#..####

.##...#.####....#
#..#..#.#....###.
.#..####.##.#####
#..###.##..#.#..#
.##.#######..####
.##.#######..####
#..###.##..#.#..#

###.##.#..#.#.###
###.##.#..#.#.###
.##.##..###..##..
...#.####.##.##.#
####.#.#..#.##...
....####....#...#
..###.##.#.#...##

#####...##.##
#..##.##..##.
....##..#...#
#.#####....#.
....#....##..
#..#..#...#..
.##....######
.##.###..####
#..#.#...####
........##.##
.##.####..#..
.##..##.###.#
.##..##.###.#

...#.....##...#.#
...#.#.###....#..
..##.###......#.#
..##.###......#.#
...#.#.###....#..
...#.....##...#.#
#...#..##.#...#..
.####.######.....
###.##....#.....#
..##.#.###...#...
####..#...#..##..
..#.#####.###..##
##..#...#....#...
#######...###.#..
#######...###.#..
##..#...#....#...
..#######.###..##

####.#####.##.###
..#..###..#.#####
.#.#.####.##.#..#
#.####..#....#..#
.....#.#.#.###..#
##..#.####.#..##.
..#....#..####..#
.####.#####.#.##.
.####.#####.#.##.
..#....#..####..#
##..#.####.#..##.
.....#.#.#.###..#
#.####..#....#..#

#...####.
...#.##.#
.#..#..#.
#####..##
.####..##
.#..#..#.
...#.##.#
#...####.
#...#..#.
#.#.####.
#.#######

..##..#
###....
....##.
..##..#
....##.
...####
##..##.
###..#.
..#.##.
...#..#
..##..#
...#..#
##.####
####..#
..##..#

###....#...##..
..####..##....#
.####..#.######
####.#.#.#.##.#
#####..####..##
.###.####......
#.#..#.##.#..#.
#######..#.##.#
..#..###.##..##
.#.###.....##..
#...#....######
.###..#.#......
...##.##.#.##.#
...##.##.#.##.#
.####.#.#......
#...#....######
.#.###.....##..

#.#.###..#..#
.##.###.#....
#.###.#......
....##....##.
#.#.#..#.####
...#.#....##.
.#.##.#.#####
...##.#.#####
...#.#....##.

..#.##.#..##..#
#..#..######..#
##..#..###.#..#
###...##...#..#
##.########....
###...#.##.####
..#...##.#..##.

.##..##..##..
####..#..#..#
#..#..#..##.#
.##.#......#.
#######..####
####...##...#
.##....##....
#..#...##...#
.##.##....##.
####.#.##.#.#
....#..##..#.

.##.###
.##.###
.######
##...##
#..#.#.
.##....
.##....
#.#....
...###.
...###.
#.#.#..
.##....
.##....
#..#.#.
##...##)"sv;

} // namespace day13
