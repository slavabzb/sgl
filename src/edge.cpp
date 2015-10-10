#include <sgl/edge.h>



sgl::edge::edge(
    sgl::node_t from,
    sgl::node_t to,
    sgl::weight_t weight)
        : from(from)
        , to(to)
        , weight(weight)
{

}



sgl::const_node_t sgl::edge::get_from() const
{
    return this->from;
}



sgl::const_node_t sgl::edge::get_to() const
{
    return this->to;
}



void sgl::edge::set_weight(sgl::weight_t weight)
{
    this->weight = weight;
}



sgl::weight_t sgl::edge::get_weight() const
{
    return this->weight;
}


bool sgl::edge::operator<(const edge& rhs) const
{
    bool less =
        (*this->from < *rhs.from) ||
        (*this->to < *rhs.to) ||
        (this->weight < rhs.weight);

    return less;
}



bool sgl::edge::operator==(const edge& rhs) const
{
    bool equal =
        (*this->from == *rhs.from) &&
        (*this->to == *rhs.to) &&
        (this->weight == rhs.weight);

    return equal;
}
