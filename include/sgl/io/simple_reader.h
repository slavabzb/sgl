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

#include <istream>
#include <sgl/io/reader.h>

namespace sgl
{
    namespace io
    {
        /**
         * A @ref sr-graph reader.
         * Reads @ref sr-graph from input stream.
         * 
         * @ingroup io
         */
        class simple_reader: public reader
        {
        public:
            /**
             * Constructor.
             * 
             * Constructs a simple_reader and provide istream as input stream.
             * 
             * @param istream - an input stream.
             */
            simple_reader(std::istream& istream);
            virtual ~simple_reader();

            virtual sgl::view::view_t read() override;

        private:
            void read_adjacency_matrix(sgl::view::view_t& view);
            void read_adjacency_list(sgl::view::view_t& view);
            void read_edge_list(sgl::view::view_t& view);

        private:
            std::istream& istream;
        };

        typedef std::shared_ptr<simple_reader> simple_reader_t;     ///< simple_reader type.
    } // io
} // sgl
