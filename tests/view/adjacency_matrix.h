#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/edge_list.h>



class adjacency_matrix_test: public CxxTest::TestSuite
{
public:
    virtual void setUp()
    {
        this->view = std::make_shared<sgl::view::adjacency_matrix>();
    }

    
    
private:
    sgl::view::adjacency_matrix_t view;

    
    
public:
    void test_constructor()
    {
        sgl::view::adjacency_matrix_t adjacency_matrix_view;

        TS_ASSERT_THROWS_NOTHING(adjacency_matrix_view =
            std::make_shared<sgl::view::adjacency_matrix>());

        TS_ASSERT(adjacency_matrix_view);
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.size(), 0);

        std::size_t nodes = 2;
        TS_ASSERT_THROWS_NOTHING(adjacency_matrix_view =
            std::make_shared<sgl::view::adjacency_matrix>(nodes));
        TS_ASSERT(adjacency_matrix_view);
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.size(), nodes);
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.at(0).size(), nodes);
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.at(1).size(), nodes);
    }

    
    
    void test_add_node()
    {
        TS_ASSERT_THROWS_NOTHING(this->view->add_node(0));
        TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
    }

    
    
    void test_remove_node()
    {
        std::size_t nodes = 2;
        this->add_nodes(nodes);
        this->view->matrix.at(0).at(0) = 0;
        this->view->matrix.at(0).at(1) = 1;
        this->view->matrix.at(1).at(0) = 2;
        this->view->matrix.at(1).at(1) = 3;

        sgl::core::node node(0);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_node(node));

        TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 3);

        sgl::core::node bad_node(node.get_id() + 1);
        TS_ASSERT_THROWS(
            this->view->remove_node(bad_node),
            std::invalid_argument);
    }

       
    
    void test_add_edge()
    {
        sgl::core::edge edge(0, 1, 1);

        TS_ASSERT_THROWS(this->view->add_edge(edge), std::out_of_range);

        this->add_nodes(2);
        TS_ASSERT_THROWS_NOTHING(this->view->add_edge(edge));
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), edge.get_weight());
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), edge.get_weight());
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
        
        TS_ASSERT_THROWS_NOTHING(this->view->add_edge(edge));
    }

        
        
    void test_remove_edge()
    {
        sgl::core::edge edge(0, 1, 1);

        TS_ASSERT_THROWS(this->view->remove_edge(edge), std::out_of_range);

        std::size_t nodes = 2;
        this->add_nodes(nodes);
        this->add_edge(edge);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_edge(edge));
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
    }

        
        
    void test_exists()
    {
        sgl::core::edge edge(0, 1, 1);
        
        TS_ASSERT(!this->view->exists(edge));
        TS_ASSERT(!this->view->exists(edge.get_first()));
        TS_ASSERT(!this->view->exists(edge.get_second()));
        
        const std::size_t nodes = 2;
        this->add_nodes(nodes);
        
        TS_ASSERT(!this->view->exists(edge));
        TS_ASSERT(this->view->exists(edge.get_first()));
        TS_ASSERT(this->view->exists(edge.get_second()));
        
        this->add_edge(edge);
        
        TS_ASSERT(this->view->exists(edge));
        TS_ASSERT(this->view->exists(edge.get_first()));
        TS_ASSERT(this->view->exists(edge.get_second()));
    }
    
    
    
    void test_get_weight()
    {
        std::size_t nodes = 2;
        this->add_nodes(nodes);
        
        const sgl::core::weight_t weight = 1;
        this->view->matrix.at(0).at(0) = 0;
        this->view->matrix.at(0).at(1) = weight;
        this->view->matrix.at(1).at(0) = weight;
        this->view->matrix.at(1).at(1) = 0;
        
        sgl::core::weight_t weight_retrieved = 0;
        TS_ASSERT_THROWS_NOTHING(
            weight_retrieved = this->view->get_edge_weight(0, 1));
        TS_ASSERT_EQUALS(weight_retrieved, weight);
                
        TS_ASSERT_THROWS(
            this->view->get_edge_weight(0, 2),
            std::out_of_range);
    }
    
    
    
    void test_get_nodes()
    {
        sgl::core::node_set_t nodes;
        nodes.insert(0);
        nodes.insert(1);
        
        std::size_t nodes_count = 2;
        this->add_nodes(nodes_count);
        
        TS_ASSERT_EQUALS(this->view->get_nodes(), nodes);
    }
    
    
    
    void test_get_edges()
    {
        std::size_t nodes = 2;
        this->add_nodes(nodes);
        
        sgl::core::edge edge(0, 1, 1);
        this->add_edge(edge);
        
        sgl::core::edge_set_t edges;
        edges.insert(sgl::core::edge(0, 1, 1));
        
        TS_ASSERT_EQUALS(this->view->get_edges(), edges);
    }
    
    
    
    void test_conversion()
    {
        {
            sgl::view::adjacency_matrix rhs(5, 0, 1);
            TS_ASSERT_THROWS(*this->view = rhs, std::invalid_argument);
        }
        
        {
            sgl::view::adjacency_matrix rhs(5);
            rhs.add_node(0);
            rhs.add_node(1);
            rhs.add_edge(sgl::core::edge(0, 1, 2));
            
            TS_ASSERT_THROWS_NOTHING(*this->view = rhs);
            TS_ASSERT_EQUALS(*this->view, rhs);
        }
        
        {
            sgl::view::adjacency_list rhs;
            rhs.add_node(0);
            rhs.add_node(1);
            rhs.add_edge(sgl::core::edge(0, 1, 2));
            
            TS_ASSERT_THROWS_NOTHING(*this->view = rhs);            
            TS_ASSERT_EQUALS(this->view->get_edges().size(), 1);
            TS_ASSERT_EQUALS(rhs.get_edges().size(), 1);
            TS_ASSERT_EQUALS(this->view->get_edges().begin()->get_first(), rhs.get_edges().begin()->get_first());
            TS_ASSERT_EQUALS(this->view->get_edges().begin()->get_second(), rhs.get_edges().begin()->get_second());
            TS_ASSERT_EQUALS(this->view->get_nodes(), rhs.get_nodes());
        }
        
        {
            sgl::view::edge_list rhs;
            rhs.add_node(0);
            rhs.add_node(1);
            rhs.add_edge(sgl::core::edge(0, 1, 2));
            
            TS_ASSERT_THROWS_NOTHING(*this->view = rhs);            
            TS_ASSERT_EQUALS(this->view->get_edges().size(), 1);
            TS_ASSERT_EQUALS(rhs.get_edges().size(), 1);
            TS_ASSERT_EQUALS(this->view->get_edges().begin()->get_first(), rhs.get_edges().begin()->get_first());
            TS_ASSERT_EQUALS(this->view->get_edges().begin()->get_second(), rhs.get_edges().begin()->get_second());
            TS_ASSERT_EQUALS(this->view->get_nodes(), rhs.get_nodes());
        }
    }
    
    
    
private:
    void add_nodes(std::size_t nodes)
    {
        for(std::size_t node = 0; node < nodes; ++node)
        {
            this->view->matrix.push_back(
                sgl::view::adjacency_matrix::matrix_row_t(nodes));
        }
    }

        
        
    void add_edge(const sgl::core::edge& edge)
    {
        this->view->matrix
            .at(edge.get_first().get_id())
                .at(edge.get_second().get_id()) =
                    edge.get_weight();
        
        this->view->matrix
            .at(edge.get_second().get_id())
                .at(edge.get_first().get_id()) =
                    edge.get_weight();
    }
};
