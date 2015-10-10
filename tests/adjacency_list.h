#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/adjacency_list.h>

class adjacency_list_test: public CxxTest::TestSuite
{
public:
    virtual void setUp()
    {
        bool oriented = true;
        bool weighted = true;
        oriented_weighted_view = std::make_shared<sgl::view::adjacency_list>(
            oriented, weighted);
        
        this->not_oriented_not_weighted_view =
            std::make_shared<sgl::view::adjacency_list>();
    }

    
    
private:
    sgl::view::adjacency_list_t oriented_weighted_view;
    sgl::view::adjacency_list_t not_oriented_not_weighted_view;

    
    
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
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 0);
        TS_ASSERT_THROWS_NOTHING(this->oriented_weighted_view->add_node());
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.begin()->first, 1);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list[1].size(), 0);
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_weighted_view->add_node());
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 2);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.begin()->first, 1);
        TS_ASSERT_EQUALS((++this->oriented_weighted_view->list.begin())->first, 2);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list[1].size(), 0);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list[2].size(), 0);
        
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 2);
    }
    
    
    
    void test_add_edge()
    {
        sgl::node_id_t node_id_from = 0;
        sgl::node_id_t node_id_to = 1;
        
        sgl::node_t from = std::make_shared<sgl::node>(node_id_from);
        sgl::node_t to = std::make_shared<sgl::node>(node_id_to);
        
        sgl::weight_t weight = 2;   
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
        
        TS_ASSERT_THROWS_NOTHING(this->oriented_weighted_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 1);
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list[0].size(), 1);
        
        sgl::view::adjacency_list::list_t::const_iterator it =
            this->oriented_weighted_view->list.find(*from);
        
        TS_ASSERT(it != this->oriented_weighted_view->list.end());
        TS_ASSERT_EQUALS(it->first, *from);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, weight);
        
        sgl::weight_t new_weight = edge->get_weight() + 1;
        edge->set_weight(new_weight);
        TS_ASSERT_THROWS_NOTHING(this->oriented_weighted_view->add_edge(edge));
        TS_ASSERT_EQUALS(this->oriented_weighted_view->list.size(), 1);
        
        it = this->oriented_weighted_view->list.find(*from);
        TS_ASSERT(it != this->oriented_weighted_view->list.end());
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        /*TS_ASSERT_THROWS_NOTHING(
            this->not_oriented_not_weighted_view->add_edge(edge));
        TS_ASSERT_EQUALS(
            this->not_oriented_not_weighted_view->list.size(), 2);
        TS_ASSERT_EQUALS(
            this->not_oriented_not_weighted_view->list[0].size(), 1);
        TS_ASSERT_EQUALS(
            this->not_oriented_not_weighted_view->list[1].size(), 1);
        
        it = this->not_oriented_not_weighted_view->list.find(*from);
        TS_ASSERT(it != this->not_oriented_not_weighted_view->list.end());
        TS_ASSERT_EQUALS(it->first, *from);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *to);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        it = this->not_oriented_not_weighted_view->list.find(*to);
        TS_ASSERT_EQUALS(it->first, *to);
        TS_ASSERT_EQUALS(it->second.size(), 1);
        TS_ASSERT_EQUALS(it->second.begin()->first, *from);
        TS_ASSERT_EQUALS(it->second.begin()->second, edge->get_weight());
        
        TS_ASSERT_THROWS(
            this->not_oriented_not_weighted_view->add_edge(edge),
            std::invalid_argument);*/
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
