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

#include <sgl/core/node.h>
#include <sgl/core/edge.h>
#include <sgl/view/type.h>

namespace sgl
{
    namespace view
    {
        class view
        {
        public:
            view(bool oriented = false, bool weighted = false);
            virtual ~view();

            virtual void add_node(const sgl::core::node& node) = 0;
            virtual void add_edge(const sgl::core::edge& edge) = 0;

            virtual void remove_node(const sgl::core::node& node) = 0;
            virtual void remove_edge(const sgl::core::edge& edge) = 0;

            virtual type get_type() const = 0;
            virtual sgl::core::node_set_t get_nodes() const = 0;
            virtual sgl::core::edge_set_t get_edges() const = 0;

            virtual bool exists(const sgl::core::edge& edge) const = 0;
            virtual bool exists(const sgl::core::node& node) const = 0;

            bool is_oriented() const;
            bool is_weighted() const;

        protected:
            using base_t = view;

            void check_flags(const view& view) const;

        private:
            bool oriented;
            bool weighted;
        };

        typedef std::shared_ptr<view> view_t;
        typedef const std::shared_ptr<const view> const_view_t;
    } // view
} // sgl
