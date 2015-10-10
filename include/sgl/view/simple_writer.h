#pragma once

#include <ostream>
#include <sgl/view_writer.h>

namespace sgl {

class simple_view_writer: public view_writer
{
public:
	simple_view_writer(std::ostream& ostream);
	virtual ~simple_view_writer();
	
	virtual void write(const_view_t& view) override;
	
private:
	std::ostream& ostream;
};

} // sgl
