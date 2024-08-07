#include <string_view>

namespace day23
{

using namespace std::literals;

inline constexpr auto sample =
	R"(#.#####################
#.......#########...###
#######.#########.#.###
###.....#.>.>.###.#.###
###v#####.#v#.###.#.###
###.>...#.#.#.....#...#
###v###.#.#.#########.#
###...#.#.#.......#...#
#####.#.#.#######.#.###
#.....#.#.#.......#...#
#.#####.#.#.#########v#
#.#...#...#...###...>.#
#.#.#v#######v###.###v#
#...#.>.#...>.>.#.###.#
#####v#.#.###v#.#.###.#
#.....#...#...#.#.#...#
#.#########.###.#.#.###
#...###...#...#...#.###
###.###.#.###v#####v###
#...#...#.#.>.>.#.>.###
#.###.###.#.###.#.#v###
#.....###...###...#...#
#####################.#)"sv;

inline constexpr auto input =
	R"(#.###########################################################################################################################################
#.#...#...###.....#...###...#...#.......#.....#.............#.........###...............#.......#.....#.....#.....#.......#...#.....###.....#
#.#.#.#.#.###.###.#.#.###.#.#.#.#.#####.#.###.#.###########.#.#######.###.#############.#.#####.#.###.#.###.#.###.#.#####.#.#.#.###.###.###.#
#...#.#.#.....#...#.#.....#.#.#.#.....#.#...#.#.......#.....#.#.......#...#.............#.....#.#...#...#...#.#...#.....#.#.#.#...#...#.#...#
#####.#.#######v###.#######.#.#.#####.#.###.#.#######.#.#####.#.#######.###.#################.#.###.#####.###.#.#######.#.#.#.###.###.#.#.###
#.....#...#...#.>.#.......#.#.#.#####.#...#.#.#...#...#.#.>.>.#...#...#.#...#.........#.......#.###...#...###.#.#.......#.#.#...#...#.#.#.###
#.#######.#.#.#v#.#######.#.#.#.#####.###.#.#.#.#.#.###.#.#v#####.#.#.#.#.###.#######.#.#######.#####.#.#####.#.#.#######.#.###.###.#.#.#.###
#.........#.#.#.#...###...#...#...#...#...#.#.#.#.#...#.#.#...#...#.#.#.#.###...#.....#.......#...#...#...###.#.#.....#...#.#...#...#...#...#
###########.#.#.###.###.#########.#.###.###.#.#.#.###.#.#.###.#.###.#.#.#.#####.#.###########.###.#.#####.###.#.#####.#.###.#.###.#########.#
#.........#.#.#...#...#.......#...#.#...###.#.#.#.#...#.#.#...#...#.#.#.#...>.>.#.....###...#...#.#.....#.#...#.#...#.#...#.#...#.#.......#.#
#.#######.#.#.###.###.#######.#.###.#.#####.#.#.#.#.###.#.#.#####.#.#.#.#####v#######.###.#.###.#.#####.#.#.###.#.#.#.###.#.###.#.#.#####.#.#
#.....###...#.#...###...#...#.#.#...#...#...#.#.#.#...#...#.#...#...#...###...#.......#...#.....#...#...#...#...#.#.#.#...#.#...#.#.#...#...#
#####.#######.#.#######.#.#.#.#.#.#####.#.###.#.#.###.#####.#.#.###########.###.#######.###########.#.#######.###.#.#.#.###.#.###.#.#.#.#####
#...#.......#.#.#.......#.#.#.#.#...#...#...#...#.#...#.....#.#...#...#...#...#.###...#.....#.......#...#...#.#...#.#.#...#.#...#.#...#.....#
#.#.#######.#.#.#.#######.#.#.#.###.#.#####.#####.#.###.#####.###.#.#.#.#.###.#.###.#.#####.#.#########.#.#.#.#.###.#.###.#.###.#.#########.#
#.#.........#...#...#...#.#.#.#.#...#.>.>.#.....#.#...#.......###...#.#.#.....#...#.#.#...#.#.........#...#.#...#...#...#.#.#...#.#.........#
#.#################.#.#.#.#.#.#.#.#####v#.#####.#.###.###############.#.#########.#.#.#.#.#.#########.#####.#####.#####.#.#.#.###.#.#########
#.................#...#.#.#.#.#.#.#.....#.#.....#.#...#.....#.........#...#...#...#.#.#.#.#.....#.....###...#...#.......#.#.#.....#.....#...#
#################.#####.#.#.#.#.#.#.#####.#.#####.#.###.###.#.###########.#.#.#.###.#.#.#.#####.#.#######.###.#.#########.#.###########.#.#.#
#.................###...#.#.#.#.#.#.....#.#.....#.#.###...#...#.....#...#.#.#.#...#.#.#.#.#...#.#...#.>.>.###.#...###...#...#...###...#...#.#
#.###################.###.#.#.#.#.#####.#.#####.#.#.#####.#####.###.#.#.#.#.#.###.#.#.#.#.#.#.#.###.#.#v#####.###.###.#.#####.#.###.#.#####.#
#...................#.#...#.#.#.#.#.....#.......#...#####.#.....###.#.#.#...#.###...#.#.#.#.#.#...#...#.....#.#...#...#.....#.#.....#.......#
###################.#.#.###.#.#.#.#.#####################.#.#######.#.#.#####.#######.#.#.#.#.###.#########.#.#.###.#######.#.###############
#.........#...#...#.#.#...#.#.#...#.........#.....#.......#.#.......#.#.#...#.......#...#...#...#.###.......#.#...#.......#.#.......###.....#
#.#######.#.#.#.#.#.#.###.#.#.#############.#.###.#.#######.#.#######.#.#.#.#######.###########.#.###.#######.###.#######.#.#######.###.###.#
#.....###...#...#.#.#.#...#.#.#.............#.#...#.........#.......#.#...#.#.......#.....#...#...#...#...###...#...#...#.#.###...#.....#...#
#####.###########.#.#.#.###.#.#.#############.#.###################.#.#####.#.#######.###.#.#.#####.###.#.#####.###.#.#.#.#.###.#.#######.###
#.....#...#...###...#...###...#...............#.....#...#...###...#.#.#.....#...#...#.#...#.#.....#.....#.....#.#...#.#.#.#.###.#.#...#...###
#.#####.#.#.#.#####################################.#.#.#.#.###.#.#v#.#.#######.#.#.#.#.###.#####.###########.#.#.###.#.#.#.###.#.#v#.#.#####
#.#...#.#.#.#...#...#...#.....#.......#.....#.......#.#.#.#.#...#.>.>.#.#...###...#...#.#...#.....#...###.....#.#...#.#.#.#.#...#.>.#.#.....#
#.#.#.#.#.#.###.#.#.#.#.#.###.#.#####.#.###.#.#######.#.#.#.#.#####v###.#.#.###########v#.###.#####.#.###.#####.###.#.#.#.#.#.#####v#.#####.#
#.#.#.#.#...#...#.#.#.#.#...#.#.....#...###...#...#...#.#.#...#.....###.#.#.#...#.....>.>.#...#...#.#.#...###...#...#.#.#.#.#.#####.#.......#
#.#.#v#.#####.###.#.#.#.###.#.#####.###########.#.#.###.#.#####.#######.#.#.#.#.#.#####v###.###.#.#.#.#.#####.###.###.#.#.#.#.#####.#########
#...#.>.#.....#...#.#.#.#...#...#...#.........#.#.#.###.#.#...#.......#...#.#.#.#.###...###...#.#.#.#.#...#...###.....#...#.#.#.....#.......#
#####v###.#####.###.#.#.#.#####.#.###.#######.#.#.#.###.#.#.#.#######.#####.#.#.#.###.#######.#.#.#.#.###v#.###############.#.#.#####.#####.#
#.....###.###...#...#.#...#.....#.....#.......#.#.#...#.#.#.#...#...#.....#...#...#...#####...#.#.#.#.#.>.>.#...#...#...###...#.#...#.#.....#
#.#######.###.###.###.#####.###########.#######.#.###.#.#.#.###.#.#.#####.#########.#######.###.#.#.#.#.#v###.#.#.#.#.#.#######.#.#.#.#.#####
#...#...#.#...#...###.....#...#.....#...#...#...#.....#...#...#...#.......#.......#.......#...#.#.#.#.#.#.#...#...#...#.......#...#.#.#.#...#
###.#.#.#.#.###.#########.###.#.###.#.###.#.#.###############.#############.#####.#######.###.#.#.#.#.#.#.#.#################.#####.#.#.#.#.#
###...#.#.#.###...###...#.#...#...#.#...#.#.#...........#####.........#.....#...#.#...#...#...#.#.#.#.#.#.#.#.....#...........#.....#.#...#.#
#######.#.#.#####.###.#.#.#.#####.#.###v#.#.###########.#############.#.#####.#.#.#.#.#.###.###.#.#.#.#.#.#.#.###.#.###########.#####.#####.#
#.......#...#.....#...#...#...#...#.#.>.>.#.....#.......#.............#.....#.#.#...#.#...#...#.#.#.#...#...#...#.#...#...#...#.....#...#...#
#.###########.#####.#########.#.###.#.#v#######.#.#######.#################.#.#.#####.###.###.#.#.#.###########.#.###.#.#.#.#.#####.###.#.###
#...#.......#.....#.....#.....#...#.#.#.......#.#.......#.............#.....#.#.....#...#.###...#...#...........#...#...#.#.#.......#...#...#
###.#.#####.#####.#####.#.#######.#.#.#######.#.#######.#############.#.#####.#####.###.#.###########.#############.#####.#.#########.#####.#
###...#.....#.....#...#.#...#.....#...#...#...#.........#...#...#...#.#.......#...#...#...#...#.....#.....#...#####.#.....#.....#...#.#.....#
#######.#####.#####.#.#.###.#.#########.#.#.#############.#.#.#.#.#.#.#########.#.###.#####.#.#.###.#####.#.#.#####.#.#########.#.#.#.#.#####
#.......#...#.......#.#...#...#...###...#...#...#.........#...#...#...#...#.....#.....#...#.#.#...#.#...#...#.....#...###...###...#.#.#.....#
#.#######.#.#########.###.#####.#.###.#######.#.#.#####################.#.#.###########.#.#.#.###.#.#.#.#########.#######.#.#######.#.#####.#
#.........#.#...#...#...#.#...#.#.#...#.......#.#.#...#.......#.....###.#.#.......#...#.#.#.#.###.#...#.#.........#...#...#.....#...#.#.....#
###########.#.#.#.#.###.#.#.#.#.#.#.###.#######.#.#.#.#.#####.#.###.###.#.#######.#.#.#.#.#.#.###.#####.#.#########.#.#.#######.#.###.#.#####
#.........#...#.#.#...#...#.#...#.#.....#.....#.#...#...#.....#...#.###.#.#...#...#.#.#.#...#...#.....#.#.....#...#.#.#...#.....#.....#.....#
#.#######.#####.#.###.#####.#####.#######.###.#.#########.#######.#.###.#.#.#.#v###.#.#.#######.#####.#.#####.#.#.#.#.###.#.###############.#
#.......#.#.....#.#...#...#.....#.#...###...#...#...#...#.....#...#.#...#.#.#.>.>.#.#.#.#.......#...#.#.#...#.#.#...#.#...#.....#.......#...#
#######.#.#.#####.#.###.#.#####.#.#.#.#####v#####.#.#.#.#####.#.###.#.###.#.###v#.#.#.#.#.#######.#.#.#.#.#.#v#.#####.#.#######.#.#####.#.###
#.......#...###...#...#.#.#####.#...#.....>.>.#...#.#.#.#.....#...#...###...#...#.#.#.#.#.#.....#.#.#.#...#.>.>.#.....#...#.....#.....#...###
#.#############.#####.#.#.#####.###########v#.#.###.#.#.#.#######.###########.###.#.#.#.#.#.###.#.#.#.#######v###.#######.#.#########.#######
#.........#...#.#.....#.#.###...#.....#...#.#.#.#...#.#.#.......#.........###...#...#.#.#.#.#...#.#.#.#.......###...#...#.#...#...###.......#
#########.#.#.#.#.#####.#.###.###.###.#.#.#.#.#.#.###.#.#######.#########.#####.#####.#.#.#.#.###.#.#.#.###########.#.#.#.###.#.#.#########.#
###.......#.#.#.#.#...#.#.#...###...#...#...#...#.#...#.#...#...#...#.....#...#.....#.#.#.#.#.#...#...#...#...###...#.#.#.#...#.#...#...#...#
###.#######.#.#.#.#.#.#.#.#.#######.#############.#.###.#.#.#.###.#.#.#####.#.#####.#.#.#.#.#.#.#########.#.#.###.###.#.#.#.###.###.#.#.#.###
#...#...###.#.#.#.#.#.#.#.#...#.....#...........#.#.#...#.#.#.#...#.#...#...#.......#.#.#.#.#.#.#####.....#.#...#...#.#.#.#...#.#...#.#.#...#
#.###.#.###.#.#.#.#.#.#.#.###.#.#####.#########.#.#.#.###.#.#v#.###.###.#.###########.#.#.#.#.#.#####.#####.###.###.#.#.#.###.#.#.###.#.###.#
#...#.#.#...#.#.#.#.#.#.#.#...#...#...#...#.....#...#.....#.>.>.###.#...#...#...#...#...#.#.#.#.#.....#...#.###...#...#...#...#.#.#...#.#...#
###.#.#.#.###.#.#.#.#.#.#.#.#####.#.###.#.#.#################v#####.#.#####.#.#.#.#.#####.#.#.#.#.#####.#.#.#####.#########.###.#.#.###.#.###
#...#.#.#...#...#.#.#.#.#...###...#.#...#...#...#.....#.......#...#...#...#...#...#...###...#.#.#.....#.#...#.....###...###.#...#.#.#...#.###
#.###.#v###.#####.#.#.#.#######.###.#.#######.#.#.###.#.#######.#.#####.#.###########.#######.#.#####.#.#####.#######.#.###.#.###.#.#.###v###
#.....#.>...#...#...#.#.#.......#...#.......#.#...#...#.......#.#.#...#.#.#...........#...###...###...#.#...#.........#...#...###...#.#.>.###
#######v#####.#.#####.#.#.#######.#########.#.#####.#########.#.#.#.#.#.#.#.###########.#.#########.###.#.#.#############.###########.#.#v###
#.......#.....#.....#.#.#.#...#...#.........#.....#.....#.....#.#...#...#.#.........#...#.#.......#...#.#.#.........#...#...#####...#...#...#
#.#######.#########.#.#.#.#.#.#.###.#############.#####.#.#####.#########.#########.#.###.#.#####.###.#.#.#########.#.#.###.#####.#.#######.#
#.......#.#.........#...#...#.#.#...#...#.....###...#...#.....#.....#.....#.........#.#...#...#...###...#.....#...#...#.....#.....#...#.....#
#######.#.#.#################.#.#.###.#.#.###.#####.#.#######.#####.#.#####.#########.#.#####.#.#############.#.#.###########.#######.#.#####
###.....#.#.#...#...###.....#.#.#.....#...#...#...#.#.###.....#...#.#.....#.#.....#...#.#...#.#...#...###...#...#.......#...#.......#.#...###
###.#####.#.#.#.#.#.###.###.#.#.###########.###.#.#.#.###v#####.#.#.#####.#.#.###.#.###.#.#.#.###.#.#.###.#.###########.#.#.#######.#.###.###
#...#...#.#...#...#.....#...#...#...........#...#...#...>.>.###.#.#...#...#...#...#...#...#.#.#...#.#...#.#.#...........#.#.###.....#...#...#
#.###.#.#.###############.#######.###########.###########v#.###.#.###.#.#######v#####.#####.#.#.###.###.#.#.#.###########.#.###.#######.###.#
#...#.#.#.#...............#...###...#...#...#.....#.......#.....#.#...#.#.....>.>...#.#.....#.#.###...#.#.#.#.....#...#...#...#...#.....#...#
###.#.#.#.#.###############.#.#####.#.#.#.#.#####.#.#############.#.###.#.#####v###.#.#.#####.#.#####.#.#.#.#####v#.#.#.#####.###.#.#####.###
###...#...#.......###.....#.#...###...#...#.#.....#.........#.....#...#.#...###...#.#.#.#...#.#...#...#.#.#.#...>.>.#.#.#.....###.#.###...###
#################.###.###.#.###.###########.#.#############.#.#######.#.###.#####.#.#.#.#.#.#.###.#.###.#.#.#.###v###.#.#.#######.#.###v#####
#...#.......#.....#...#...#...#.#...###...#.#.....#.........#.......#.#.#...#.....#...#...#...###.#...#.#.#...###...#.#.#.....#...#...>.#...#
#.#.#.#####.#v#####.###.#####.#.#.#.###.#.#.#####.#.###############.#.#.#.###.###################.###.#.#.#########.#.#.#####.#.#######v#.#.#
#.#.#.....#.#.>.###...#.....#.#.#.#.#...#...#.....#.#...#.......#...#.#.#...#.................#...#...#...###.....#.#.#.....#...#.....#...#.#
#.#.#####.#.#v#.#####.#####.#.#.#.#.#.#######.#####.#.#.#.#####.#.###.#.###.#################.#.###.#########.###.#.#.#####.#####.###.#####.#
#.#.......#...#...###.#.....#.#.#.#.#...#...#.....#.#.#...###...#.....#.....#.................#.#...#.........###...#.#...#.....#...#...#...#
#.###############.###.#.#####.#.#.#.###.#.#.#####.#.#.#######.###############.#################.#.###.###############.#.#.#####.###.###.#.###
#.#.........#...#...#.#.#...#.#.#.#.###.#.#.#...#.#.#.#.......###...........#...#.............#.#...#.....#.........#...#...#...#...###...###
#.#.#######.#.#.###.#.#.#.#.#.#.#.#.###v#.#.#.#.#.#.#.#.#########.#########.###.#.###########.#.###.#####.#.#######.#######.#.###.###########
#.#.#.......#.#.###.#.#.#.#.#.#...#...>.>.#.#.#.#.#.#.#.....#...#.#.........#...#.#.........#.#...#.#.....#.#.....#...#.....#.###...........#
#.#.#.#######.#.###.#.#.#.#.#.#########v###.#.#.#.#.#.#####.#.#.#.#.#########.###.#.#######.#.###.#.#.#####.#.###.###.#.#####.#############.#
#.#.#.#.....#.#...#.#.#...#...#.........###.#.#...#...#.....#.#...#...#.....#.....#...#...#...###...#.....#.#...#.#...#.......#.............#
#.#.#.#.###.#.###.#.#.#########.###########.#.#########.#####.#######.#.###.#########.#.#.###############.#.###.#.#.###########.#############
#.#.#...#...#.#...#...###...###.....#.....#.#.......#...#.....###.....#.#...#.......#...#...........#...#...#...#...#...###...#.............#
#.#.#####.###.#.#########.#.#######.#.###.#.#######.#.###.#######.#####.#.###.#####.###############.#.#.#####.#######.#.###.#.#############.#
#.#.....#.....#.....#...#.#...#...#...#...#...#.....#.#...#.......###...#...#.....#.................#.#.......###...#.#.###.#...#...........#
#.#####.###########.#.#.#.###.#.#.#####.#####.#.#####.#.###.#########.#####.#####.###################.###########.#.#.#.###.###.#.###########
#...#...#...........#.#.#.#...#.#.#...#.....#...#...#...###...........#.....#...#.........#...#.....#.........###.#...#...#.#...#...........#
###.#.###.###########.#.#.#.###.#.#.#.#####v#####.#.###################.#####.#.#########.#.#.#.###.#########.###.#######.#.#.#############.#
###...###.........#...#...#.#...#.#.#.#...>.>.###.#.###...###...#.......#...#.#.#...#.....#.#.#.#...#.......#...#.....#...#.#.#####.......#.#
#################v#.#######.#.###.#.#.#.###v#.###.#.###.#.###.#.#.#######.#.#.#.#.#.#.#####.#.#.#.###.#####.###.#####.#.###.#.#####v#####.#.#
###...#.........#.>.#.......#...#...#...###.#.....#...#.#.#...#...#...###.#.#.#.#.#.#.###...#...#...#...#...#...#.....#.#...#...#.>.#####...#
###.#.#.#######.#v###.#########.###########.#########.#.#.#.#######.#.###.#.#.#.#.#.#v###.#########.###.#.###.###.#####.#.#####.#.#v#########
#...#.#.......#...###.......#...###...#...#...#.......#.#.#.......#.#.#...#.#.#.#.#.>.>.#.....#.....#...#.#...###...###...#...#...#.........#
#.###.#######.#############.#.#####.#.#.#.###.#.#######.#.#######v#.#.#.###.#.#.#.###v#.#####.#.#####.###.#.#######.#######.#.#############.#
#...#...#...#...........###...###...#...#.....#.#...#...#.#.....>.>.#.#...#...#.#.#...#...###.#.#...#...#.#...#...#...#...#.#.###...#...#...#
###.###.#.#.###########.#########.#############.#.#.#.###.#.#####v###.###.#####.#.#.#####.###.#.#.#.###.#.###v#.#.###.#.#.#.#.###.#.#.#.#.###
###...#.#.#...........#.....#...#.............#.#.#.#...#...###...###.#...###...#.#.....#.....#.#.#...#.#.#.>.>.#.#...#.#...#.....#...#...###
#####.#.#.###########.#####.#.#.#############.#.#.#.###.#######.#####.#.#####.###.#####.#######.#.###.#.#.#.#v###.#.###.#####################
#.....#.#...........#...#...#.#.#.........#...#...#.#...###...#.....#.#.#...#.....###...###.....#...#.#.#...#.#...#.###.#...#.....#.........#
#.#####.###########.###.#.###.#.#.#######.#.#######.#.#####.#.#####.#.#.#.#.#########.#####.#######.#.#.#####.#.###.###.#.#.#.###.#.#######.#
#.....#...........#...#.#.###.#.#.#.....#.#...#...#...###...#.#.....#.#...#.#.........###...#...#...#.#.#.....#.....###...#...#...#...#.....#
#####.###########.###.#.#.###.#.#.#.###.#.###.#.#.#######.###.#.#####.#####.#.###########.###.#.#.###.#.#.#####################.#####.#.#####
#.....#.....#...#.....#.#.#...#...#.#...#.....#.#.#...#...###.#.....#.....#.#...........#...#.#.#.###.#.#.#.....#...#####...###.......#.....#
#.#####.###.#.#.#######.#.#.#######.#.#########.#.#.#.#.#####.#####.#####.#.###########.###.#.#.#.###.#.#.#.###.#.#.#####.#.###############.#
#.....#.###...#.......#...#...#.....#.......#...#.#.#.#.....#.#...#.....#.#.#.......#...###...#.#...#...#...#...#.#...#...#.#.......#...#...#
#####.#.#############.#######.#.###########.#.###.#.#.#####.#.#.#.#####.#.#.#.#####.#.#########.###.#########.###.###.#.###.#.#####.#.#.#.###
#.....#.#.............###...#.#.#.....#.....#...#...#.......#.#.#.#...#.#...#.....#.#.......#...#...#...#.....###.#...#...#...#...#...#...###
#.#####.#.###############.#.#.#.#.###.#.#######.#############.#.#.#.#.#.#########.#.#######.#.###.###.#.#.#######.#.#####.#####.#.###########
#.....#.#.............#...#.#...#...#...#...#...#.....#...###...#...#...#.....#...#.........#.....#...#...#.......#.....#.......#...........#
#####.#.#############.#.###.#######.#####.#.#.###.###.#.#.###############.###.#.###################.#######.###########.###################.#
#.....#.#...#.........#.#...#.....#.#...#.#.#.....###...#.........#.....#...#.#...................#.........#...#...#...###...#...#...#...#.#
#.#####.#.#.#.#########.#.###.###.#.#.#.#.#.#####################.#.###.###.#.###################.###########.#.#.#.#.#####.#.#.#.#.#.#.#.#.#
#.#.....#.#.#...#...###.#...#...#.#.#.#...#.#...#.....#...........#...#.#...#...#...#.............#...........#.#.#.#.#.....#...#.#.#...#...#
#.#.#####.#.###.#.#.###.###.###.#.#.#.#####.#.#.#.###.#.#############.#.#.#####.#.#.#.#############.###########.#.#.#.#.#########.#.#########
#.#.#.....#.....#.#.#...#...###.#.#...#.....#.#.#.#...#.....#...#####.#.#.....#...#.#.......#.....#.......#...#...#...#.......#...#.#.......#
#.#.#.###########.#.#.###.#####.#.#####.#####.#.#.#.#######.#.#.#####.#.#####.#####.#######.#.###.#######.#.#.###############.#.###.#.#####.#
#.#.#.............#.#...#...#...#...#...#.....#.#.#.#...#...#.#...#...#.#.....#...#.........#.#...#...###...#.#...#...........#.....#.....#.#
#.#.###############.###.###.#.#####.#.###.#####.#.#.#.#.#v###.###.#.###.#.#####.#.###########.#.###.#.#######.#.#.#.#####################.#.#
#...#####...........###.#...#...#...#...#.....#.#.#.#.#.>.>.#.#...#...#.#.......#.......#.....#...#.#.#...#...#.#.#.............#.....#...#.#
#########.#############.#.#####.#.#####v#####.#.#.#.#.#####.#.#.#####.#.###############.#.#######.#.#.#.#.#.###.#.#############.#.###.#.###.#
###...#...#.....###...#.#.#...#.#.#...>.>.#...#.#.#...#####...#.#.....#...#.....#...#...#.#.......#.#.#.#.#...#.#...#...#.......#.#...#...#.#
###.#.#.###.###.###.#.#.#.#.#.#.#.#.#####.#.###.#.#############.#.#######.#.###.#.#.#.###.#.#######.#.#.#.###.#.###.#.#.#.#######.#.#####.#.#
#...#...#...###...#.#.#.#.#.#.#.#...#.....#...#.#.....#.........#.#.......#...#.#.#...###.#.###...#.#.#.#.###.#.#...#.#.#...#...#.#...#...#.#
#.#######.#######.#.#.#.#.#.#.#.#####.#######.#.#####.#.#########.#.#########.#.#.#######.#.###.#.#.#.#.#.###v#.#.###.#.###v#.#.#.###.#.###.#
#.....#...#...###.#.#.#.#...#.#...###.#...#...#.#.....#.....#...#.#.###...###.#.#.....#...#...#.#.#.#.#.#.#.>.>.#...#.#.#.>.#.#...#...#.#...#
#####.#.###.#.###.#.#.#.#####.###.###.#.#.#.###.#.#########.#.#.#.#.###.#.###.#.#####v#.#####.#.#.#.#.#.#.#.#######.#.#.#.#v#.#####.###.#.###
#.....#.#...#.....#.#.#.....#...#.#...#.#.#...#.#.#.........#.#.#.#.#...#.#...#...#.>.>.#.....#.#.#.#.#.#.#.#.......#.#.#.#.#.#.....###.#.###
#.#####.#.#########.#.#####.###.#.#.###.#.###.#.#.#.#########.#.#.#.#.###.#.#####.#.#####.#####.#.#.#.#.#.#.#.#######.#.#.#.#.#.#######.#.###
#.......#...........#.......###...#.....#.....#...#...........#...#...###...#####...#####.......#...#...#...#.........#...#...#.........#...#
###########################################################################################################################################.#)"sv;

} // namespace day23
