#include <algorithm>
#include <iostream>
#include <sgl/adjacency_matrix_view.h>



sgl::adjacency_matrix_view::adjacency_matrix_view(std::size_t nodes)
    : matrix(nodes, matrix_row_t(nodes))
{

}



sgl::adjacency_matrix_view::~adjacency_matrix_view()
{

}



void sgl::adjacency_matrix_view::add_node()
{
    std::for_each(this->matrix.begin(), this->matrix.end(),
        [](matrix_row_t& row)
        {
            row.push_back(0);
        });

    this->matrix.push_back(matrix_row_t(this->matrix.size() + 1, 0));
}



void sgl::adjacency_matrix_view::add_edge(sgl::const_edge_t edge)
{
    sgl::node_id_t from = edge->get_from()->get_id();
    sgl::node_id_t to = edge->get_to()->get_id();
    sgl::weight_t weight = edge->get_weight();
    sgl::node_id_t max = std::max(from, to);
    bool in_range = (max < this->matrix.size());

    if(!in_range)
    {
        throw std::invalid_argument("adjacency_matrix_view::add_edge: "
            "can't add edge: the node with node_id = " +
            std::to_string(max) +
            " doesn't exists");
    }

    if(weight > 0)
    {
        this->matrix[from][to] = weight;
        this->matrix[to][from] = weight;
    }
}



void sgl::adjacency_matrix_view::remove_node(sgl::const_node_t node)
{
    matrix_t::iterator it = this->matrix.begin() + node->get_id();
    std::size_t distance = std::distance(this->matrix.begin(), it);

    if(distance >= this->matrix.size())
    {
        throw std::invalid_argument("adjacency_matrix_view::remove_node: "
            "can't remove node: the node with node_id = " +
            std::to_string(distance) +
            " doesn't exists");
    }

    this->matrix.erase(it);

    std::for_each(this->matrix.begin(), this->matrix.end(),
        [&](matrix_row_t& row)
        {
            row.erase(row.begin() + node->get_id());
        });
}



void sgl::adjacency_matrix_view::remove_edge(sgl::const_edge_t edge)
{
	sgl::node_id_t from = edge->get_from()->get_id();
    sgl::node_id_t to = edge->get_to()->get_id();
    sgl::node_id_t max = std::max(from, to);
    bool in_range = (max < this->matrix.size());
	
    if(!in_range)
    {
        throw std::invalid_argument("adjacency_matrix_view::remove_edge: "
            "can't remove edge: the node with node_id = " +
            std::to_string(max) +
            " doesn't exists");
    }
	
	this->matrix[from][to] = 0;
	this->matrix[to][from] = 0;
}



sgl::node_set_t sgl::adjacency_matrix_view::get_nodes()
{
    sgl::node_set_t nodes;

    for(matrix_t::size_type node_id = 0; node_id < this->matrix.size();
        ++node_id)
    {
        sgl::node node(node_id);
        nodes.insert(node);
    }

    return nodes;
}



sgl::edge_set_t sgl::adjacency_matrix_view::get_edges()
{
    sgl::edge_set_t edges;

	if(this->matrix.size() > 0)
	{
		for(matrix_t::size_type row = 0; row < this->matrix.size() - 1; ++row)
		{
			for(matrix_row_t::size_type column = row + 1;
				column < this->matrix[row].size(); ++column)
			{
				sgl::weight_t weight = this->matrix[row][column];

				if(weight != 0)
				{
					sgl::node_t from = std::make_shared<sgl::node>(row);
					sgl::node_t to = std::make_shared<sgl::node>(column);
					sgl::edge edge(from, to, weight);
					edges.insert(edge);
				}
			}
		}
	}

    return edges;
}
