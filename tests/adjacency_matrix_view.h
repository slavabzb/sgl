#pragma once

#include <sgl/adjacency_matrix_view.h>
#include <cxxtest/TestSuite.h>



class adjacency_matrix_view_test: public CxxTest::TestSuite
{
public:
	adjacency_matrix_view_test()
	{
		
	}
		
private:
	sgl::view_t view;
	
public:
	void test_constructor()
	{
		sgl::adjacency_matrix_view_t adjacency_matrix_view;
		
		TS_ASSERT_THROWS_NOTHING(adjacency_matrix_view =
			std::make_shared<sgl::adjacency_matrix_view>());
		TS_ASSERT(adjacency_matrix_view);
		TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.size(), 0);
		
	}
};
