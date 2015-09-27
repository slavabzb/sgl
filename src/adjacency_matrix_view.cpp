#include <algorithm>
#include <sgl/adjacency_matrix_view.h>

namespace sgl {

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
    this->matrix.erase(this->matrix.begin() + node->get_id());
    
    std::for_each(this->matrix.begin(), this->matrix.end(),
        [&](matrix_row_t& row)
        {
            row.erase(row.begin() + node->get_id());
        });
}



void adjacency_matrix_view::remove_edge(const_edge_t& edge)
{
    
}

} // sgl
