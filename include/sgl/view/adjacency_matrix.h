#pragma once

#include <vector>
#include <sgl/view/view.h>

class adjacency_matrix_test;

namespace sgl {
namespace view {

class adjacency_matrix: public view
{
#ifdef TESTS
    friend class ::adjacency_matrix_test;
#endif

    typedef std::vector<node_id_t> matrix_row_t;
    typedef std::vector<matrix_row_t> matrix_t;

public:
    adjacency_matrix(std::size_t nodes = 0);
    virtual ~adjacency_matrix();

    virtual void add_node() override;
    virtual void add_edge(const_edge_t edge) override;

    virtual void remove_node(const_node_t node) override;
    virtual void remove_edge(const_edge_t edge) override;

    virtual const_node_set_t get_nodes() const override;
    virtual const_edge_set_t get_edges() const override;
    
    virtual type get_type() const override;
    
    virtual bool exists(const_edge_t edge) const override;
    virtual bool exists(const_node_t node) const override;

private:
    bool in_range(node_id_t from, node_id_t to) const;
    
private:
    matrix_t matrix;
};

typedef std::shared_ptr<adjacency_matrix> adjacency_matrix_t;
typedef const std::shared_ptr<const adjacency_matrix> const_adjacency_matrix_t;

} // view
} // sgl
