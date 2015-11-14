#include <sgl/disjoint/dsu.h>



disjoint::dsu::dsu(size_type size)
    : parent(size, 0)
    , rank(size, 0)
{
    for(size_type i = 0; i < size; ++i)
    {
        this->parent[i] = i;
    }
}



disjoint::dsu::value_type disjoint::dsu::find(value_type value)
{
    if(value == this->parent[value])
    {
        return value;
    }

    return this->parent[value] = this->find(this->parent[value]);
}



void disjoint::dsu::unite(value_type first, value_type second)
{
    first = this->find(first);
    second = this->find(second);

    if(first != second)
    {
        if(this->rank[first] < this->rank[second])
        {
            std::swap(first, second);
        }

        this->parent[second] = first;

        if(this->rank[first] == this->rank[second])
        {
            ++this->rank[first];
        }
    }
}



disjoint::dsu::size_type disjoint::dsu::size() const
{
    return this->parent.size();
}
