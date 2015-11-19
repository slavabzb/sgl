/**
 * @cond
 *
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
 *
 * @endcond
 */

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
         * 
         * @ingroup core
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

            /**
             * Compares the edge and rhs.
             * 
             * @param rhs - an edge to be compared with.
             * @return Flag; true, if the first node or the second node or the weight of the node is less than rhs ones.
             */
            bool operator<(const edge& rhs) const;
            
            /**
             * Compares the edge and rhs.
             * 
             * @param rhs - an edge to be compared with.
             * @return Flag; true, if the first node and the second node and the weight of the node is equal to rhs ones.
             */
            bool operator==(const edge& rhs) const;

        private:
            node first;
            node second;
            weight_t weight;
        };

        typedef std::set<edge> edge_set_t; ///< Set of edges.
    } // core
} // sgl
