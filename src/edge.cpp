#include <sgl/edge.h>

using namespace sgl;



edge::edge(const node_t& from, const node_t& to, const weight_t& weight)
    : from(from)
    , to(to)
    , weight(weight)
{

}



const_node_t edge::get_from() const
{
    return this->from;
}



const_node_t edge::get_to() const
{
    return this->to;
}



void edge::set_weight(const weight_t& weight)
{
    this->weight = weight;
}
