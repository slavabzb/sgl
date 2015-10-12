#pragma once

#include <sstream>

#include <cxxtest/TestSuite.h>

#include <sgl/view/simple_writer.h>
#include <sgl/view/adjacency_matrix.h>



class simple_writer_test: public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->string =
            "C 3\n"
            "0 0\n"
            "0 2 0 \n"
            "2 0 5 \n"
            "0 5 0 \n";
        
        this->writer = std::make_shared<sgl::view::simple_writer>(
            this->stringstream);
        
        this->view = std::make_shared<sgl::view::adjacency_matrix>(3);
        
        sgl::node_t node0 = std::make_shared<sgl::node>(0);
        sgl::node_t node1 = std::make_shared<sgl::node>(1);
        sgl::node_t node2 = std::make_shared<sgl::node>(2);
        
        sgl::edge_t edge0 = std::make_shared<sgl::edge>(node0, node1, 2);
        sgl::edge_t edge1 = std::make_shared<sgl::edge>(node1, node2, 5);
        
        this->view->add_edge(edge0);       
        this->view->add_edge(edge1);
    }
    
    
    
private:
    std::stringstream stringstream;
    std::string string;
    sgl::view::writer_t writer;
    sgl::view::view_t view;
    
    
    
public:
    void test_write()
    {
        TS_ASSERT_THROWS_NOTHING(this->writer->write(this->view));
        TS_ASSERT_EQUALS(this->stringstream.str(), this->string);
    }
};
