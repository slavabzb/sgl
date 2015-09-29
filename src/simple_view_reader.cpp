#include <sgl/simple_view_reader.h>
#include <sgl/adjacency_matrix_view.h>
#include <iostream>



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

		std::size_t ignore = 0;
        for(std::size_t row = 0; row < nodes; ++row)
        {
			this->istream.ignore(++ignore, '\n');
			std::cout << "\nignore: " << ignore;
			
            view->add_node();

            for(std::size_t column = 0; column < nodes; ++column)
            {
                sgl::weight_t weight;
				
                this->istream >> weight;

				std::cout << "\nweight: " << weight;
				
				if(weight > 0)
				{
					sgl::node_t from = std::make_shared<sgl::node>(row);
					sgl::node_t to = std::make_shared<sgl::node>(column);
					sgl::edge_t edge = std::make_shared<sgl::edge>(from,
						to, weight);
					
					view->add_edge(edge);
				}
            }
        }
    }
	
	return view;
}
