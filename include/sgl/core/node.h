#pragma once

#include <cstdint>
#include <memory>
#include <set>
#include <string>

namespace sgl {

typedef uint32_t node_id_t;

class node
{
public:
    node(node_id_t node_id = 0);

    node_id_t get_id() const;
    std::string to_string() const;

    bool operator<(const node& rhs) const;
    bool operator==(const node& rhs) const;
	bool operator!=(const node& rhs) const;

private:
    node_id_t node_id;
};

typedef std::set<node> node_set_t;

} // sgl
