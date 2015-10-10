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



std::string sgl::edge::to_string() const
{
    std::string string =
        "from: " + std::to_string(this->from->get_id()) + ", "
        "to: " + std::to_string(this->to->get_id()) + ", "
        "weight: " + std::to_string(this->weight);
    
    return string;
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
