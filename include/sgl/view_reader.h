#pragma once

#include <sgl/view.h>

namespace sgl {

class view_reader
{
public:
	virtual ~view_reader() {}
	
	virtual view_t read() = 0;
};

} // sgl
