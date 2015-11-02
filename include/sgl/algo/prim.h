#pragma once

#include <sgl/view/adjacency_list.h>

namespace sgl {

class algo
{
public:
    static sgl::view::view_t prim(sgl::view::const_adjacency_list_t adjacency_list);
};    

} // sgl
