#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/adjacency_list.h>

class adjacency_list_test: public CxxTest::TestSuite
{
public:
    virtual void setUp()
    {
        bool oriented = true;
        this->oriented_view =
            std::make_shared<sgl::view::adjacency_list>(oriented);
        
        this->not_oriented_view =
            std::make_shared<sgl::view::adjacency_list>();
    }

    
    
private:
    sgl::view::adjacency_list_t oriented_view;
    sgl::view::adjacency_list_t not_oriented_view;

    
    
public:
    void test_constructor()
    {
        sgl::view::adjacency_list_t adjacency_list;
        TS_ASSERT_THROWS_NOTHING(
            adjacency_list = std::make_shared<sgl::view::adjacency_list>());
        
        TS_ASSERT_EQUALS(adjacency_list->list.size(), 0);
    }
    
    
    
    void test_add_node()
    {
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 0);
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_node());
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_view->list.begin()->first, 1);
        TS_ASSERT_EQUALS(this->oriented_view->list[1].size(), 0);
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_node());
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->oriented_view->list.begin()->first, 1);
        TS_ASSERT_EQUALS((++this->oriented_view->list.begin())->first, 2);
        TS_ASSERT_EQUALS(this->oriented_view->list[1].size(), 0);
        TS_ASSERT_EQUALS(this->oriented_view->list[2].size(), 0);
        
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 2);
    }
    
    
    
    void test_oriented_view_add_edge()
    {
        sgl::node_id_t node_id_from = 0;
        sgl::node_id_t node_id_to = 1;
        
        sgl::node_t from = std::make_shared<sgl::node>(node_id_from);
        sgl::node_t to = std::make_shared<sgl::node>(node_id_to);
        
        sgl::weight_t weight = 2;   
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_view->list[0].size(), 1);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->oriented_view->list.find(*from);
        
        TS_ASSERT(it != this->oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *from);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight);
        
        sgl::weight_t new_weight = edge->get_weight() + 1;
        edge->set_weight(new_weight);
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        
        it = this->oriented_view->list.find(*from);
        TS_ASSERT(it != this->oriented_view->list.end());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
    }
    
    
    
    void test_not_oriented_view_add_edge()
    {
        sgl::node_id_t node_id_from = 0;
        sgl::node_id_t node_id_to = 1;
        
        sgl::node_t from = std::make_shared<sgl::node>(node_id_from);
        sgl::node_t to = std::make_shared<sgl::node>(node_id_to);
        
        sgl::weight_t weight = 2;   
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
        
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[0].size(), 1);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[1].size(), 1);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(*from);
        
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *from);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        it = this->not_oriented_view->list.find(*to);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *to);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *from);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        sgl::weight_t new_weight = edge->get_weight() + 1;
        edge->set_weight(new_weight);
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[0].size(), 1);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[1].size(), 1);
        
        it = this->not_oriented_view->list.find(*from);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *from);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        it = this->not_oriented_view->list.find(*to);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *to);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *from);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
    }
    
    
    
    void test_remove_node()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::node_id_t node_id_0 = 0;
        sgl::node_id_t node_id_1 = 1;
        sgl::node_id_t node_id_2 = 2;
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        sgl::node_t node0 = std::make_shared<sgl::node>(node_id_0);
        sgl::node_t node1 = std::make_shared<sgl::node>(node_id_1);
        sgl::node_t node2 = std::make_shared<sgl::node>(node_id_2);
        
        this->not_oriented_view->list[0].insert(std::make_pair(*node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(*node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(*node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(*node0, weight1));
        
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->remove_node(node1));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(*node0);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *node0);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *node2);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
        
        it = this->not_oriented_view->list.find(*node1);
        TS_ASSERT_EQUALS(it, this->not_oriented_view->list.end());
        
        it = this->not_oriented_view->list.find(*node2);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *node2);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *node0);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
    }
    
    
    
    void test_remove_edge()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::node_id_t node_id_0 = 0;
        sgl::node_id_t node_id_1 = 1;
        sgl::node_id_t node_id_2 = 2;
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        sgl::node_t node0 = std::make_shared<sgl::node>(node_id_0);
        sgl::node_t node1 = std::make_shared<sgl::node>(node_id_1);
        sgl::node_t node2 = std::make_shared<sgl::node>(node_id_2);
                
        this->not_oriented_view->list[0].insert(std::make_pair(*node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(*node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(*node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(*node0, weight1));
        
        sgl::edge_t edge = std::make_shared<sgl::edge>(node0, node1, weight0);
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->remove_edge(edge));
        
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 3);
        
         sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(*node0);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *node0);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *node2);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
        
        it = this->not_oriented_view->list.find(*node1);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *node1);
        TS_ASSERT_EQUALS(it->second.size(), 0);
        
        it = this->not_oriented_view->list.find(*node2);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, *node2);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *node0);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
    }
    
    
    
    void test_exists()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::node_id_t node_id_0 = 0;
        sgl::node_id_t node_id_1 = 1;
        sgl::node_id_t node_id_2 = 2;
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        sgl::node_t node0 = std::make_shared<sgl::node>(node_id_0);
        sgl::node_t node1 = std::make_shared<sgl::node>(node_id_1);
        sgl::node_t node2 = std::make_shared<sgl::node>(node_id_2);
                
        this->not_oriented_view->list[0].insert(std::make_pair(*node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(*node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(*node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(*node0, weight1));
        
        sgl::edge_t existing_edge = std::make_shared<sgl::edge>(node0, node1, weight0);
        sgl::edge_t not_existing_edge = std::make_shared<sgl::edge>(node1, node2, weight0);
        
        bool exists = false;
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(existing_edge));
        TS_ASSERT_EQUALS(exists, true);
        
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(not_existing_edge));
        TS_ASSERT_EQUALS(exists, false);
        
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(node0));
        TS_ASSERT_EQUALS(exists, true);      
        
        sgl::node_t not_existing_node = std::make_shared<sgl::node>(node_id_2 + 1);
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(not_existing_node));
        TS_ASSERT_EQUALS(exists, false);
    }
    
    
    
private:
    void add_nodes(sgl::view::adjacency_list_t& view, std::size_t nodes)
    {
        for(sgl::node_id_t node_id = 0; node_id < nodes; ++node_id)
        {
            sgl::node node(node_id);
            sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                std::make_pair(
                    node,
                    sgl::view::adjacency_list::adjacency_nodes_t());
            
            view->list.insert(adjacency_info);
        }
    }
};
