#pragma once

#include <sgl/node.h>

namespace sgl {

typedef uint32_t weight_t;

class edge
{
public:
    edge(const node_t& from, const node_t& to, const weight_t& weight = 0);
    
    const_node_t get_from() const;
    const_node_t get_to() const;
    
    void set_weight(const weight_t& weight);
    weight_t get_weight() const;
    
    bool operator< (const edge& rhs) const;
    
private:
    node_t from;
    node_t to;
    weight_t weight;
};

typedef std::set<edge> edge_set_t;
typedef std::shared_ptr<edge> edge_t;
typedef const std::shared_ptr<const edge> const_edge_t;

} // sgl
