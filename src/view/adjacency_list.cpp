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
    list_t::iterator it = this->list.find(*edge->get_first());

    if(it == this->list.end())
    {
        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
        adjacency_nodes.insert(std::make_pair(
            *edge->get_second(), edge->get_weight()));

        sgl::view::adjacency_list::adjacency_info_t adjacency_info =
            std::make_pair(*edge->get_first(), adjacency_nodes);

        this->list.insert(adjacency_info);

        if(!this->is_oriented())
        {
            it = this->list.find(*edge->get_second());

            if(it == this->list.end())
            {
                sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
                adjacency_nodes.insert(std::make_pair(
                    *edge->get_first(), edge->get_weight()));

                sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                    std::make_pair(*edge->get_second(), adjacency_nodes);

                this->list.insert(adjacency_info);
            }
            else
            {
                it->second.insert(std::make_pair(
                    *edge->get_first(), edge->get_weight()));
            }
        }
    }
    else
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == *edge->get_second())
                    {
                        return true;
                    }

                    return false;
                });

        if(pos != it->second.end())
        {
            it->second.erase(pos);
        }

        it->second.insert(std::make_pair(*edge->get_second(), edge->get_weight()));

        if(!this->is_oriented())
        {
            it = this->list.find(*edge->get_second());

            if(it != this->list.end())
            {
                adjacency_nodes_t::const_iterator pos =
                    std::find_if(it->second.begin(), it->second.end(),
                        [&edge](const edge_info_t& edge_info)
                        {
                            if(edge_info.first == *edge->get_first())
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
                    *edge->get_first(), edge->get_weight()));
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
    for(list_t::iterator it = this->list.begin(); it != this->list.end(); ++it)
    {
        if(it->first == *node)
        {
            this->list.erase(it);
        }
        else
        {
            adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&node](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == *node)
                        {
                            return true;
                        }

                        return false;
                    });

            if(pos != it->second.end())
            {
                it->second.erase(pos);
            }
        }
    }
}



void sgl::view::adjacency_list::remove_edge(sgl::const_edge_t edge)
{
    list_t::iterator it = this->list.find(*edge->get_first());

    if(it != this->list.end())
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == *edge->get_second() &&
                       edge_info.second == edge->get_weight())
                    {
                        return true;
                    }

                    return false;
                });

        if(pos != it->second.end())
        {
            it->second.erase(pos);
        }

        it = this->list.find(*edge->get_second());

        if(it != this->list.end())
        {
            adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&edge](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == *edge->get_first() &&
                           edge_info.second == edge->get_weight())
                        {
                            return true;
                        }

                        return false;
                    });

            if(pos != it->second.end())
            {
                it->second.erase(pos);
            }
        }
        else
        {
            throw std::runtime_error("adjacency_list::remove_edge: "
                "internal list corrupted");
        }
    }
}



sgl::view::type sgl::view::adjacency_list::get_type() const
{
    return sgl::view::type::adjacency_list;
}



std::size_t sgl::view::adjacency_list::get_nodes_count() const
{
    // TODO
    return 0;
}



bool sgl::view::adjacency_list::exists(sgl::const_edge_t edge) const
{
    bool exists = false;

    list_t::const_iterator it = this->list.find(*edge->get_first());

    if(it != this->list.end())
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == *edge->get_second() &&
                       edge_info.second == edge->get_weight())
                    {
                        return true;
                    }

                    return false;
                });

        if(pos != it->second.end())
        {
            exists = true;
        }
    }

    return exists;
}



bool sgl::view::adjacency_list::exists(sgl::const_node_t node) const
{
    bool exists = false;

    list_t::const_iterator it = this->list.find(*node);

    if(it != this->list.end())
    {
        exists = true;
    }
    else
    {
        for(list_t::const_iterator it = this->list.begin();
            it != this->list.end(); ++it)
        {
            adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&node](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == *node)
                        {
                            return true;
                        }

                        return false;
                    });

            if(pos != it->second.end())
            {
                exists = true;
                break;
            }
        }
    }

    return exists;
}
