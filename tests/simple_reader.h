#pragma once

#include <sstream>
#include <cxxtest/TestSuite.h>
#include <sgl/view/simple_reader.h>

class simple_reader_test: public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->reader = std::make_shared<sgl::view::simple_reader>(
            this->stringstream);
    }

    
    
private:
    std::stringstream stringstream;
    sgl::view::reader_t reader;
    sgl::node_set_t nodes;
    sgl::edge_set_t edges;

    
    
public:
    void test_read_oriented()
    {
        this->init_oriented();
        
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());
        TS_ASSERT(view);

        sgl::node_set_t nodes;
        TS_ASSERT_THROWS_NOTHING(nodes = view->get_nodes());
        TS_ASSERT_EQUALS(nodes.size(), 3);
        TS_ASSERT_EQUALS(nodes, this->nodes);

        sgl::edge_set_t edges;
        TS_ASSERT_THROWS_NOTHING(edges = view->get_edges());
        TS_ASSERT_EQUALS(edges.size(), 2);
        TS_ASSERT_EQUALS(edges, this->edges);
    }
    
    
    
    void test_read_not_oriented()
    {
        this->init_not_oriented();
        
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = this->reader->read());
        TS_ASSERT(view);

        sgl::node_set_t nodes;
        TS_ASSERT_THROWS_NOTHING(nodes = view->get_nodes());
        TS_ASSERT_EQUALS(nodes.size(), 3);
        TS_ASSERT_EQUALS(nodes, this->nodes);

        sgl::edge_set_t edges;
        TS_ASSERT_THROWS_NOTHING(edges = view->get_edges());
        TS_ASSERT_EQUALS(edges.size(), 4);
        TS_ASSERT_EQUALS(edges, this->edges);
    }
    
    
    
private:
    void init_oriented()
    {
        this->stringstream.str(
            "C 3\n"
            "1 1\n"
            "0 2 5\n"
            "2 0 0\n"
            "5 0 0\n");

        sgl::node_t node0 = std::make_shared<sgl::node>(0);
        sgl::node_t node1 = std::make_shared<sgl::node>(1);
        sgl::node_t node2 = std::make_shared<sgl::node>(2);

        this->nodes.insert(*node0);
        this->nodes.insert(*node1);
        this->nodes.insert(*node2);

        sgl::weight_t edge0_weight = 2;
        sgl::weight_t edge1_weight = 5;
        
        this->edges.insert(sgl::edge(node0, node1, edge0_weight));
        this->edges.insert(sgl::edge(node0, node2, edge1_weight));
    }
    
    
    
    void init_not_oriented()
    {
        this->stringstream.str(
            "C 3\n"
            "0 1\n"
            "0 2 5\n"
            "2 0 0\n"
            "5 0 0\n");

        sgl::node_t node0 = std::make_shared<sgl::node>(0);
        sgl::node_t node1 = std::make_shared<sgl::node>(1);
        sgl::node_t node2 = std::make_shared<sgl::node>(2);

        this->nodes.insert(*node0);
        this->nodes.insert(*node1);
        this->nodes.insert(*node2);

        sgl::weight_t edge0_weight = 2;
        sgl::weight_t edge1_weight = 5;
        
        this->edges.insert(sgl::edge(node0, node1, edge0_weight));
        this->edges.insert(sgl::edge(node0, node2, edge1_weight));
        this->edges.insert(sgl::edge(node1, node0, edge0_weight));
        this->edges.insert(sgl::edge(node2, node0, edge1_weight));
    }
};
