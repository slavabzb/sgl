/**
 * Copyright (c) 2015-2016
 * 
 * Bezborodov, V.A. vyacheslav.bezborodov@gmail.com
 * Golodov, V.A. avaksa@gmail.com
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

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
