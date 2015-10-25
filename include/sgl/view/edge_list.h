#pragma once

#include <map>
#include <set>

#include <sgl/view/view.h>

class edge_list_test;

namespace sgl {
namespace view {

class edge_list: public view
{
#ifdef TESTS
    friend class ::edge_list_test;
#endif

public:
    edge_list(bool oriented = false, bool weighted = false);
    virtual ~edge_list();

    virtual void add_node() override;
    virtual void add_edge(const edge& edge) override;

    virtual void remove_node(const node& node) override;
    virtual void remove_edge(const edge& edge) override;
    
    virtual type get_type() const override;
    virtual node_set_t get_nodes() const override;
    virtual edge_set_t get_edges() const override;
    
    virtual bool exists(const edge& edge) const override;
    virtual bool exists(const node& node) const override;
    
private:
    edge_set_t edges;
    node_set_t nodes;
};

typedef std::shared_ptr<edge_list> edge_list_t;
typedef const std::shared_ptr<const edge_list> const_edge_list_t;

} // view
} // sgl
