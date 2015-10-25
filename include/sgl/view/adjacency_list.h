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

public:
    using edge_info_t = std::pair<node, weight_t>;   
    using adjacency_nodes_t = std::set<edge_info_t>;

private:
    using adjacency_info_t = std::pair<node, adjacency_nodes_t>;
    using list_t = std::map<adjacency_info_t::first_type, adjacency_info_t::second_type>;
    
public:
    adjacency_list(bool oriented = false, bool weighted = false);
    virtual ~adjacency_list();

    virtual void add_node() override;
    virtual void add_edge(const edge& edge) override;

    virtual void remove_node(const node& node) override;
    virtual void remove_edge(const edge& edge) override;
    
    virtual type get_type() const override;
    virtual node_set_t get_nodes() const override;
    virtual edge_set_t get_edges() const override;
    
    virtual bool exists(const edge& edge) const override;
    virtual bool exists(const node& node) const override;
    
    adjacency_nodes_t get_adjacency_nodes(const node& node) const;
    
    bool operator==(const adjacency_list& rhs) const;
    
    adjacency_list& operator=(const adjacency_list& rhs);
    adjacency_list& operator=(const view& rhs);
    
private:
    list_t list;
};

typedef std::shared_ptr<adjacency_list> adjacency_list_t;
typedef const std::shared_ptr<const adjacency_list> const_adjacency_list_t;

} // view
} // sgl
