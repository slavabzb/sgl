#pragma once

#include <istream>
#include <sgl/view_reader.h>

namespace sgl {

class simple_view_reader: public view_reader
{
public:
	simple_view_reader(std::istream& istream);
	virtual ~simple_view_reader();
	
	virtual view_t read() override;
	
private:
	std::istream& istream;
};

} // sgl
