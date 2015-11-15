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
        /**
         * An interface for graph representations.
         */
        class view
        {
        public:
            /**
             * Constructor.
             * Constructs a view using given properties.
             * 
             * @param oriented - a flag; true, if graph is oriented, false otherwise,
             * @param weighted - a flag; true, if graph is weighted, false otherwise.
             */
            view(bool oriented = false, bool weighted = false);
            virtual ~view();

            /**
             * Adds a node to the view.
             * 
             * @param node - a node to be added.
             */
            virtual void add_node(const sgl::core::node& node) = 0;
            
            /**
             * Adds an edge to the view.
             * 
             * @param edge - an edge to be added.
             */
            virtual void add_edge(const sgl::core::edge& edge) = 0;

            /**
             * Removes a node from the view.
             * 
             * @param node - a node to be removed.
             */
            virtual void remove_node(const sgl::core::node& node) = 0;
            
            /**
             * Removes an edge from the view.
             * 
             * @param edge - an edge to be removed.
             */
            virtual void remove_edge(const sgl::core::edge& edge) = 0;

            /**
             * Retrieves a type of the view.
             * 
             * @return The type of the view.
             */
            virtual type get_type() const = 0;
            
            /**
             * Retrieves the nodes of the view.
             * 
             * @return The nodes of the view.
             */
            virtual sgl::core::node_set_t get_nodes() const = 0;
            
            /**
             * Retrieves the edges of the view.
             * 
             * @return The edges of the view.
             */
            virtual sgl::core::edge_set_t get_edges() const = 0;

            /**
             * Checks if edge exists in the view.
             * 
             * @param edge - an edge to be checked.
             * @return Flag; true, if the edge exists in the view, false otherwise.
             */
            virtual bool exists(const sgl::core::edge& edge) const = 0;
            
            /**
             * Checks if node exists in the view.
             * 
             * @param node - a node to be checked.
             * @return Flag; true, if the node exists in the view, false otherwise.
             */
            virtual bool exists(const sgl::core::node& node) const = 0;

            /**
             * Checks if view is oriented.
             * 
             * @return Flag; true, if the view is oriented, false otherwise.
             */
            bool is_oriented() const;
            
            /**
             * Checks if view is weighted.
             * 
             * @return Flag; true, if the view is weighted, false otherwise.
             */
            bool is_weighted() const;

            /**
             * Compares the view and rhs.
             * 
             * @param rhs - a view to be compared with.
             * @return Flag; true, if the view and rhs is equivalent, false otherwise.
             */
            bool operator==(const view& rhs) const;
            
            /**
             * Compares the view and rhs.
             * 
             * @param rhs - a view to be compared with.
             * @return  Flag; true, if the view and rhs is not equivalent, false otherwise.
             */
            bool operator!=(const view& rhs) const;
            
        private:
            bool oriented;
            bool weighted;
        };

        typedef std::shared_ptr<view> view_t;                       ///< view type.
        typedef const std::shared_ptr<const view> const_view_t;     ///< const view type.
    } // view
} // sgl
