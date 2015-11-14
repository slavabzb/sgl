#pragma once

#include <ostream>
#include <sgl/io/writer.h>

namespace sgl
{
    namespace io
    {
        class simple_writer: public writer
        {
        public:
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

        typedef std::shared_ptr<simple_writer> simple_writer_t;
    } // io
} // sgl
