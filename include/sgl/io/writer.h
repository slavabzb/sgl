#pragma once

#include <sgl/view/view.h>

namespace sgl
{
    namespace io
    {
        class writer
        {
        public:
            virtual ~writer() {}

            virtual void write(sgl::view::const_view_t& view) = 0;
        };

        typedef std::shared_ptr<writer> writer_t;
    } // io
} // sgl
