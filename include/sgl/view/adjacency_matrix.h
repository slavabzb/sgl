#pragma once

#include <vector>
#include <sgl/view.h>

class adjacency_matrix_view_test;

namespace sgl {

class adjacency_matrix_view: public view
{
#ifdef TESTS
	friend class ::adjacency_matrix_view_test;
#endif

    typedef std::vector<node_id_t> matrix_row_t;
    typedef std::vector<matrix_row_t> matrix_t;

public:
    adjacency_matrix_view(std::size_t nodes = 0);
    virtual ~adjacency_matrix_view();

    virtual void add_node() override;
    virtual void add_edge(const edge& edge) override;

    virtual void remove_node(const node& node) override;
    virtual void remove_edge(const edge& edge) override;

    virtual node_set_t get_nodes() override;
    virtual edge_set_t get_edges() override;

private:
    matrix_t matrix;
};

typedef std::shared_ptr<adjacency_matrix_view> adjacency_matrix_view_t;

} // sgl
