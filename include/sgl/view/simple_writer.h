#pragma once

#include <ostream>
#include <sgl/view/writer.h>

namespace sgl {
namespace view {

class simple_writer: public writer
{
public:
    simple_writer(std::ostream& ostream);
    virtual ~simple_writer();

    virtual void write(const_view_t& view) override;

private:
    void write_adjacency_matrix(const_view_t& view);
    
private:
    std::ostream& ostream;
};

typedef std::shared_ptr<simple_writer> simple_writer_t;

} // view
} // sgl
