#pragma once

#include <vector>
#include <sgl/view.h>

namespace sgl {
    
    
    
class adjacency_matrix_view: public view
{
    typedef std::vector<node_id_t> matrix_row_t;
    typedef std::vector<matrix_row_t> matrix_t;
    
public:
    adjacency_matrix_view(std::size_t nodes = 0);
    virtual ~adjacency_matrix_view();
    
    virtual void add_node() override;
    virtual void add_edge(const_edge_t& edge) override;
    
    virtual void remove_node(const node_t& node) override;
    virtual void remove_edge(const_edge_t& edge) override;
	
#ifndef TESTS
private:
#endif
    matrix_t matrix;
};



typedef std::shared_ptr<adjacency_matrix_view> adjacency_matrix_view_t;



} // sgl
