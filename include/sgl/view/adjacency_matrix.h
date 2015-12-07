/* Copyright (c) 2015
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

#pragma once /** @file adjacency_matrix.h @ref adjacency_matrix. */

#include <vector>
#include <sgl/view/view.h>

#ifdef TESTS
class adjacency_matrix_test;
#endif

namespace sgl
{
    namespace view
    {
        /**
         * @ref adjacency_matrix
         * @ingroup view
         */
        class adjacency_matrix: public view
        {
        #ifdef TESTS
            friend class ::adjacency_matrix_test;
        #endif

            using base_t = view;
            using matrix_row_t = std::vector<sgl::core::node_id_t>;
            using matrix_t = std::vector<matrix_row_t>;    

        public:
            /**
             * Constructor.
             * Constructs an adjacency_matrix using given properties.
             * 
             * @param nodes - a number of nodes in the view,
             * @param oriented - a flag; true, if graph is oriented, false otherwise,
             * @param weighted - a flag; true, if graph is weighted, false otherwise.
             */
            adjacency_matrix(std::size_t nodes = 0, bool oriented = false, bool weighted = false);
            
            /**
             * Copy constructor.
             * Constructs an adjacency_matrix using other as pattern.
             * 
             * @param other - a view to be constructed from.
             */
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

            /**
             * Retrieves a weight of the edge.
             * 
             * @param first - the beginning of the edge,
             * @param second - the end of the edge.
             * @return A weight of the edge.
             * @throw std::out_of_range if there is no first and/or second node in the adjacency_matrix.
             */
            sgl::core::weight_t get_edge_weight(const sgl::core::node& first, const sgl::core::node& second) const;

            /**
             * Assigns rhs to the adjacency_matrix.
             * 
             * @param rhs - an adjacency_matrix to be assigned with.
             * @return The adjacency_matrix.
             * @throw std::invalid_argument if oriented/weighted flags are mismatched.
             */
            adjacency_matrix& operator=(const sgl::view::adjacency_matrix& rhs);
            
            /**
             * Assigns ths to the adjacency_matrix.
             * 
             * @param rhs - an adjacency_matrix to be assigned with.
             * @return The adjacency_matrix.
             * @throw std::invalid_argument if oriented/weighted flags are mismatched.
             */
            adjacency_matrix& operator=(const sgl::view::view& rhs);

        private:
            bool in_range(sgl::core::node_id_t from, sgl::core::node_id_t to) const;

        private:
            matrix_t matrix;
        };

        typedef std::shared_ptr<adjacency_matrix> adjacency_matrix_t;                       ///< adjacency_matrix type.
        typedef const std::shared_ptr<const adjacency_matrix> const_adjacency_matrix_t;     ///< const adjacency_matrix type.
    } // view
} // sgl
