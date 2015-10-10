#pragma once

#include <sgl/view/view.h>

namespace sgl {
namespace view {

class writer
{
public:
    virtual ~writer() {}

    virtual void write(const_view_t& view) = 0;
};

typedef std::shared_ptr<writer> writer_t;

} // view
} // sgl
