#include <sgl/core/node.h>

#include <sgl/io/simple_writer.h>
#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/edge_list.h>
#include <sgl/details/converter.h>



sgl::io::simple_writer::simple_writer(std::ostream& ostream)
    : ostream(ostream)
{

}



sgl::io::simple_writer::~simple_writer()
{

}



void sgl::io::simple_writer::write(sgl::view::const_view_t& view)
{
    sgl::view::type type = view->get_type();

    this->ostream << sgl::details::converter::convert(type) << ' ';

    switch(type)
    {
    case sgl::view::type::adjacency_matrix:
        this->write_adjacency_matrix(view);
        break;
    case sgl::view::type::adjacency_list:
        this->write_adjacency_list(view);
        break;
    case sgl::view::type::edge_list:
        this->write_edge_list(view);
        break;
    }
}



void sgl::io::simple_writer::write_adjacency_matrix(sgl::view::const_view_t& view)
{
    sgl::view::const_adjacency_matrix_t adjacency_matrix =
        std::dynamic_pointer_cast<const sgl::view::adjacency_matrix>(view);

    if(!adjacency_matrix)
    {
        throw std::invalid_argument("simple_writer::write_adjacency_matrix: "
            "can't write: the type of view is not a adjacency_matrix");
    }

    const std::size_t nodes_count = adjacency_matrix->get_nodes().size();

    this->ostream << nodes_count << '\n';
    this->ostream << adjacency_matrix->is_oriented() << ' ';
    this->ostream << adjacency_matrix->is_weighted() << '\n';

    for(sgl::core::node_id_t first = 0; first < nodes_count; ++first)
    {
        for(sgl::core::node_id_t second = 0; second < nodes_count - 1; ++second)
        {
            this->ostream << adjacency_matrix->get_edge_weight(first, second) << ' ';
        }

        this->ostream << adjacency_matrix->get_edge_weight(first, nodes_count - 1);
        this->ostream << '\n';
    }
}



void sgl::io::simple_writer::write_adjacency_list(
    sgl::view::const_view_t& view)
{
    sgl::view::const_adjacency_list_t adjacency_list =
        std::dynamic_pointer_cast<const sgl::view::adjacency_list>(view);

    if(!adjacency_list)
    {
        throw std::invalid_argument("simple_writer::write_adjacency_list: "
            "can't write: the type of view is not a adjacency_list");
    }

    sgl::core::node_set_t nodes = adjacency_list->get_nodes();

    this->ostream << nodes.size() << '\n';
    this->ostream << adjacency_list->is_oriented() << ' ';
    this->ostream << adjacency_list->is_weighted() << '\n';

    for(const sgl::core::node& node : nodes)
    {
        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes =
            adjacency_list->get_adjacency_nodes(node);

        if(adjacency_nodes.empty())
        {
            this->ostream << '\n';
        }
        else
        {
            for(const sgl::view::adjacency_list::edge_info_t& edge_info : adjacency_nodes)
            {
                this->ostream << edge_info.first.get_id();

                if(adjacency_list->is_weighted())
                {
                    this->ostream << ' ' << edge_info.second;
                }

                if(edge_info != *(--adjacency_nodes.end()))
                {
                    this->ostream << ' ';
                }
            }

            this->ostream << '\n';
        }
    }
}



void sgl::io::simple_writer::write_edge_list(sgl::view::const_view_t& view)
{
    sgl::view::const_edge_list_t edge_list = std::dynamic_pointer_cast<const sgl::view::edge_list>(view);

    if(!edge_list)
    {
        throw std::invalid_argument("simple_writer::write_edge_list: "
            "can't write: the type of view is not a edge_list");
    }

    sgl::core::node_set_t nodes = edge_list->get_nodes();
    sgl::core::edge_set_t edges = edge_list->get_edges();

    this->ostream << nodes.size() << ' ';
    this->ostream << edges.size() << '\n';

    this->ostream << edge_list->is_oriented() << ' ';
    this->ostream << edge_list->is_weighted() << '\n';

    for(const sgl::core::edge& edge : edges)
    {
        this->ostream << edge.get_first().get_id() << ' ' << edge.get_second().get_id();

        if(edge_list->is_weighted())
        {
            this->ostream << ' ' << edge.get_weight();
        }

        this->ostream << '\n';
    }
}
