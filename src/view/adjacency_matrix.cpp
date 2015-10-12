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
    sgl::node_id_t from = edge->get_first()->get_id();
    sgl::node_id_t to = edge->get_second()->get_id();
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
    sgl::node_id_t from = edge->get_first()->get_id();
    sgl::node_id_t to = edge->get_second()->get_id();

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



sgl::view::type sgl::view::adjacency_matrix::get_type() const
{
    return sgl::view::type::adjacency_matrix;
}



std::size_t sgl::view::adjacency_matrix::get_nodes_count() const
{
    return this->matrix.size();
}



bool sgl::view::adjacency_matrix::exists(sgl::const_edge_t edge) const
{
    bool exists = true;

    sgl::node_id_t from = edge->get_first()->get_id();
    sgl::node_id_t to = edge->get_second()->get_id();

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



sgl::weight_t sgl::view::adjacency_matrix::get_weight(
    sgl::node_id_t first, sgl::node_id_t second) const
{
    if(!this->in_range(first, second))
    {
        throw std::out_of_range("adjacency_matrix::get_weight(): "
            "can't retrieve a weight of edge: "
            "the node with node_id = " +
            std::to_string(std::max(first, second)) +
            " doesn't exists");
    }

    return this->matrix[first][second];
}



bool sgl::view::adjacency_matrix::in_range(
    sgl::node_id_t from, sgl::node_id_t to) const
{
    sgl::node_id_t max = std::max(from, to);

    return max < this->matrix.size();
}
