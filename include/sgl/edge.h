#pragma once

#include <string>

#include <sgl/node.h>

namespace sgl {

typedef uint32_t weight_t;

class edge
{
public:
    edge(node_t first, node_t second, weight_t weight = 0);
 
    const_node_t get_first() const;
    const_node_t get_second() const;

    void set_weight(weight_t weight);
    weight_t get_weight() const;

    std::string to_string() const;
    
    bool operator<(const edge& rhs) const;
    bool operator==(const edge& rhs) const;

private:
    node_t first;
    node_t second;
    weight_t weight;
};

typedef std::shared_ptr<edge> edge_t;
typedef const std::shared_ptr<const edge> const_edge_t;
typedef std::set<edge> edge_set_t;
typedef const std::set<edge> const_edge_set_t;

} // sgl
