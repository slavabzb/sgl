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

#include <map>
#include <set>

#include <sgl/view/view.h>

class adjacency_list_test;

namespace sgl
{
    namespace view
    {
        class adjacency_list: public view
        {
        #ifdef TESTS
            friend class ::adjacency_list_test;
        #endif

        public:
            using edge_info_t = std::pair<sgl::core::node, sgl::core::weight_t>;   
            using adjacency_nodes_t = std::set<edge_info_t>;

        private:
            using adjacency_info_t = std::pair<sgl::core::node, adjacency_nodes_t>;
            using list_t = std::map<adjacency_info_t::first_type, adjacency_info_t::second_type>;

        public:
            adjacency_list(bool oriented = false, bool weighted = false);
            adjacency_list(const view& other);
            virtual ~adjacency_list();

            virtual void add_node(const sgl::core::node& node) override;
            virtual void add_edge(const sgl::core::edge& edge) override;

            virtual void remove_node(const sgl::core::node& node) override;
            virtual void remove_edge(const sgl::core::edge& edge) override;

            virtual type get_type() const override;
            virtual sgl::core::node_set_t get_nodes() const override;
            virtual sgl::core::edge_set_t get_edges() const override;

            virtual bool exists(const sgl::core::edge& edge) const override;
            virtual bool exists(const sgl::core::node& node) const override;

            adjacency_nodes_t get_adjacency_nodes(const sgl::core::node& node) const;

            bool operator==(const adjacency_list& rhs) const;

            adjacency_list& operator=(const adjacency_list& rhs);
            adjacency_list& operator=(const view& rhs);

        private:
            list_t list;
        };

        typedef std::shared_ptr<adjacency_list> adjacency_list_t;
        typedef const std::shared_ptr<const adjacency_list> const_adjacency_list_t;
    } // view
} // sgl
