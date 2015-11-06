#include <sstream>

#include <sgl/view/simple_reader.h>
#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/edge_list.h>
#include <sgl/details/converter.h>


sgl::view::simple_reader::simple_reader(std::istream& istream)
    : istream(istream)
{

}



sgl::view::simple_reader::~simple_reader()
{

}



sgl::view::view_t sgl::view::simple_reader::read()
{
    sgl::view::view_t view;

    char char_type = 0;
    this->istream >> char_type;

    sgl::view::type type = sgl::details::converter::convert(char_type);

    switch(type)
    {
    case sgl::view::type::adjacency_matrix:
        this->read_adjacency_matrix(view);
        break;
    case sgl::view::type::adjacency_list:
        this->read_adjacency_list(view);
        break;
    case sgl::view::type::edge_list:
        this->read_edge_list(view);
        break;
    }

    return view;
}



void sgl::view::simple_reader::read_adjacency_matrix(sgl::view::view_t& view)
{
    std::size_t nodes = 0;
    this->istream >> nodes;

    bool oriented = false;
    this->istream >> oriented;

    bool weighted = false;
    this->istream >> weighted;

    view = std::make_shared<sgl::view::adjacency_matrix>(
        nodes, oriented, weighted);

    for(std::size_t row = 0; row < nodes; ++row)
    {
        for(std::size_t column = 0; column < nodes; ++column)
        {
            sgl::weight_t weight;
            this->istream >> weight;

            sgl::edge edge(row, column, weight);
            if(!view->exists(edge))
            {
                view->add_edge(edge);
            }
        }
    }
}



void sgl::view::simple_reader::read_adjacency_list(sgl::view::view_t& view)
{
    std::size_t nodes = 0;
    this->istream >> nodes;

    bool oriented = false;
    this->istream >> oriented;

    bool weighted = false;
    this->istream >> weighted;

    view = std::make_shared<sgl::view::adjacency_list>(oriented, weighted);

    this->istream.ignore();

    for(sgl::node_id_t first = 0; first < nodes; ++first)
    {
        std::string adjacency_info;
        std::getline(this->istream, adjacency_info);

        if(!adjacency_info.empty())
        {
            std::stringstream stringstream;
            stringstream.str(adjacency_info);

            while(!stringstream.eof())
            {
                sgl::node_id_t second = 0;
                stringstream >> second;

                sgl::weight_t weight = 0;
                if(view->is_weighted())
                {
                    stringstream >> weight;
                }

                view->add_edge(sgl::edge(first, second, weight));
            }
        }
        else
        {
            view->add_node(first);
        }
    }
}



void sgl::view::simple_reader::read_edge_list(sgl::view::view_t& view)
{
    std::size_t nodes = 0;
    this->istream >> nodes;

    std::size_t edges = 0;
    this->istream >> edges;

    bool oriented = false;
    this->istream >> oriented;

    bool weighted = false;
    this->istream >> weighted;

    view = std::make_shared<sgl::view::edge_list>(oriented, weighted);

    for(sgl::node_id_t node = 0; node < nodes; ++node)
    {
        view->add_node(node);
    }

    this->istream.ignore();

    for(std::size_t iedge = 0; iedge < edges; ++iedge)
    {
        std::string edge_info;
        std::getline(this->istream, edge_info);

        if(!edge_info.empty())
        {
            std::stringstream stringstream;
            stringstream.str(edge_info);

            while(!stringstream.eof())
            {
                sgl::node_id_t first = 0;
                stringstream >> first;

                sgl::node_id_t second = 0;
                stringstream >> second;

                sgl::weight_t weight = 0;
                if(view->is_weighted())
                {
                    stringstream >> weight;
                }

                view->add_edge(sgl::edge(first, second, weight));
            }
        }
    }
}
