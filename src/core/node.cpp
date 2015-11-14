#include <sgl/core/node.h>



sgl::core::node::node(sgl::core::node_id_t node_id)
    : node_id(node_id)
{

}



sgl::core::node_id_t sgl::core::node::get_id() const
{
    return this->node_id;
}



std::string sgl::core::node::to_string() const
{
    std::string string = "node_id: " + std::to_string(this->node_id);

    return string;
}



bool sgl::core::node::operator<(const sgl::core::node& rhs) const
{
    return this->node_id < rhs.node_id;
}



bool sgl::core::node::operator==(const sgl::core::node& rhs) const
{
    return this->node_id == rhs.node_id;
}



bool sgl::core::node::operator!=(const sgl::core::node& rhs) const
{
    return this->node_id != rhs.node_id;
}
