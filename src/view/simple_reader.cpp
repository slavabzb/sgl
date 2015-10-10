#include <sgl/view/simple_reader.h>
#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/converter.h>
#include <iostream>


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

    sgl::view::type type = sgl::view::converter::convert(char_type);

    switch(type)
    {
    case sgl::view::type::adjacency_matrix:
        this->read_adjacency_matrix(view);
        break;
    case sgl::view::type::adjacency_list:
        break;
    case sgl::view::type::edge_list:
        break;
    }

    return view;
}



void sgl::view::simple_reader::read_adjacency_matrix(sgl::view::view_t& view)
{
    std::size_t nodes = 0;
    this->istream >> nodes;

    view = std::make_shared<sgl::view::adjacency_matrix>(nodes);

    bool oriented = false;
    this->istream >> oriented;
    view->set_oriented(oriented);

    bool weighted = false;
    this->istream >> weighted;
    view->set_weighted(weighted);

    for(std::size_t row = 0; row < nodes; ++row)
    {
        for(std::size_t column = 0; column < nodes; ++column)
        {
            sgl::weight_t weight;
            this->istream >> weight;

            sgl::node_t from = std::make_shared<sgl::node>(row);
            sgl::node_t to = std::make_shared<sgl::node>(column);
            sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);

            view->add_edge(edge);
        }
    }
}
