#pragma once

#include <cstdint>
#include <memory>

namespace sgl {

typedef uint32_t node_id_t;



class node
{
public:
    node(const node_id_t& node_id);
    
    node_id_t get_id() const;
    
private:
    node_id_t node_id;
};



typedef std::shared_ptr<node> node_t;
typedef std::shared_ptr<const node> const_node_t;



} // sgl
