#include <sgl/view/simple_writer.h>
#include <sgl/view/converter.h>



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
    std::size_t nodes_count = view->get_nodes().size();
    this->ostream << nodes_count << ' ';
    // why?
    this->ostream << '0' << '\n';

    sgl::edge_set_t edges = view->get_edges();

    std::size_t line_limit = 0;
    for(sgl::edge_set_t::const_iterator it = edges.begin();
        it != edges.end(); ++it)
    {
        this->ostream << it->get_weight() << ' ';
        
        if(line_limit == nodes_count)
        {
            this->ostream << '\n';
            line_limit = 0;
        }
    }
}
