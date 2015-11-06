#pragma once

#include <sgl/view/adjacency_list.h>

namespace sgl
{
	struct algo
	{
		/**
		 * @brief Prim's algorithm finds a minimum spanning tree for a weighted undirected graph.
		 *
		 * @param adjacency_list - an adjacency list view that contains source graph info
		 * @return Minimum spanning tree, if adjacency_list is NOT oriented and IS weighted;
		 * nullptr otherwise.
		 */
		static sgl::view::view_t prim(sgl::view::const_adjacency_list_t adjacency_list);
	}; // algo
} // sgl
