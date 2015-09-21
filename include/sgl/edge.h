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
    
private:
    node_t from;
    node_t to;
    weight_t weight;
};



typedef std::shared_ptr<edge> edge_t;
typedef std::shared_ptr<const edge> const_edge_t;



} // sgl
