#pragma once

#include <sgl/view/view.h>

namespace sgl
{
    namespace io
    {
        class reader
        {
        public:
            virtual ~reader() {}

            virtual sgl::view::view_t read() = 0;
        };

        typedef std::shared_ptr<reader> reader_t;

    } // io
} // sgl
