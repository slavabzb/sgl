#include <sgl/view/adjacency_list.h>
#include <algorithm>
#include <iostream>


sgl::view::adjacency_list::adjacency_list(bool oriented, bool weighted)
    : view(oriented, weighted)
{

}



sgl::view::adjacency_list::~adjacency_list()
{

}



void sgl::view::adjacency_list::add_node()
{
    list_t::iterator it = this->list.end();

    if(this->list.size() != 0)
    {
        it = --this->list.end();
    }

    sgl::node_id_t node_id = 1;

    if(it != this->list.end())
    {
        node_id = it->first.get_id() + 1;
    }

    sgl::node node(node_id);
    adjacency_info_t adjacency_info = std::make_pair(node, adjacency_nodes_t());
    this->list.insert(adjacency_info);
}



void sgl::view::adjacency_list::add_edge(const_edge_t edge)
{
    list_t::iterator it = this->list.find(*edge->get_from());

    if(it == this->list.end())
    {
        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
        adjacency_nodes.insert(std::make_pair(
            *edge->get_to(), edge->get_weight()));

        sgl::view::adjacency_list::adjacency_info_t adjacency_info =
            std::make_pair(*edge->get_from(), adjacency_nodes);

        this->list.insert(adjacency_info);

        if(!this->is_oriented())
        {
            it = this->list.find(*edge->get_to());

            if(it == this->list.end())
            {
                sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
                adjacency_nodes.insert(std::make_pair(
                    *edge->get_from(), edge->get_weight()));

                sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                    std::make_pair(*edge->get_to(), adjacency_nodes);

                this->list.insert(adjacency_info);
            }
            else
            {
                it->second.insert(std::make_pair(
                    *edge->get_from(), edge->get_weight()));
            }
        }
    }
    else
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == *edge->get_to())
                    {
                        return true;
                    }

                    return false;
                });

        if(pos != it->second.end())
        {
            it->second.erase(pos);
        }

        it->second.insert(std::make_pair(*edge->get_to(), edge->get_weight()));

        if(!this->is_oriented())
        {
            it = this->list.find(*edge->get_to());

            if(it != this->list.end())
            {
                adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&edge](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == *edge->get_to())
                        {
                            return true;
                        }

                        return false;
                    });

                if(pos != it->second.end())
                {
                    it->second.erase(pos);
                }

                it->second.insert(std::make_pair(
                    *edge->get_from(), edge->get_weight()));
            }
            else
            {
                throw std::runtime_error("adjacency_list::add_edge: "
                    "internal list corrupted");
            }
        }
    }
}



void sgl::view::adjacency_list::remove_node(sgl::const_node_t node)
{
    list_t::const_iterator it = this->list.find(*node);

    if(it == this->list.end())
    {
        return;
    }
}



void sgl::view::adjacency_list::remove_edge(sgl::const_edge_t edge)
{

}



sgl::const_node_set_t sgl::view::adjacency_list::get_nodes() const
{
    sgl::node_set_t nodes;

    return nodes;
}



sgl::const_edge_set_t sgl::view::adjacency_list::get_edges() const
{
    sgl::edge_set_t edges;

    return edges;
}



sgl::view::type sgl::view::adjacency_list::get_type() const
{
    return sgl::view::type::adjacency_list;
}



bool sgl::view::adjacency_list::exists(sgl::const_edge_t edge) const
{
    bool exists = true;

    list_t::const_iterator it = this->list.end();
    it = this->list.find(*edge->get_from());
    exists = it != this->list.end();

    return exists;
}



bool sgl::view::adjacency_list::exists(sgl::const_node_t node) const
{
    bool exists = false;



    return exists;
}



bool sgl::view::adjacency_list::in_range(
    const sgl::node& from, const sgl::node& to) const
{

}
