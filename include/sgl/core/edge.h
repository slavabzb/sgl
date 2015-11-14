#pragma once

#include <string>
#include <sgl/core/node.h>

namespace sgl
{
    namespace core
    {
        typedef uint32_t weight_t; ///< Weight of edge.

        /**
         * Graph edge.
         * Represents an edge of the graph with two nodes and weight.
         */
        class edge
        {
        public:
            /**
             * Constructor.
             * Constructs an edge with given nodes end weight.
             * 
             * @param first - first node;
             * @param second - second node;
             * @param weight - weight of the edge.
             */
            edge(const node& first, const node& second, weight_t weight = 0);

            /**
             * Retrieves the first node of the edge.
             * 
             * @return The first node of the edge.
             */
            const node& get_first() const;

            /**
             * Retrieves the second node of the edge.
             * 
             * @return The second node of the edge.
             */
            const node& get_second() const;

            /**
             * Assigns new weight to the edge.
             * 
             * @param weight - new weight of the edge.
             */
            void set_weight(weight_t weight);

            /**
             * Retrieves weight of the edge.
             * 
             * @return Weight of the edge.
             */
            weight_t get_weight() const;

            /**
             * Converts edge to the string.
             * 
             * @return String which represents the edge.
             */
            std::string to_string() const;

            // operators
            bool operator<(const edge& rhs) const;
            bool operator==(const edge& rhs) const;

        private:
            node first;
            node second;
            weight_t weight;
        };

        typedef std::set<edge> edge_set_t; ///< Set of edges.
    } // core
} // sgl
