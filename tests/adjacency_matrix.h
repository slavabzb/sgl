#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/view/adjacency_matrix.h>

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
        TS_ASSERT_THROWS_NOTHING(this->view->add_node());
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

        sgl::node_id_t node_id = 0;
        sgl::node_t node = std::make_shared<sgl::node>(node_id);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_node(node));

        TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).size(), 1);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 3);

        sgl::node_t bad_node = std::make_shared<sgl::node>(node_id + 1);
        TS_ASSERT_THROWS(
            this->view->remove_node(bad_node),
            std::invalid_argument
        );
    }

       
    
    void test_add_edge()
    {
        sgl::node_t from = std::make_shared<sgl::node>(0);
        sgl::node_t to = std::make_shared<sgl::node>(1);
        sgl::weight_t weight = 1;
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);

        TS_ASSERT_THROWS(this->view->add_edge(edge), std::out_of_range);

        this->add_nodes(2);
        TS_ASSERT_THROWS_NOTHING(this->view->add_edge(edge));
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), weight);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), weight);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
        
        TS_ASSERT_THROWS(this->view->add_edge(edge), std::invalid_argument);
    }

        
        
    void test_remove_edge()
    {
        sgl::node_id_t node_id_from = 0;
        sgl::node_id_t node_id_to = 1;
        sgl::weight_t weight = 1;

        sgl::node_t from = std::make_shared<sgl::node>(node_id_from);
        sgl::node_t to = std::make_shared<sgl::node>(node_id_to);
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);

        TS_ASSERT_THROWS(this->view->remove_edge(edge), std::out_of_range);

        std::size_t nodes = 2;
        this->add_nodes(nodes);
        this->add_edge(node_id_from, node_id_to, weight);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_edge(edge));
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), 0);
        TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
    }

        
        
    void test_exists()
    {
        sgl::node_id_t node_id_from = 0;
        sgl::node_id_t node_id_to = 1;
        sgl::weight_t weight = 1;

        sgl::node_t from = std::make_shared<sgl::node>(node_id_from);
        sgl::node_t to = std::make_shared<sgl::node>(node_id_to);
        sgl::edge_t edge = std::make_shared<sgl::edge>(from, to, weight);
        
        TS_ASSERT(!this->view->exists(edge));
        TS_ASSERT(!this->view->exists(from));
        TS_ASSERT(!this->view->exists(to));
        
        const std::size_t nodes = 2;
        this->add_nodes(nodes);
        
        TS_ASSERT(!this->view->exists(edge));
        TS_ASSERT(this->view->exists(from));
        TS_ASSERT(this->view->exists(to));
        
        this->add_edge(node_id_from, node_id_to, weight);
        
        TS_ASSERT(this->view->exists(edge));
        TS_ASSERT(this->view->exists(from));
        TS_ASSERT(this->view->exists(to));
    }
    
    
    
    void test_get_weight()
    {
        std::size_t nodes = 2;
        this->add_nodes(nodes);
        
        const sgl::weight_t weight = 1;
        this->view->matrix.at(0).at(0) = 0;
        this->view->matrix.at(0).at(1) = weight;
        this->view->matrix.at(1).at(0) = weight;
        this->view->matrix.at(1).at(1) = 0;
        
        sgl::weight_t weight_retrieved = 0;
        TS_ASSERT_THROWS_NOTHING(
            weight_retrieved = this->view->get_weight(0, 1));
        TS_ASSERT_EQUALS(weight_retrieved, weight);
                
        TS_ASSERT_THROWS(
            this->view->get_weight(0, 2),
            std::out_of_range);
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

        
        
    void add_edge(sgl::node_id_t from, sgl::node_id_t to, sgl::weight_t weight)
    {
        this->view->matrix.at(from).at(to) = weight;
        this->view->matrix.at(to).at(from) = weight;
    }
};
