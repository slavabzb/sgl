#pragma once

#include <sstream>
#include <cxxtest/TestSuite.h>
#include <sgl/simple_view_reader.h>

class simple_view_reader_test: public CxxTest::TestSuite
{
public:
	void setUp()
	{
		this->stringstream.str(
			"C 3 1\n"
			"0 2 5\n"
			"2 0 0\n"
			"5 0 0\n");
		
		this->view_reader = std::make_shared<sgl::simple_view_reader>(
			this->stringstream);
	}
	
	
	
private:
	std::stringstream stringstream;
	sgl::view_reader_t view_reader;
	
	
	
public:
	void test_read()
	{
		sgl::view_t view;
		TS_ASSERT_THROWS_NOTHING(view = this->view_reader->read());
		TS_ASSERT(view);
		
		sgl::node_set_t nodes;
		TS_ASSERT_THROWS_NOTHING(nodes = view->get_nodes());
		TS_ASSERT_EQUALS(nodes.size(), 3);
	}
};
