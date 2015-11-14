#pragma once

#include <cstdint>
#include <vector>

namespace disjoint
{
    class dsu
    {
        typedef uint32_t value_type;
        typedef std::vector<value_type> container_type;
        typedef container_type::size_type size_type;

    public:
        dsu(size_type size);

        value_type find(value_type value);
        void unite(value_type first, value_type second);
        size_type size() const;

    private:
        container_type parent;
        container_type rank;
    };
} // disjoint
