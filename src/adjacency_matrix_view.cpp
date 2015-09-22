#include <algorithm>
#include <sgl/adjacency_matrix_view.h>

using namespace sgl;



adjacency_matrix_view::adjacency_matrix_view(std::size_t nodes)
    : matrix(nodes, matrix_row_t(nodes))
{

}



adjacency_matrix_view::~adjacency_matrix_view()
{
    
}



void adjacency_matrix_view::add_node()
{	
    std::for_each(this->matrix.begin(), this->matrix.end(),
        [](matrix_row_t& row)
        {
                row.push_back(0);
        });

    this->matrix.push_back(matrix_row_t(this->matrix.size() + 1, 0));
}



void adjacency_matrix_view::add_edge(const_edge_t& edge)
{
    
}
    


void adjacency_matrix_view::remove_node(const node_t& node)
{
    node_id_t row_id = 0;
    std::remove_if(this->matrix.begin(), this->matrix.end(),
        [&](matrix_row_t& row) -> bool
        {
                if(row_id++ == node->get_id())
                {
                        return true;
                }
        });
		
    std::for_each(this->matrix.begin(), this->matrix.end(),
        [&node](matrix_row_t& row)
        {
            node_id_t column_id = 0;
            std::remove_if(row.begin(), row.end(),
                [&](node_id_t& node_id)
                {
                    if(column_id++ == node->get_id())
                    {
                        return true;
                    }
                });
        });
}



void adjacency_matrix_view::remove_edge(const_edge_t& edge)
{
    
}
