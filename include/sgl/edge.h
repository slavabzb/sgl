#pragma once

#include <sgl/node.h>

namespace sgl {

typedef uint32_t weight_t;

class edge
{
public:
    edge(const node& from, const node& to, const weight_t& weight = 0);

    const node& get_from() const;
    const node& get_to() const;

    void set_weight(const weight_t& weight);
    weight_t get_weight() const;

    bool operator<(const edge& rhs) const;
	bool operator==(const edge& rhs) const;

private:
    node from;
    node to;
    weight_t weight;
};

typedef std::set<edge> edge_set_t;

} // sgl
