#include <sgl/simple_view_reader.h>
#include <sgl/adjacency_matrix_view.h>



sgl::simple_view_reader::simple_view_reader(std::istream& istream)
	: istream(istream)
{

}



sgl::simple_view_reader::~simple_view_reader()
{

}



sgl::view_t sgl::simple_view_reader::read()
{
    sgl::view_t view;

    char type = ' ';
    this->istream >> type;

    if(type == 'C')
    {
        std::size_t nodes = 0;
        this->istream >> nodes;

		view = std::make_shared<sgl::adjacency_matrix_view>(nodes);

        bool W = false;
        this->istream >> W;

        for(std::size_t row = 0; row < nodes; ++row)
        {
            for(std::size_t column = 0; column < nodes; ++column)
            {
				sgl::weight_t weight;
				this->istream >> weight;

				if(column > row)
				{
					if(weight > 0)
					{
						sgl::node from(row);
						sgl::node to(column);
						sgl::edge edge(from, to, weight);

						view->add_edge(edge);
					}
				}
            }
        }
    }

	return view;
}
