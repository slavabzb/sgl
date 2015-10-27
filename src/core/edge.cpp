#include <sgl/core/edge.h>



sgl::edge::edge(
    const sgl::node& first,
    const sgl::node& second,
    sgl::weight_t weight)
        : first(first)
        , second(second)
        , weight(weight)
{

}



const sgl::node& sgl::edge::get_first() const
{
    return this->first;
}



const sgl::node& sgl::edge::get_second() const
{
    return this->second;
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
        "from: " + std::to_string(this->first.get_id()) + ", "
        "to: " + std::to_string(this->second.get_id()) + ", "
        "weight: " + std::to_string(this->weight);

    return string;
}



bool sgl::edge::operator<(const edge& rhs) const
{
    bool less =
        (this->first < rhs.first) ||
        (this->second < rhs.second) ||
        (this->weight < rhs.weight);

    return less;
}



bool sgl::edge::operator==(const edge& rhs) const
{
    bool equal =
        (this->first == rhs.first) &&
        (this->second == rhs.second) &&
        (this->weight == rhs.weight);

    return equal;
}
