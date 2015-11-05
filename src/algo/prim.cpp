#include <sgl/algo/prim.h>
#include <sgl/view/adjacency_list.h>
#include <limits>
#include <algorithm>



sgl::view::view_t sgl::algo::prim(sgl::view::const_adjacency_list_t adjacency_list)
{
    sgl::view::adjacency_list_t minimal_spanning_tree;
    if(adjacency_list->is_oriented() || !adjacency_list->is_weighted())
    {
        return minimal_spanning_tree;
    }

    sgl::node_set_t source_nodes = adjacency_list->get_nodes();
    sgl::node_set_t visited_nodes;

    if(!source_nodes.empty())
    {
        const sgl::node& first = *source_nodes.begin();

        sgl::node second;
        sgl::weight_t weight = std::numeric_limits<sgl::weight_t>::max();

        sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes = adjacency_list->get_adjacency_nodes(first);
        std::for_each(adjacency_nodes.begin(), adjacency_nodes.end(),
        [&weight, &second, &source_nodes](const sgl::view::adjacency_list::edge_info_t& edge_info)
        {
            if(edge_info.second < weight)
            {
                weight = edge_info.second;
                second = edge_info.first;
            }
        });

        minimal_spanning_tree = std::make_shared<sgl::view::adjacency_list>(adjacency_list->is_oriented(), adjacency_list->is_weighted());
        minimal_spanning_tree->add_edge(sgl::edge(first, second, weight));

        visited_nodes.insert(first);
        visited_nodes.insert(second);

        while(visited_nodes != source_nodes)
        {
            sgl::node first;
            sgl::node second;
            sgl::weight_t weight = std::numeric_limits<sgl::weight_t>::max();

            sgl::node_set_t nodes = minimal_spanning_tree->get_nodes();
            for(const sgl::node& node : nodes)
            {
                sgl::view::adjacency_list::adjacency_nodes_t adjacency_nodes = adjacency_list->get_adjacency_nodes(node);

                std::for_each(adjacency_nodes.begin(), adjacency_nodes.end(),
                [&](const sgl::view::adjacency_list::edge_info_t& edge_info)
                {
                    if(nodes.find(edge_info.first) == nodes.end())
                    {
                        if(edge_info.second < weight)
                        {
                            weight = edge_info.second;
                            first = node;
                            second = edge_info.first;
                        }
                    }
                });
            }

            minimal_spanning_tree->add_edge(sgl::edge(first, second, weight));
            visited_nodes.insert(second);
        }
    }

    return minimal_spanning_tree;
}
