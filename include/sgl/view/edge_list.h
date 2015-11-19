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

#include <map>
#include <set>

#include <sgl/view/view.h>

#ifdef TESTS
class edge_list_test;
#endif

namespace sgl
{
    namespace view
    {
        /**
         * @ref edge_list
         * @ingropu view
         */
        class edge_list: public view
        {
        #ifdef TESTS
            friend class ::edge_list_test;
        #endif

            using base_t = view;
            
        public:
            /**
             * Constructor.
             * Constructs an edge_list using given properties.
             * 
             * @param oriented - a flag; true, if graph is oriented, false otherwise,
             * @param weighted - a flag; true, if graph is weighted, false otherwise.
             */
            edge_list(bool oriented = false, bool weighted = false);
            
            /**
             * Copy constructor.
             * Constructs an edge_list using other as pattern.
             * 
             * @param other - a view to be constructed from.
             */
            edge_list(const view& other);
            
            virtual ~edge_list();

            virtual void add_node(const sgl::core::node& node) override;
            virtual void add_edge(const sgl::core::edge& edge) override;

            virtual void remove_node(const sgl::core::node& node) override;
            virtual void remove_edge(const sgl::core::edge& edge) override;

            virtual type get_type() const override;
            virtual sgl::core::node_set_t get_nodes() const override;
            virtual sgl::core::edge_set_t get_edges() const override;

            virtual bool exists(const sgl::core::edge& edge) const override;
            virtual bool exists(const sgl::core::node& node) const override;

            /**
             * Assigns rhs to the edge_list.
             * 
             * @param rhs - an edge_list to be assigned with.
             * @return The edge_list.
             * @throw std::invalid_argument if oriented/weighted flags are mismatched.
             */
            edge_list& operator=(const edge_list& rhs);
            
            /**
             * Assigns ths to the edge_list.
             * 
             * @param rhs - an edge_list to be assigned with.
             * @return The edge_list.
             * @throw std::invalid_argument if oriented/weighted flags are mismatched.
             */
            edge_list& operator=(const view& rhs);

        private:
            sgl::core::edge_set_t edges;
            sgl::core::node_set_t nodes;
        };

        typedef std::shared_ptr<edge_list> edge_list_t;                     ///< edge_list type.
        typedef const std::shared_ptr<const edge_list> const_edge_list_t;   ///< const edge_list type.

    } // view
} // sgl
