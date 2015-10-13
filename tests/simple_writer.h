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
        
        sgl::edge edge0(0, 1, 2);
        sgl::edge edge1(1, 2, 5);
        
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
