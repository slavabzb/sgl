#include <sgl/adjacency_matrix_view.h>

using namespace sgl;



adjacency_matrix_view::adjacency_matrix_view(std::size_t nodes)
    : matrix(nodes, matrix_row_t(nodes))
{

}



adjacency_matrix_view::~adjacency_matrix_view()
{
    
}



void adjacency_matrix_view::add_node(const_node_t& node)
{
    if(node->get_id() < this->matrix.size())
    {
        
    } 
}



void adjacency_matrix_view::add_edge(const_edge_t& edge)
{
    
}
    


void remove_node(const_node_t& node)
{
    
}



void adjacency_matrix_view::remove_edge(const_edge_t& edge)
{
    
}
