#pragma once

#include <istream>
#include <sgl/view/reader.h>

namespace sgl {
namespace view {

class simple_reader: public reader
{
public:
    simple_reader(std::istream& istream);
    virtual ~simple_reader();

    virtual view_t read() override;

private:
    void read_adjacency_matrix(view_t& view);
    
private:
    std::istream& istream;
};

typedef std::shared_ptr<simple_reader> simple_reader_t;

} // view
} // sgl
