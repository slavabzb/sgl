#include <sgl/view/simple_writer.h>
#include <sgl/view/converter.h>

#include "sgl/view/adjacency_matrix.h"



sgl::view::simple_writer::simple_writer(std::ostream& ostream)
    : ostream(ostream)
{

}



sgl::view::simple_writer::~simple_writer()
{

}



void sgl::view::simple_writer::write(sgl::view::const_view_t& view)
{
    sgl::view::type type = view->get_type();

    this->ostream << sgl::view::converter::convert(type) << ' ';

    switch(type)
    {
    case sgl::view::type::adjacency_matrix:
        this->write_adjacency_matrix(view);
        break;
    case sgl::view::type::adjacency_list:
        break;
    case sgl::view::type::edge_list:
        break;
    }
}



void sgl::view::simple_writer::write_adjacency_matrix(
    sgl::view::const_view_t& view)
{
    sgl::view::const_adjacency_matrix_t adjacency_matrix =
        std::dynamic_pointer_cast<const sgl::view::adjacency_matrix>(view);

    if(!adjacency_matrix)
    {
        throw std::invalid_argument("simple_writer::write_adjacency_matrix: "
            "can't write: the type of view is not a adjacency_matrix");
    }

    const std::size_t nodes_count = adjacency_matrix->get_nodes_count();

    this->ostream << nodes_count << '\n';
    this->ostream << adjacency_matrix->is_oriented() << ' ';
    this->ostream << adjacency_matrix->is_weighted() << '\n';

    for(sgl::node_id_t first = 0; first < nodes_count; ++first)
    {
        for(sgl::node_id_t second = 0; second < nodes_count; ++second)
        {
            this->ostream << adjacency_matrix->get_weight(first, second) << ' ';
        }

        this->ostream << '\n';
    }
}
