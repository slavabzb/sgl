#pragma once

#include <sstream>

#include <cxxtest/TestSuite.h>

#include <sgl/view/simple_reader.h>
#include <sgl/view/adjacency_matrix.h>


class simple_reader_test: public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->reader = std::make_shared<sgl::view::simple_reader>(
            this->stringstream);
        
        this->stringstream.str(
            "C 3\n"
            "1 1\n"
            "0 2 0 \n"
            "2 0 5 \n"
            "0 5 0 \n");
    }

    
    
private:
    std::stringstream stringstream;
    sgl::view::reader_t reader;
    sgl::node_set_t nodes;
    sgl::edge_set_t edges;

    
    
public:
    void test_read()
    {
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());

        sgl::view::adjacency_matrix_t adjacency_matrix =
            std::dynamic_pointer_cast<sgl::view::adjacency_matrix>(view);
        
        TS_ASSERT(adjacency_matrix);
        TS_ASSERT(adjacency_matrix->is_oriented());
        TS_ASSERT(adjacency_matrix->is_weighted());
        
        const std::size_t nodes_count = adjacency_matrix->get_nodes_count();
        TS_ASSERT_EQUALS(nodes_count, 3);
        
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(0, 0), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(0, 1), 2);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(0, 2), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(1, 0), 2);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(1, 1), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(1, 2), 5);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(2, 0), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(2, 1), 5);
        TS_ASSERT_EQUALS(adjacency_matrix->get_weight(2, 2), 0);
    }
};
