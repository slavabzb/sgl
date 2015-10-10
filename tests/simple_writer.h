#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/simple_writer.h>
#include <sgl/view/adjacency_matrix.h>

class simple_writer_test: public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->writer = std::make_shared<sgl::view::simple_writer>(std::cout);
        
        this->view = std::make_shared<sgl::view::adjacency_matrix>(3);
//        this->view->add_edge(0, 1, 2);
  //      this->view->add_edge(1, 2, 3);
    }
    
    
    
private:
    sgl::view::writer_t writer;
    sgl::view::view_t view;
    
    
    
public:
    void test_write()
    {
        //this->writer->write(this->view);
    }
};
