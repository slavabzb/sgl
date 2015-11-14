#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/algo/prim.h>
#include <sgl/view/adjacency_list.h>



class prim_test: public CxxTest::TestSuite
{
    sgl::view::adjacency_list_t view;
    sgl::view::adjacency_list_t minimal_spanning_tree;
    
public:
    virtual void setUp() override
    {
        bool oriented = false;
        bool weighted = true;
        this->view = std::make_shared<sgl::view::adjacency_list>(oriented, weighted);
        
        this->view->add_edge(sgl::core::edge(0, 1, 7));
        this->view->add_edge(sgl::core::edge(0, 3, 5));
        this->view->add_edge(sgl::core::edge(1, 3, 9));
        this->view->add_edge(sgl::core::edge(1, 2, 8));
        this->view->add_edge(sgl::core::edge(1, 4, 7));
        this->view->add_edge(sgl::core::edge(2, 4, 5));
        this->view->add_edge(sgl::core::edge(3, 4, 15));
        this->view->add_edge(sgl::core::edge(3, 5, 6));
        this->view->add_edge(sgl::core::edge(4, 5, 8));
        this->view->add_edge(sgl::core::edge(4, 6, 9));
        this->view->add_edge(sgl::core::edge(5, 6, 11));
        
        this->minimal_spanning_tree = std::make_shared<sgl::view::adjacency_list>(oriented, weighted);
        this->minimal_spanning_tree = this->view;
        this->minimal_spanning_tree->remove_edge(sgl::core::edge(1, 3, 9));
        this->minimal_spanning_tree->remove_edge(sgl::core::edge(1, 2, 8));
        this->minimal_spanning_tree->remove_edge(sgl::core::edge(3, 4, 15));
        this->minimal_spanning_tree->remove_edge(sgl::core::edge(4, 5, 8));
        this->minimal_spanning_tree->remove_edge(sgl::core::edge(5, 6, 11));
    }
    
    void test_prim()
    {
        sgl::view::view_t minimal_spanning_tree = sgl::algo::prim(this->view);

        TS_ASSERT_EQUALS(minimal_spanning_tree->get_edges(), this->minimal_spanning_tree->get_edges());
        TS_ASSERT_EQUALS(minimal_spanning_tree->get_nodes(), this->minimal_spanning_tree->get_nodes());
    }
};
