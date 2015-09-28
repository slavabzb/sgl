#pragma once

#include <cstdint>
#include <memory>
#include <set>

namespace sgl {

typedef uint32_t node_id_t;

class node
{
public:
    node(const node_id_t& node_id);
    
    node_id_t get_id() const;
    
    bool operator<(const node& rhs) const;
	
private:
    node_id_t node_id;
};

typedef std::set<node> node_set_t;
typedef std::shared_ptr<node> node_t;
typedef const std::shared_ptr<const node> const_node_t;

} // sgl
