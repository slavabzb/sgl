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

#include <sgl/view/view.h>

namespace sgl
{
    namespace core
    {
        /**
         * Graph.
         * Graph represented in selected view.     
         */
        class graph
        {
        public:
            /**
             * Constructor.
             * Constructs a graph with given view.
             * 
             * @param view - view of the graph.
             * @throw std::invalid_argument if view is nullptr.
             */
            graph(const sgl::view::view_t& view);

            /**
             * Retrieves the view of the graph.
             * 
             * @return The view of the graph.
             */
            sgl::view::view_t get_view();

            /**
             * Retrieves the view of the constant graph.
             * 
             * @return The view of the constant graph.
             */
            sgl::view::const_view_t get_view() const;

            /**
             * Assigns new view to the graph.
             * 
             * @param view - new view of the graph.
             * @throw std::invalid_argument if view is nullptr.
             */
            void set_view(const sgl::view::view_t& view);

        private:
            sgl::view::view_t view;
        };
    } // core
} // sgl
