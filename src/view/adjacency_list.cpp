#include <sgl/view/adjacency_list.h>
#include <algorithm>



sgl::view::adjacency_list::adjacency_list(bool oriented, bool weighted)
    : base_t(oriented, weighted)
{

}



sgl::view::adjacency_list::adjacency_list(const sgl::view::view& other)
    : base_t(other.is_oriented(), other.is_weighted())
{
    *this = other;
}



sgl::view::adjacency_list::~adjacency_list()
{

}



void sgl::view::adjacency_list::add_node(const sgl::core::node& node)
{
    adjacency_info_t adjacency_info = std::make_pair(node, adjacency_nodes_t());
    this->list.insert(adjacency_info);
}



void sgl::view::adjacency_list::add_edge(const sgl::core::edge& edge)
{
    list_t::iterator it = this->list.find(edge.get_first());

    if(it == this->list.end())
    {
        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
        adjacency_nodes.insert(std::make_pair(
            edge.get_second(), edge.get_weight()));

        sgl::view::adjacency_list::adjacency_info_t adjacency_info =
            std::make_pair(edge.get_first(), adjacency_nodes);

        this->list.insert(adjacency_info);

        if(!this->is_oriented())
        {
            it = this->list.find(edge.get_second());

            if(it == this->list.end())
            {
                sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
                adjacency_nodes.insert(std::make_pair(
                    edge.get_first(), edge.get_weight()));

                sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                    std::make_pair(edge.get_second(), adjacency_nodes);

                this->list.insert(adjacency_info);
            }
            else
            {
                it->second.insert(std::make_pair(
                    edge.get_first(), edge.get_weight()));
            }
        }
    }
    else
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == edge.get_second())
                    {
                        return true;
                    }

                    return false;
                });

        if(pos != it->second.end())
        {
            it->second.erase(pos);
        }

        it->second.insert(std::make_pair(edge.get_second(), edge.get_weight()));

        if(!this->is_oriented())
        {
            it = this->list.find(edge.get_second());

            if(it != this->list.end())
            {
                adjacency_nodes_t::const_iterator pos =
                    std::find_if(it->second.begin(), it->second.end(),
                        [&edge](const edge_info_t& edge_info)
                        {
                            if(edge_info.first == edge.get_first())
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
                    edge.get_first(), edge.get_weight()));
            }
            else
            {
                sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes;
                adjacency_nodes.insert(std::make_pair(
                    edge.get_first(), edge.get_weight()));

                sgl::view::adjacency_list::adjacency_info_t adjacency_info =
                    std::make_pair(edge.get_second(), adjacency_nodes);

                this->list.insert(adjacency_info);
            }
        }
    }
}



void sgl::view::adjacency_list::remove_node(const sgl::core::node& node)
{
    for(list_t::iterator it = this->list.begin(); it != this->list.end(); ++it)
    {
        if(it->first == node)
        {
            this->list.erase(it);
        }
        else
        {
            adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&node](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == node)
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



void sgl::view::adjacency_list::remove_edge(const sgl::core::edge& edge)
{
    list_t::iterator it = this->list.find(edge.get_first());

    if(it != this->list.end())
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == edge.get_second() &&
                       edge_info.second == edge.get_weight())
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

    if(!this->is_oriented())
    {
        it = this->list.find(edge.get_second());

        if(it != this->list.end())
        {
            adjacency_nodes_t::const_iterator pos =
                std::find_if(it->second.begin(), it->second.end(),
                    [&edge](const edge_info_t& edge_info)
                    {
                        if(edge_info.first == edge.get_first() &&
                           edge_info.second == edge.get_weight())
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



sgl::view::type sgl::view::adjacency_list::get_type() const
{
    return sgl::view::type::adjacency_list;
}



sgl::core::node_set_t sgl::view::adjacency_list::get_nodes() const
{
    sgl::core::node_set_t nodes;

    for(const adjacency_info_t& adjacency_info : this->list)
    {
        nodes.insert(adjacency_info.first);

        for(const edge_info_t& edge_info : adjacency_info.second)
        {
            nodes.insert(edge_info.first);
        }
    }

    return nodes;
}



sgl::core::edge_set_t sgl::view::adjacency_list::get_edges() const
{
    sgl::core::edge_set_t edges;

    for(const adjacency_info_t& adjacency_info : this->list)
    {
        for(const edge_info_t& edge_info : adjacency_info.second)
        {
            sgl::core::edge edge_forward(adjacency_info.first, edge_info.first, edge_info.second);
            sgl::core::edge edge_backward(edge_info.first, adjacency_info.first, edge_info.second);

            sgl::core::edge_set_t::const_iterator it_forward = edges.find(edge_forward);
            sgl::core::edge_set_t::const_iterator it_backward = edges.find(edge_backward);

            if(it_forward == edges.end() && it_backward == edges.end())
            {
                edges.insert(edge_forward);
            }
        }
    }

    return edges;
}



bool sgl::view::adjacency_list::exists(const sgl::core::edge& edge) const
{
    bool exists = false;

    list_t::const_iterator it = this->list.find(edge.get_first());

    if(it != this->list.end())
    {
        adjacency_nodes_t::const_iterator pos =
            std::find_if(it->second.begin(), it->second.end(),
                [&edge](const edge_info_t& edge_info)
                {
                    if(edge_info.first == edge.get_second() &&
                       edge_info.second == edge.get_weight())
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



bool sgl::view::adjacency_list::exists(const sgl::core::node& node) const
{
    bool exists = false;

    list_t::const_iterator it = this->list.find(node);

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
                        if(edge_info.first == node)
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


sgl::view::adjacency_list::adjacency_nodes_t
sgl::view::adjacency_list::get_adjacency_nodes(const sgl::core::node& node) const
{
    return this->list.at(node);
}



sgl::view::adjacency_list& sgl::view::adjacency_list::operator=(const sgl::view::adjacency_list& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    if(this->is_oriented() != rhs.is_oriented() || this->is_weighted() != rhs.is_weighted())
    {
        throw std::invalid_argument("adjacency_list::operator=: can't assign: oriented/weighted flags mismatch");
    }

    this->list = rhs.list;

    return *this;
}


sgl::view::adjacency_list& sgl::view::adjacency_list::operator=(const sgl::view::view& rhs)
{
    if(this->is_oriented() != rhs.is_oriented() || this->is_weighted() != rhs.is_weighted())
    {
        throw std::invalid_argument("adjacency_list::operator=: can't assign: oriented/weighted flags mismatch");
    }

    this->list.clear();

    sgl::core::edge_set_t edges = rhs.get_edges();
    for(const sgl::core::edge& edge : edges)
    {
        this->add_edge(edge);
    }

    sgl::core::node_set_t nodes = rhs.get_nodes();
    for(const sgl::core::node& node : nodes)
    {
        adjacency_info_t adjacency_info = std::make_pair(node, adjacency_nodes_t());
        this->list.insert(adjacency_info);
    }

    return *this;
}
