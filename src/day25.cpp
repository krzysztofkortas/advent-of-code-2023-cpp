#include "inputs/day25.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#if defined(__GNUC__) && !defined(__clang__)
	#pragma GCC diagnostic push 
	#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/graph/adjacency_list.hpp>
#if defined(__GNUC__) && !defined(__clang__)
	#pragma GCC diagnostic pop
#endif
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/property_map/property_map.hpp>
#include <gtest/gtest.h>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;
using std::operator""sv;

using Graph = boost::
	labeled_graph<boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>, std::string>;

Graph buildGraph(std::string_view input)
{
	Graph graph;
	for (auto&& line : input | vw::split('\n'))
	{
		const auto vertexAndNeighbors =
			line | vw::split(": "sv) | rng::to<std::vector<std::string>>();
		assert(vertexAndNeighbors.size() == 2);
		const std::string& vertexName = vertexAndNeighbors[0];
		boost::add_vertex(vertexName, graph);
		for (const std::string& neighborName :
			 vertexAndNeighbors[1] | vw::split(' ') | vw::transform(rng::to<std::string>()))
		{
			boost::add_vertex(neighborName, graph);
			boost::add_edge_by_label(vertexName, neighborName, graph);
		}
	}

	return graph;
}

int64_t solve(std::string_view input)
{
	const Graph graph = buildGraph(input);
	std::map<int, bool> parity;
	const boost::associative_property_map parities(parity);
	const auto weightMap = boost::make_static_property_map<Graph::edge_descriptor>(1);
	boost::stoer_wagner_min_cut(graph, weightMap, boost::parity_map(parities));

	return rng::count(parity | vw::values, false) * rng::count(parity | vw::values, true);
}

TEST(day25, test)
{
	EXPECT_EQ(solve(day25::sample), 54);
	EXPECT_EQ(solve(day25::input), 544523);
}

} // anonymous namespace
