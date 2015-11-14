#pragma once

#include <cstdint>
#include <memory>
#include <set>
#include <string>

namespace sgl
{
    namespace core
    {
        typedef uint32_t node_id_t; ///< Id of node.

        /**
         * Node.
         * Represents a node of the graph.
         */
        class node
        {
        public:
            /**
             * Constructor.
             * Constructs a node with given id.
             * 
             * @param node_id - id of the node.
             */
            node(node_id_t node_id = 0);

            /**
             * Retrieves id of the node.
             * 
             * @return Id of the node.
             */
            node_id_t get_id() const;

            /**
             * Converts node to string.
             * 
             * @return String which represents the node.
             */
            std::string to_string() const;

            // operators
            bool operator<(const node& rhs) const;
            bool operator==(const node& rhs) const;
            bool operator!=(const node& rhs) const;

        private:
            node_id_t node_id;
        };

        typedef std::set<node> node_set_t; ///< Set of nodes.
    } // core
} // sgl
