#pragma once

#include <sgl/view.h>

namespace sgl {

class view_writer
{
public:
	virtual ~view_writer() {}
	
	virtual void write(const_view_t& view) = 0;
};

} // sgl
