#include <algorithm>
#include <sgl/view/adjacency_matrix.h>



sgl::view::adjacency_matrix::adjacency_matrix(
    std::size_t nodes, bool oriented, bool weighted)
    : view(oriented, weighted)
    , matrix(nodes, matrix_row_t(nodes))
{

}



sgl::view::adjacency_matrix::~adjacency_matrix()
{

}



void sgl::view::adjacency_matrix::add_node()
{
    std::for_each(this->matrix.begin(), this->matrix.end(),
        [](matrix_row_t& row)
        {
            row.push_back(0);
        });

    this->matrix.push_back(matrix_row_t(this->matrix.size() + 1, 0));
}



void sgl::view::adjacency_matrix::add_edge(const_edge_t edge)
{
    sgl::node_id_t from = edge->get_from()->get_id();
    sgl::node_id_t to = edge->get_to()->get_id();
    sgl::weight_t weight = edge->get_weight();

    if(!this->in_range(from, to))
    {
        throw std::out_of_range("adjacency_matrix::add_edge: "
            "can't add edge: the node with node_id = " +
            std::to_string(std::max(from, to)) +
            " doesn't exists");
    }

    if(weight > 0)
    {
        if(this->exists(edge))
        {
            throw std::invalid_argument("adjacency_matrix::add_edge: "
                "can't add edge (" + edge->to_string() + "): "
                "edge already exists");
        }
        else
        {
            this->matrix[from][to] = weight;

            if(!this->is_oriented())
            {
                this->matrix[to][from] = weight;
            }
        }
    }
}



void sgl::view::adjacency_matrix::remove_node(sgl::const_node_t node)
{
    if(!this->exists(node))
    {
        throw std::invalid_argument("adjacency_matrix::remove_node: "
            "can't remove node: the node with node_id = " +
            std::to_string(node->get_id()) +
            " doesn't exists");
    }

    matrix_t::iterator it = this->matrix.begin() + node->get_id();
    this->matrix.erase(it);

    std::for_each(this->matrix.begin(), this->matrix.end(),
        [&](matrix_row_t& row)
        {
            row.erase(row.begin() + node->get_id());
        });
}



void sgl::view::adjacency_matrix::remove_edge(sgl::const_edge_t edge)
{
    sgl::node_id_t from = edge->get_from()->get_id();
    sgl::node_id_t to = edge->get_to()->get_id();

    if(!this->in_range(from, to))
    {
        throw std::out_of_range("adjacency_matrix::remove_edge: "
            "can't remove edge (" + edge->to_string() + "): "
            "the node with node_id = " +
            std::to_string(std::max(from, to)) +
            " doesn't exists");
    }

    this->matrix[from][to] = 0;

    if(!this->is_oriented())
    {
        this->matrix[to][from] = 0;
    }
}



sgl::const_node_set_t sgl::view::adjacency_matrix::get_nodes() const
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



sgl::const_edge_set_t sgl::view::adjacency_matrix::get_edges() const
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

                    if(!this->is_oriented())
                    {
                        sgl::weight_t backward_weight =
                            this->matrix[column][row];

                        if(backward_weight != weight)
                        {
                            throw std::runtime_error(
                                "adjacency_matrix::get_edges: "
                                "internal matrix corrupted");
                        }

                        sgl::node_t from = std::make_shared<sgl::node>(column);
                        sgl::node_t to = std::make_shared<sgl::node>(row);
                        sgl::edge edge(from, to, backward_weight);

                        edges.insert(edge);
                    }
                }
            }
        }
    }

    return edges;
}



sgl::view::type sgl::view::adjacency_matrix::get_type() const
{
    return sgl::view::type::adjacency_matrix;
}



bool sgl::view::adjacency_matrix::exists(sgl::const_edge_t edge) const
{
    bool exists = true;

    sgl::node_id_t from = edge->get_from()->get_id();
    sgl::node_id_t to = edge->get_to()->get_id();

    if(this->in_range(from, to))
    {
        if(this->is_oriented())
        {
            if(this->matrix[from][to] == 0)
            {
                exists = false;
            }
        }
        else
        {
            if(this->matrix[to][from] == 0 || this->matrix[to][from] == 0)
            {
                exists = false;
            }
        }
    }
    else
    {
        exists = false;
    }

    return exists;
}



bool sgl::view::adjacency_matrix::exists(sgl::const_node_t node) const
{
    bool exists = false;

    std::size_t distance = std::distance(
        this->matrix.begin(),
        this->matrix.begin() + node->get_id());

    if(distance < this->matrix.size())
    {
        exists = true;
    }

    return exists;
}



bool sgl::view::adjacency_matrix::in_range(
    sgl::node_id_t from, sgl::node_id_t to) const
{
    sgl::node_id_t max = std::max(from, to);

    return max < this->matrix.size();
}
