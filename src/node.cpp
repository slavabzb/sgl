#include <sgl/node.h>

using namespace sgl;



node::node(const node_id_t& node_id)
    : node_id(node_id)
{
    
}
    


node_id_t node::get_id() const
{
    return this->node_id;
}
