#pragma once

#include <sgl/adjacency_matrix_view.h>
#include <cxxtest/TestSuite.h>

class adjacency_matrix_view_test: public CxxTest::TestSuite
{
public:
    virtual void setUp()
    {
        this->view = std::make_shared<sgl::adjacency_matrix_view>();
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
        TS_ASSERT_EQUALS(adjacency_matrix_view->get_nodes().size(), 0);
    }

    
    
    void test_add_node()
    {
        TS_ASSERT_THROWS_NOTHING(this->view->add_node());
        
        sgl::node_set_t nodes = this->view->get_nodes();
        TS_ASSERT_EQUALS(nodes.size(), 1);
        
        sgl::node_id_t node_id = 0;
        sgl::node node(node_id);
        TS_ASSERT(nodes.find(node) != nodes.end());
    }

    
    
    void test_remove_node()
    {
        this->view->add_node();
        this->view->add_node();
        
        sgl::node_id_t node_id = 1;
        sgl::node_t node = std::make_shared<sgl::node>(node_id);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_node(node));
        
        sgl::node_set_t nodes = this->view->get_nodes();
        TS_ASSERT_EQUALS(nodes.size(), 1);
        TS_ASSERT_EQUALS(nodes.find(*node), nodes.end());
        TS_ASSERT(nodes.find(sgl::node(0)) != nodes.end());
        
        TS_ASSERT_THROWS(this->view->remove_node(node), std::invalid_argument);
    }
    
    
    
    void test_get_nodes()
    {
        sgl::node_set_t nodes;
        TS_ASSERT_THROWS_NOTHING(nodes = this->view->get_nodes());
        TS_ASSERT_EQUALS(nodes.size(), 0);
        
        this->view->add_node();
        this->view->add_node();
        TS_ASSERT_THROWS_NOTHING(nodes = this->view->get_nodes());
        TS_ASSERT_EQUALS(nodes.size(), 2);
        TS_ASSERT_EQUALS(nodes.begin()->get_id(), 0);
        TS_ASSERT_EQUALS((++nodes.begin())->get_id(), 1);
    }
    
    
    
    void test_add_edge()
    {
        sgl::node_t from = std::make_shared<sgl::node>(0);
        sgl::node_t to = std::make_shared<sgl::node>(1);
        sgl::weight_t weight = 1;
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
        
        TS_ASSERT_THROWS(this->view->add_edge(edge), std::invalid_argument);
		
		this->view->add_node();
		this->view->add_node();
		TS_ASSERT_THROWS_NOTHING(this->view->add_edge(edge));
		
		sgl::edge_set_t edges = this->view->get_edges();
		TS_ASSERT_EQUALS(edges.size(), 1);
		TS_ASSERT(edges.find(*edge) != edges.end());
    }
	
	
	
	void test_get_edges()
	{
		sgl::edge_set_t edges;
		TS_ASSERT_THROWS_NOTHING(edges = this->view->get_edges());
		TS_ASSERT_EQUALS(edges.size(), 0);
		
		this->view->add_node();
		this->view->add_node();
	
		sgl::node_t from = std::make_shared<sgl::node>(0);
        sgl::node_t to = std::make_shared<sgl::node>(1);
        sgl::weight_t weight = 1;
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
		this->view->add_edge(edge);
		
		TS_ASSERT_THROWS_NOTHING(edges = this->view->get_edges());
		TS_ASSERT_EQUALS(edges.size(), 1);
		TS_ASSERT(edges.find(*edge) != edges.end());
	}
	
	
	
	void test_remove_edge()
	{
		sgl::node_t from = std::make_shared<sgl::node>(0);
        sgl::node_t to = std::make_shared<sgl::node>(1);
        sgl::weight_t weight = 1;
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);		
		
		TS_ASSERT_THROWS(this->view->remove_edge(edge), std::invalid_argument);
	}
};
