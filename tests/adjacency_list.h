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
        TS_ASSERT_EQUALS(this->oriented_view->list.begin()->first, 0);
        TS_ASSERT_EQUALS(this->oriented_view->list.at(0).size(), 0);
        
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_node());
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->oriented_view->list.begin()->first, 0);
        TS_ASSERT_EQUALS((++this->oriented_view->list.begin())->first, 1);
        TS_ASSERT_EQUALS(this->oriented_view->list.at(0).size(), 0);
        TS_ASSERT_EQUALS(this->oriented_view->list.at(1).size(), 0);
        
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 2);
    }
    
    
    
    void test_oriented_view_add_edge()
    {   
        sgl::edge edge(0, 1, 2);
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_view->list[0].size(), 1);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->oriented_view->list.find(edge.get_first());
        
        TS_ASSERT(it != this->oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, edge.get_first());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
        
        edge.set_weight(edge.get_weight() + 1);
        TS_ASSERT_THROWS_NOTHING(this->oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_view->list.size(), 1);
        
        it = this->oriented_view->list.find(edge.get_first());
        TS_ASSERT(it != this->oriented_view->list.end());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
    }
    
    
    
    void test_not_oriented_view_add_edge()
    {   
        sgl::edge edge(0, 1, 2);
        
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[0].size(), 1);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[1].size(), 1);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(edge.get_first());
        
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, edge.get_first());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
        
        it = this->not_oriented_view->list.find(edge.get_second());
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_first());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
        
        edge.set_weight(edge.get_weight() + 1);
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[0].size(), 1);
        TS_ASSERT_EQUALS(this->not_oriented_view->list[1].size(), 1);
        
        it = this->not_oriented_view->list.find(edge.get_first());
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, edge.get_first());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
        
        it = this->not_oriented_view->list.find(edge.get_second());
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, edge.get_second());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, edge.get_first());
        TS_ASSERT_EQUALS(it->second.begin()->second, edge.get_weight());
    }
    
    
    
    void test_remove_node()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        
        sgl::node node0(0);
        sgl::node node1(1);
        sgl::node node2(2);
        
        this->not_oriented_view->list[0].insert(std::make_pair(node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(node0, weight1));
        
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->remove_node(node1));
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 2);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(node0);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, node0);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, node2);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
        
        it = this->not_oriented_view->list.find(node1);
        TS_ASSERT_EQUALS(it, this->not_oriented_view->list.end());
        
        it = this->not_oriented_view->list.find(node2);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, node2);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, node0);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
    }
    
    
    
    void test_remove_edge()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        
        sgl::node node0(0);
        sgl::node node1(1);
        sgl::node node2(2);
                
        this->not_oriented_view->list[0].insert(std::make_pair(node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(node0, weight1));
        
        sgl::edge edge(node0, node1, weight0);
        TS_ASSERT_THROWS_NOTHING(this->not_oriented_view->remove_edge(edge));
        
        TS_ASSERT_EQUALS(this->not_oriented_view->list.size(), 3);
        
         sgl::view::adjacency_list::list_t::const_iterator it =
            this->not_oriented_view->list.find(node0);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, node0);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, node2);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
        
        it = this->not_oriented_view->list.find(node1);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, node1);
        TS_ASSERT_EQUALS(it->second.size(), 0);
        
        it = this->not_oriented_view->list.find(node2);
        TS_ASSERT(it != this->not_oriented_view->list.end());
        TS_ASSERT_EQUALS(it->first, node2);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, node0);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight1);
    }
    
    
    
    void test_exists()
    {
        const std::size_t nodes = 3;
        this->add_nodes(this->not_oriented_view, nodes);
        
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        
        sgl::node node0(0);
        sgl::node node1(1);
        sgl::node node2(2);
                
        this->not_oriented_view->list[0].insert(std::make_pair(node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(node0, weight1));
        
        sgl::edge existing_edge(node0, node1, weight0);
        sgl::edge not_existing_edge(node1, node2, weight0);
        
        bool exists = false;
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(existing_edge));
        TS_ASSERT_EQUALS(exists, true);
        
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(not_existing_edge));
        TS_ASSERT_EQUALS(exists, false);
        
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(node0));
        TS_ASSERT_EQUALS(exists, true);      
        
        sgl::node not_existing_node(node2.get_id() + 1);
        TS_ASSERT_THROWS_NOTHING(exists = this->not_oriented_view->exists(not_existing_node));
        TS_ASSERT_EQUALS(exists, false);
    }
    
    
    
    void test_get_nodes()
    {
        const std::size_t nodes_count = 3;
        this->add_nodes(this->oriented_view, nodes_count);
        
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        
        sgl::node node0(0);
        sgl::node node1(1);
        sgl::node node2(2);
                
        this->oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->oriented_view->list[1].insert(std::make_pair(node0, weight0));
        
        sgl::node_set_t nodes;
        nodes.insert(node0);
        nodes.insert(node1);
        nodes.insert(node2);
        
        TS_ASSERT_EQUALS(this->oriented_view->get_nodes(), nodes);
    }
    
    
    
    void test_get_edges()
    {
        const std::size_t nodes_count = 3;
        this->add_nodes(this->oriented_view, nodes_count);
        this->add_nodes(this->not_oriented_view, nodes_count);
        
        sgl::weight_t weight0 = 2;
        sgl::weight_t weight1 = 5;
        
        sgl::node node0(0);
        sgl::node node1(1);
        sgl::node node2(2);
                
        this->oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->oriented_view->list[1].insert(std::make_pair(node0, weight0));
        
        this->not_oriented_view->list[0].insert(std::make_pair(node1, weight0));
        this->not_oriented_view->list[0].insert(std::make_pair(node2, weight1));
        this->not_oriented_view->list[1].insert(std::make_pair(node0, weight0));
        this->not_oriented_view->list[2].insert(std::make_pair(node0, weight1));
        
        sgl::edge_set_t edges;
        edges.insert(sgl::edge(node0, node2, weight1));
        edges.insert(sgl::edge(node1, node0, weight0));
        
        TS_ASSERT_EQUALS(this->oriented_view->get_edges(), edges);
        
        edges.clear();
        edges.insert(sgl::edge(node0, node1, weight0));
        edges.insert(sgl::edge(node0, node2, weight1));
        
        TS_ASSERT_EQUALS(this->not_oriented_view->get_edges(), edges);
    }
    
    
    
    
private:
    void add_nodes(sgl::view::adjacency_list_t& view, std::size_t nodes)
    {
        for(sgl::node_id_t node_id = 0; node_id < nodes; ++node_id)
        {
            sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                std::make_pair(
                    node_id,
                    sgl::view::adjacency_list::adjacency_nodes_t());
            
            view->list.insert(adjacency_info);
        }
    }
};
