#include <sgl/core/node.h>



sgl::node::node(sgl::node_id_t node_id)
    : node_id(node_id)
{

}



sgl::node_id_t sgl::node::get_id() const
{
    return this->node_id;
}



std::string sgl::node::to_string() const
{
    std::string string = "node_id: " + std::to_string(this->node_id);

    return string;
}



bool sgl::node::operator<(const sgl::node& rhs) const
{
    return this->node_id < rhs.node_id;
}



bool sgl::node::operator==(const sgl::node& rhs) const
{
    return this->node_id == rhs.node_id;
}
