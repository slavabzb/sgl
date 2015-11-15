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

#include <ostream>
#include <sgl/io/writer.h>

namespace sgl
{
    namespace io
    {
        /**
         * A @ref sr-graph writer.
         * 
         * Writes a @ref sr-graph to output stream.
         */
        class simple_writer: public writer
        {
        public:
            /**
             * Constructor.
             * 
             * Constructs a simple_writer and provides ostream as output stream.
             * 
             * @param ostream - an output stream.
             */
            simple_writer(std::ostream& ostream);
            virtual ~simple_writer();

            virtual void write(sgl::view::const_view_t& view) override;

        private:
            void write_adjacency_matrix(sgl::view::const_view_t& view);
            void write_adjacency_list(sgl::view::const_view_t& view);
            void write_edge_list(sgl::view::const_view_t& view);

        private:
            std::ostream& ostream;
        };

        typedef std::shared_ptr<simple_writer> simple_writer_t;     ///< simple_writer type.
    } // io
} // sgl
