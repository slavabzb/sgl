#pragma once

#include <istream>
#include <sgl/view_reader.h>

class simple_view_reader_test;

namespace sgl {

class simple_view_reader: public view_reader
{
#ifdef TESTS
	friend class ::simple_view_reader_test;
#endif

public:
	simple_view_reader(std::istream& istream);
	virtual ~simple_view_reader();

	virtual view_t read() override;

private:
	std::istream& istream;
};

typedef std::shared_ptr<simple_view_reader> simple_view_reader_t;

} // sgl
