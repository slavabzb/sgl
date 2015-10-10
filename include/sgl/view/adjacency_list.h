#pragma once

#include <map>
#include <set>

#include <sgl/view/view.h>

class adjacency_list_test;

namespace sgl {
namespace view {

class adjacency_list: public view
{
#ifdef TESTS
    friend class ::adjacency_list_test;
#endif

    using edge_info_t = std::pair<node, weight_t>;
    
    /*struct edge_info_comparer
    {
        bool operator() (const edge_info_t& lhs, const edge_info_t& rhs)
        {
            return lhs.first < rhs.first;
        }
    };*/
    
    using adjacency_nodes_t = std::set<edge_info_t/*, edge_info_comparer*/>;
    using adjacency_info_t = std::pair<node, adjacency_nodes_t>;
    using list_t = std::map<adjacency_info_t::first_type,
        adjacency_info_t::second_type>;
    
public:
    adjacency_list(bool oriented = false, bool weighted = false);
    virtual ~adjacency_list();

    virtual void add_node() override;
    virtual void add_edge(const_edge_t edge) override;

    virtual void remove_node(const_node_t node) override;
    virtual void remove_edge(const_edge_t edge) override;

    virtual const_node_set_t get_nodes() const override;
    virtual const_edge_set_t get_edges() const override;
    
    virtual type get_type() const override;
    
    virtual bool exists(const_edge_t edge) const override;
    virtual bool exists(const_node_t node) const override;

private:
    bool in_range(const node& from, const node& to) const;
    
private:
    list_t list;
};

typedef std::shared_ptr<adjacency_list> adjacency_list_t;
typedef const std::shared_ptr<const adjacency_list> const_adjacency_list_t;

} // view
} // sgl
