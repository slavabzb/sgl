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

#include <vector>
#include <sgl/view/view.h>

class adjacency_matrix_test;

namespace sgl
{
    namespace view
    {
        class adjacency_matrix: public view
        {
        #ifdef TESTS
            friend class ::adjacency_matrix_test;
        #endif

            using matrix_row_t = std::vector<sgl::core::node_id_t>;
            using matrix_t = std::vector<matrix_row_t>;    

        public:
            adjacency_matrix(std::size_t nodes = 0, bool oriented = false, bool weighted = false);
            adjacency_matrix(const view& other);
            virtual ~adjacency_matrix();

            virtual void add_node(const sgl::core::node& node) override;
            virtual void add_edge(const sgl::core::edge& edge) override;

            virtual void remove_node(const sgl::core::node& node) override;
            virtual void remove_edge(const sgl::core::edge& edge) override;

            virtual type get_type() const override;
            virtual sgl::core::node_set_t get_nodes() const override;
            virtual sgl::core::edge_set_t get_edges() const override;

            virtual bool exists(const sgl::core::edge& edge) const override;
            virtual bool exists(const sgl::core::node& node) const override;

            sgl::core::weight_t get_edge_weight(const sgl::core::node& first, const sgl::core::node& second) const;

            bool operator==(const adjacency_matrix& rhs) const;

            adjacency_matrix& operator=(const sgl::view::adjacency_matrix& rhs);
            adjacency_matrix& operator=(const sgl::view::view& rhs);

        private:
            bool in_range(sgl::core::node_id_t from, sgl::core::node_id_t to) const;

        private:
            matrix_t matrix;
        };

        typedef std::shared_ptr<adjacency_matrix> adjacency_matrix_t;
        typedef const std::shared_ptr<const adjacency_matrix> const_adjacency_matrix_t;
    } // view
} // sgl
