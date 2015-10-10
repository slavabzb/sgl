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
        TS_ASSERT_EQUALS(adjacency_matrix_view->matrix.size(), 0);

		std::size_t nodes = 2;
		TS_ASSERT_THROWS_NOTHING(adjacency_matrix_view =
            std::make_shared<sgl::adjacency_matrix_view>(nodes));
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
        sgl::node node(node_id);

        TS_ASSERT_THROWS_NOTHING(this->view->remove_node(node));

		TS_ASSERT_EQUALS(this->view->matrix.size(), 1);
		TS_ASSERT_EQUALS(this->view->matrix.at(0).size(), 1);
		TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 3);

		sgl::node bad_node(node_id + 1);
        TS_ASSERT_THROWS(this->view->remove_node(bad_node), std::invalid_argument);
    }

    void test_get_nodes()
    {
        sgl::node_set_t node_set;
        TS_ASSERT_THROWS_NOTHING(node_set = this->view->get_nodes());
        TS_ASSERT_EQUALS(node_set.size(), 0);

		std::size_t nodes = 2;
        this->add_nodes(nodes);

        TS_ASSERT_THROWS_NOTHING(node_set = this->view->get_nodes());
        TS_ASSERT_EQUALS(node_set.size(), nodes);
        TS_ASSERT_EQUALS(node_set.begin()->get_id(), 0);
        TS_ASSERT_EQUALS((++node_set.begin())->get_id(), 1);
    }

    void test_add_edge()
    {
        sgl::node from(0);
        sgl::node to(1);
        sgl::weight_t weight = 1;
        sgl::edge edge(from, to, weight);

        TS_ASSERT_THROWS(this->view->add_edge(edge), std::invalid_argument);

		this->add_nodes(2);
		TS_ASSERT_THROWS_NOTHING(this->view->add_edge(edge));
		TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
		TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), 1);
		TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), 1);
		TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
    }

	void test_get_edges()
	{
		sgl::edge_set_t edges;
		TS_ASSERT_THROWS_NOTHING(edges = this->view->get_edges());
		TS_ASSERT_EQUALS(edges.size(), 0);

		std::size_t nodes = 2;
		this->add_nodes(nodes);

		sgl::node_id_t node_id_from = 0;
		sgl::node_id_t node_id_to = 1;
		sgl::weight_t weight = 1;
		this->add_edge(node_id_from, node_id_to, weight);

		TS_ASSERT_THROWS_NOTHING(edges = this->view->get_edges());
		TS_ASSERT_EQUALS(edges.size(), 1);

		sgl::node from(node_id_from);
        sgl::node to(node_id_to);
        sgl::edge edge(from, to, weight);
		TS_ASSERT(edges.find(edge) != edges.end());
	}

	void test_remove_edge()
	{
		sgl::node_id_t node_id_from = 0;
		sgl::node_id_t node_id_to = 1;
		sgl::weight_t weight = 1;

		sgl::node from(node_id_from);
        sgl::node to(node_id_to);
        sgl::edge edge(from, to, weight);

		TS_ASSERT_THROWS(this->view->remove_edge(edge), std::invalid_argument);

		std::size_t nodes = 2;
		this->add_nodes(nodes);
		this->add_edge(node_id_from, node_id_to, weight);

		TS_ASSERT_THROWS_NOTHING(this->view->remove_edge(edge));
		TS_ASSERT_EQUALS(this->view->matrix.at(0).at(0), 0);
		TS_ASSERT_EQUALS(this->view->matrix.at(0).at(1), 0);
		TS_ASSERT_EQUALS(this->view->matrix.at(1).at(0), 0);
		TS_ASSERT_EQUALS(this->view->matrix.at(1).at(1), 0);
	}

private:
	void add_nodes(std::size_t nodes)
	{
		for(std::size_t node = 0; node < nodes; ++node)
		{
			this->view->matrix.push_back(
				sgl::adjacency_matrix_view::matrix_row_t(nodes));
		}
	}

	void add_edge(sgl::node_id_t from, sgl::node_id_t to, sgl::weight_t weight)
	{
		this->view->matrix.at(from).at(to) = weight;
		this->view->matrix.at(to).at(from) = weight;
	}
};
