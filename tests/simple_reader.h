#pragma once

#include <sstream>
#include <cxxtest/TestSuite.h>
#include <sgl/simple_view_reader.h>

class simple_view_reader_test: public CxxTest::TestSuite
{
public:
	void setUp()
	{
		this->stringstream.str(
			"C 3 1\n"
			"0 2 5\n"
			"2 0 0\n"
			"5 0 0\n");

		this->view_reader = std::make_shared<sgl::simple_view_reader>(
			this->stringstream);

		sgl::node node0(0);
		sgl::node node1(1);
		sgl::node node2(2);

        this->nodes.insert(node0);
		this->nodes.insert(node1);
		this->nodes.insert(node2);

		sgl::weight_t edge0_weight = 2;
		sgl::weight_t edge1_weight = 5;

		this->edges.insert(sgl::edge(node0, node1, edge0_weight));
		this->edges.insert(sgl::edge(node0, node2, edge1_weight));
	}

private:
	std::stringstream stringstream;
	sgl::view_reader_t view_reader;
	sgl::node_set_t nodes;
	sgl::edge_set_t edges;

public:
	void test_read()
	{
		sgl::view_t view;
		TS_ASSERT_THROWS_NOTHING(view = this->view_reader->read());
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
};
