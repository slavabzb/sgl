#pragma once

#include <sgl/view.h>

namespace sgl {

class view_source
{
public:
    virtual view_t get() = 0;
    virtual void store(const_view_t& view) = 0;
};

} // sgl
