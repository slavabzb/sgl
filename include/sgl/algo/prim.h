#pragma once

#include <sgl/view/adjacency_list.h>

namespace sgl {
namespace algo {

/**
 * Prim's algorithm is a greedy algorithm that finds a minimum spanning tree
 * for a weighted undirected graph.
 * 
 * @param adjacency_list - an adjacency list view that contains source graph info
 * @return Minimum spanning tree, if adjacency_list is NOT oriented and is weighted;
 * nullptr otherwise.
 */
sgl::view::view_t prim(sgl::view::const_adjacency_list_t adjacency_list);

} // algo
} // sgl
