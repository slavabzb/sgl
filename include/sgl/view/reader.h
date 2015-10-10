#pragma once

#include <sgl/view/view.h>

namespace sgl {
namespace view {

class reader
{
public:
    virtual ~reader() {}

    virtual view_t read() = 0;
};

typedef std::shared_ptr<reader> reader_t;

} // view
} // sgl
