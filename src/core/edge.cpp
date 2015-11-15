#include <sgl/core/edge.h>



sgl::core::edge::edge(const sgl::core::node& first, const sgl::core::node& second, sgl::core::weight_t weight)
    : first(first)
    , second(second)
    , weight(weight)
{

}



const sgl::core::node& sgl::core::edge::get_first() const
{
    return this->first;
}



const sgl::core::node& sgl::core::edge::get_second() const
{
    return this->second;
}



void sgl::core::edge::set_weight(sgl::core::weight_t weight)
{
    this->weight = weight;
}



sgl::core::weight_t sgl::core::edge::get_weight() const
{
    return this->weight;
}



std::string sgl::core::edge::to_string() const
{
    std::string string =
        "first: " + std::to_string(this->first.get_id()) + ", "
        "second: " + std::to_string(this->second.get_id()) + ", "
        "weight: " + std::to_string(this->weight);

    return string;
}



bool sgl::core::edge::operator<(const edge& rhs) const
{
    bool less =
        (this->first < rhs.first) ||
        (this->second < rhs.second) ||
        (this->weight < rhs.weight);

    return less;
}



bool sgl::core::edge::operator==(const edge& rhs) const
{
    bool equal =
        (this->first == rhs.first) &&
        (this->second == rhs.second) &&
        (this->weight == rhs.weight);

    return equal;
}
