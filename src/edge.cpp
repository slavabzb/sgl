#include <sgl/edge.h>



sgl::edge::edge(
    const sgl::node_t& from,
    const sgl::node_t& to,
    const sgl::weight_t& weight)
        : from(nullptr)
        , to(nullptr)
        , weight(weight)
{
    if(from->get_id() == to->get_id())
    {
        throw std::invalid_argument("edge::edge: "
            "the \"from\" node is equal to the \"to\" node; node_id = " +
            std::to_string(from->get_id()));
    }

    this->from = from;
    this->to = to;
}



sgl::const_node_t sgl::edge::get_from() const
{
    return this->from;
}



sgl::const_node_t sgl::edge::get_to() const
{
    return this->to;
}



void sgl::edge::set_weight(const sgl::weight_t& weight)
{
    this->weight = weight;
}



sgl::weight_t sgl::edge::get_weight() const
{
    return this->weight;
}


bool sgl::edge::operator<(const edge& rhs) const
{
    return (*this->from < *rhs.from) && (*this->to < *rhs.to);
}
