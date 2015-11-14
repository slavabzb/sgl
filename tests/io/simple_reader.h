#pragma once

#include <sstream>

#include <cxxtest/TestSuite.h>

#include <sgl/io/simple_reader.h>
#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/edge_list.h>


class simple_reader_test: public CxxTest::TestSuite
{
    std::stringstream stringstream;
    sgl::io::reader_t reader;
    sgl::core::node_set_t nodes;
    sgl::core::edge_set_t edges;

public:
    virtual void setUp() override
    {
        this->reader = std::make_shared<sgl::io::simple_reader>(this->stringstream);
        this->stringstream.str(std::string());
    }
    
    void test_read_adjacency_matrix()
    {
        this->init_adjacency_matrix();
        
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());

        sgl::view::adjacency_matrix_t adjacency_matrix =
            std::dynamic_pointer_cast<sgl::view::adjacency_matrix>(view);
        
        TS_ASSERT(adjacency_matrix);
        TS_ASSERT(adjacency_matrix->is_oriented());
        TS_ASSERT(adjacency_matrix->is_weighted());
        
        const std::size_t nodes_count = adjacency_matrix->get_nodes().size();
        TS_ASSERT_EQUALS(nodes_count, 3);
        
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(0, 0), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(0, 1), 2);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(0, 2), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(1, 0), 2);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(1, 1), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(1, 2), 5);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(2, 0), 0);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(2, 1), 5);
        TS_ASSERT_EQUALS(adjacency_matrix->get_edge_weight(2, 2), 0);
    }
    
    void test_read_adjacency_list()
    {
        this->init_adjacency_list();
        
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());

        sgl::view::adjacency_list_t adjacency_list =
            std::dynamic_pointer_cast<sgl::view::adjacency_list>(view);
        
        TS_ASSERT(adjacency_list);
        TS_ASSERT(!adjacency_list->is_oriented());
        TS_ASSERT(adjacency_list->is_weighted());
        TS_ASSERT_EQUALS(adjacency_list->get_edges().size(), 2);
        TS_ASSERT_EQUALS(adjacency_list->get_nodes().size(), 4);
        
        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes = adjacency_list->get_adjacency_nodes(0);
        TS_ASSERT_EQUALS(adjacency_nodes.size(), 2);
        TS_ASSERT(adjacency_nodes.find(sgl::view::adjacency_list::edge_info_t(1, 2)) != adjacency_nodes.end());
        TS_ASSERT(adjacency_nodes.find(sgl::view::adjacency_list::edge_info_t(3, 5)) != adjacency_nodes.end());
        
        adjacency_nodes = adjacency_list->get_adjacency_nodes(1);
        TS_ASSERT_EQUALS(adjacency_nodes.size(), 1);
        TS_ASSERT(adjacency_nodes.find(sgl::view::adjacency_list::edge_info_t(0, 2)) != adjacency_nodes.end());
        
        adjacency_nodes = adjacency_list->get_adjacency_nodes(2);
        TS_ASSERT_EQUALS(adjacency_nodes.size(), 0);
        
        adjacency_nodes = adjacency_list->get_adjacency_nodes(3);
        TS_ASSERT_EQUALS(adjacency_nodes.size(), 1);
        TS_ASSERT(adjacency_nodes.find(sgl::view::adjacency_list::edge_info_t(0, 5)) != adjacency_nodes.end());
    }
    
    void test_read_edge_list()
    {
        this->init_edge_list();
        
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());

        sgl::view::edge_list_t edge_list = std::dynamic_pointer_cast<sgl::view::edge_list>(view);
        
        TS_ASSERT(edge_list);
        TS_ASSERT(!edge_list->is_oriented());
        TS_ASSERT(edge_list->is_weighted());
        
        sgl::core::node_set_t nodes = edge_list->get_nodes();               
        TS_ASSERT_EQUALS(nodes.size(), 4);
        TS_ASSERT(nodes.find(0) != nodes.end());
        TS_ASSERT(nodes.find(1) != nodes.end());
        TS_ASSERT(nodes.find(2) != nodes.end());
        TS_ASSERT(nodes.find(3) != nodes.end());
        
        sgl::core::edge_set_t edges = edge_list->get_edges();
        TS_ASSERT_EQUALS(edges.size(), 2);
        TS_ASSERT(edges.find(sgl::core::edge(0, 1, 2)) != edges.end());
        TS_ASSERT(edges.find(sgl::core::edge(0, 3, 5)) != edges.end());
    }
    
private:
    void init_adjacency_matrix()
    {
        this->stringstream.str(
            "C 3\n"
            "1 1\n"
            "0 2 0\n"
            "2 0 5\n"
            "0 5 0\n");
    }
    
    void init_adjacency_list()
    {
        this->stringstream.str(
            "L 4\n"
            "0 1\n"
            "1 2 3 5\n"
            "0 2\n"
            "\n"
            "0 5\n");
    }
    
    void init_edge_list()
    {
        this->stringstream.str(
            "E 4 2\n"
            "0 1\n"
            "0 1 2\n"
            "0 3 5\n");
    }
};
