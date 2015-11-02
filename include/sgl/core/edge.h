#pragma once

#include <string>

#include <sgl/core/node.h>

namespace sgl {

typedef uint32_t weight_t;

class edge
{
public:
    edge(const node& first, const node& second, weight_t weight = 0);
 
    const node& get_first() const;
    const node& get_second() const;

    void set_weight(weight_t weight);
    weight_t get_weight() const;

    std::string to_string() const;
    
    bool operator<(const edge& rhs) const;
    bool operator==(const edge& rhs) const;

private:
    node first;
    node second;
    weight_t weight;
};

typedef std::set<edge> edge_set_t;

} // sgl
