#pragma once

#include <map>

namespace sgl {
namespace view {

enum class type: int8_t
{
	unknown,
	adjacency_matrix,
	adjacency_list,
	edge_list
};

} // view
} // sgl
