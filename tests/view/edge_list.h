#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/edge_list.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/adjacency_matrix.h>



class edge_list_test: public CxxTest::TestSuite
{
    sgl::view::edge_list_t oriented_view;
    sgl::view::edge_list_t not_oriented_view;
    
public:
    virtual void setUp() override
    {
        this->oriented_view = std::make_shared<sgl::view::edge_list>(1, 1);
        this->not_oriented_view = std::make_shared<sgl::view::edge_list>(0, 1);
    }
    
    void test_constructor()
    {
        sgl::view::view_t view;
        TS_ASSERT_THROWS_NOTHING(view = std::make_shared<sgl::view::edge_list>());
    }
    
    void test_add_node()
    {
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_node(0));
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 1);
        TS_ASSERT(this->oriented_view->nodes.find(0) != this->oriented_view->nodes.end());
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_node(1));
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 2);
        TS_ASSERT(this->oriented_view->nodes.find(1) != this->oriented_view->nodes.end());
    }
    
    void test_add_edge()
    {
        sgl::core::edge edge(0, 1, 2);
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 2);
        TS_ASSERT(this->oriented_view->nodes.find(0) != this->oriented_view->nodes.end());
        TS_ASSERT(this->oriented_view->nodes.find(1) != this->oriented_view->nodes.end());
        TS_ASSERT_EQUALS(this->oriented_view->edges.size(), 1);
        TS_ASSERT(this->oriented_view->edges.find(edge) != this->oriented_view->edges.end());
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->edges.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 2);
    }
    
    void test_remove_node()
    {
        this->oriented_view->nodes.insert(0);
        this->oriented_view->nodes.insert(1);
        this->oriented_view->nodes.insert(2);
        this->oriented_view->nodes.insert(3);
        
        this->oriented_view->edges.insert(sgl::core::edge(0, 1, 4));
        this->oriented_view->edges.insert(sgl::core::edge(1, 2, 5));
        this->oriented_view->edges.insert(sgl::core::edge(2, 3, 6));
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->remove_node(2));
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 3);
        TS_ASSERT(this->oriented_view->nodes.find(0) != this->oriented_view->nodes.end());
        TS_ASSERT(this->oriented_view->nodes.find(1) != this->oriented_view->nodes.end());
        TS_ASSERT(this->oriented_view->nodes.find(2) == this->oriented_view->nodes.end());
        TS_ASSERT(this->oriented_view->nodes.find(3) != this->oriented_view->nodes.end());
        TS_ASSERT_EQUALS(this->oriented_view->edges.size(), 1);
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(0, 1, 4)) != this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(1, 2, 5)) == this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(2, 3, 6)) == this->oriented_view->edges.end());
    }
    
    void test_remove_edge()
    {
        this->oriented_view->nodes.insert(0);
        this->oriented_view->nodes.insert(1);
        this->oriented_view->nodes.insert(2);
        this->oriented_view->nodes.insert(3);
        
        this->oriented_view->edges.insert(sgl::core::edge(0, 1, 4));
        this->oriented_view->edges.insert(sgl::core::edge(1, 2, 5));
        this->oriented_view->edges.insert(sgl::core::edge(2, 3, 6));
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->remove_edge(sgl::core::edge(1, 2, 5)));
        TS_ASSERT_EQUALS(this->oriented_view->nodes.size(), 4);
        TS_ASSERT_EQUALS(this->oriented_view->edges.size(), 2);
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(0, 1, 4)) != this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(1, 2, 5)) == this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(2, 3, 6)) != this->oriented_view->edges.end());
    }
    
    void test_get_nodes()
    {
        this->oriented_view->nodes.insert(0);
        this->oriented_view->nodes.insert(1);
        
        sgl::core::node_set_t nodes;
        TS_ASSERT_THROWS_NOTHING(nodes = this->oriented_view->get_nodes());
        TS_ASSERT_EQUALS(nodes.size(), 2)
        TS_ASSERT(nodes.find(0) != nodes.end());
        TS_ASSERT(nodes.find(1) != nodes.end());
        TS_ASSERT(nodes.find(2) == nodes.end());
    }
    
    void test_get_edges()
    {
        this->oriented_view->edges.insert(sgl::core::edge(0, 1, 4));
        this->oriented_view->edges.insert(sgl::core::edge(1, 2, 5));
        this->oriented_view->edges.insert(sgl::core::edge(2, 3, 6));
        
        sgl::core::edge_set_t edges;
        TS_ASSERT_THROWS_NOTHING(edges = this->oriented_view->get_edges());
        TS_ASSERT_EQUALS(edges.size(), 3);
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(0, 1, 4)) != this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(1, 2, 5)) != this->oriented_view->edges.end());
        TS_ASSERT(this->oriented_view->edges.find(sgl::core::edge(2, 3, 6)) != this->oriented_view->edges.end());
    }
    
    void test_exists()
    {
        this->oriented_view->nodes.insert(0);
        this->oriented_view->nodes.insert(1);
        this->oriented_view->nodes.insert(2);
        this->oriented_view->nodes.insert(3);
        
        this->oriented_view->edges.insert(sgl::core::edge(0, 1, 4));
        this->oriented_view->edges.insert(sgl::core::edge(1, 2, 5));
        this->oriented_view->edges.insert(sgl::core::edge(2, 3, 6));
        
        TS_ASSERT(this->oriented_view->exists(2));
        TS_ASSERT(!this->oriented_view->exists(4));
        TS_ASSERT(this->oriented_view->exists(sgl::core::edge(0, 1, 4)));
        TS_ASSERT(!this->oriented_view->exists(sgl::core::edge(1, 0, 4)));
        
        this->not_oriented_view->edges.insert(sgl::core::edge(0, 1, 4));
        
        TS_ASSERT(this->not_oriented_view->exists(sgl::core::edge(0, 1, 4)));
        TS_ASSERT(this->not_oriented_view->exists(sgl::core::edge(1, 0, 4)));
    }
    
    void test_conversion()
    {
        sgl::core::edge edge(1, 2, 3);
        
        {
            sgl::view::edge_list rhs(0, 1);
            rhs.add_edge(edge);
            rhs.add_node(3);
            
            TS_ASSERT_THROWS(*this->oriented_view = rhs, std::invalid_argument);
            
            TS_ASSERT_THROWS_NOTHING(*this->not_oriented_view = rhs);
            TS_ASSERT_EQUALS(*this->not_oriented_view, rhs);
        }
        
        {
            sgl::view::adjacency_matrix rhs(3, 0, 1);
            rhs.add_edge(edge);
            
            TS_ASSERT_THROWS_NOTHING(*this->not_oriented_view = rhs);
            
            sgl::core::node_set_t nodes = this->not_oriented_view->get_nodes();
            TS_ASSERT_EQUALS(nodes.size(), 3);
            TS_ASSERT(nodes.find(0) != nodes.end());
            TS_ASSERT(nodes.find(1) != nodes.end());
            TS_ASSERT(nodes.find(2) != nodes.end());
            
            sgl::core::edge_set_t edges = this->not_oriented_view->get_edges();
            TS_ASSERT_EQUALS(edges.size(), 1);
            TS_ASSERT_EQUALS(*edges.begin(), edge);
        }
        
        {
            sgl::view::adjacency_list rhs(0, 1);
            rhs.add_edge(edge);
            rhs.add_node(3);
            
            TS_ASSERT_THROWS_NOTHING(*this->not_oriented_view = rhs);
            
            sgl::core::node_set_t nodes = this->not_oriented_view->get_nodes();
            TS_ASSERT_EQUALS(nodes.size(), 3);
            TS_ASSERT(nodes.find(0) == nodes.end());
            TS_ASSERT(nodes.find(1) != nodes.end());
            TS_ASSERT(nodes.find(2) != nodes.end());
            TS_ASSERT(nodes.find(3) != nodes.end());
            
            sgl::core::edge_set_t edges = this->not_oriented_view->get_edges();
            TS_ASSERT_EQUALS(edges.size(), 1);
            TS_ASSERT_EQUALS(*edges.begin(), edge);
        }
    }
};
