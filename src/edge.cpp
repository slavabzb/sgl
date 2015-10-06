#include <sgl/edge.h>



sgl::edge::edge(
    const sgl::node& from,
    const sgl::node& to,
    const sgl::weight_t& weight)
        : from(from)
        , to(to)
        , weight(weight)
{
    if(this->from.get_id() == this->to.get_id())
    {
        throw std::invalid_argument("edge::edge: "
            "the \"from\" node is equal to the \"to\" node; node_id = " +
            std::to_string(from.get_id()));
    }
}



const sgl::node& sgl::edge::get_from() const
{
    return this->from;
}



const sgl::node& sgl::edge::get_to() const
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
	bool less =
		(this->from < rhs.from) ||
		(this->to < rhs.to) ||
		(this->weight < rhs.weight);

    return less;
}



bool sgl::edge::operator==(const edge& rhs) const
{
	bool equal =
		(this->from == rhs.from) &&
		(this->to == rhs.to) &&
		(this->weight == rhs.weight);

    return equal;
}
