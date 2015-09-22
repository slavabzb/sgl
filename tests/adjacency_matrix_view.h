#pragma once

#include <sgl/adjacency_matrix_view.h>
#include <cxxtest/TestSuite.h>



class adjacency_matrix_view_test: public CxxTest::TestSuite
{
public:
    adjacency_matrix_view_test()
        : view(std::make_shared<sgl::adjacency_matrix_view>())
    {

    }
		
private:
    sgl::adjacency_matrix_view_t view;
	
public:
    void test_constructor()
    {
        sgl::adjacency_matrix_view_t adjacency_matrix_view;

        TS_ASSERT_THROWS_NOTHING(adjacency_matrix_view =
                std::make_shared<sgl::adjacency_matrix_view>());
        TS_ASSERT(adjacency_matrix_view);
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.size(), 0);

    }

    void test_add_node()
    {
        TS_ASSERT_THROWS_NOTHING(this->view->add_node());
        TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.begin()->size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix[0][0], 0);

        TS_ASSERT_THROWS_NOTHING(this->view->add_node());
        TS_ASSERT_EQUALS(this->view->matrix.size(), 2);
        TS_ASSERT_EQUALS(this->view->matrix.begin()->size(), 2);
        TS_ASSERT_EQUALS(this->view->matrix[0][0], 0);
        TS_ASSERT_EQUALS(this->view->matrix[0][1], 0);
        TS_ASSERT_EQUALS(this->view->matrix[1][0], 0);
        TS_ASSERT_EQUALS(this->view->matrix[1][1], 0);
    }

    void test_remove_node()
    {
        this->view->matrix[0][0] = 1;
        this->view->matrix[0][1] = 2;
        this->view->matrix[1][0] = 3;
        this->view->matrix[1][1] = 4;

        sgl::node_id_t node_id = 1;
        sgl::node_t node = std::make_shared<sgl::node>(node_id);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_node(node));
        TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.begin()->size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix[0][0], 1);
    }
};
