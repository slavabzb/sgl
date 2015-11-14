#pragma once

#include <istream>
#include <sgl/io/reader.h>

namespace sgl
{
    namespace io
    {
        class simple_reader: public reader
        {
        public:
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

        typedef std::shared_ptr<simple_reader> simple_reader_t;
    } // io
} // sgl
