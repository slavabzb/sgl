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

    using matrix_row_t = std::vector<node_id_t>;
    using matrix_t = std::vector<matrix_row_t>;

public:
    adjacency_matrix(
        std::size_t nodes = 0,
        bool oriented = false,
        bool weighted = false);
    
    virtual ~adjacency_matrix();

    virtual void add_node() override;
    virtual void add_edge(const edge& edge) override;

    virtual void remove_node(const node& node) override;
    virtual void remove_edge(const edge& edge) override;
    
    virtual type get_type() const override;
    virtual node_set_t get_nodes() const override;
    virtual edge_set_t get_edges() const override;
    
    virtual bool exists(const edge& edge) const override;
    virtual bool exists(const node& node) const override;
    
    weight_t get_weight(const node& first, const node& second) const;

private:
    bool in_range(node_id_t from, node_id_t to) const;
    
private:
    matrix_t matrix;
};

typedef std::shared_ptr<adjacency_matrix> adjacency_matrix_t;
typedef const std::shared_ptr<const adjacency_matrix> const_adjacency_matrix_t;

} // view
} // sgl
