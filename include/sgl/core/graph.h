#pragma once

#include <sgl/view/view.h>

namespace sgl {

class graph
{
public:
    graph(const sgl::view::view_t& view);
    
    sgl::view::view_t get_view();
    sgl::view::const_view_t get_view() const;
    
    void set_view(const sgl::view::view_t& view);
    
private:
    sgl::view::view_t view;
};
    
} // sgl
