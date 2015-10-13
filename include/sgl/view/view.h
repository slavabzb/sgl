#pragma once

#include <sgl/node.h>
#include <sgl/edge.h>
#include <sgl/view/type.h>

namespace sgl {
namespace view {

class view
{
public:
    view(bool oriented = false, bool weighted = false);
    virtual ~view();

    virtual void add_node() = 0;
    virtual void add_edge(const edge& edge) = 0;

    virtual void remove_node(const node& node) = 0;
    virtual void remove_edge(const edge& edge) = 0;
    
    virtual type get_type() const = 0;
    virtual std::size_t get_nodes_count() const = 0;
    
    virtual bool exists(const edge& edge) const = 0;
    virtual bool exists(const node& node) const = 0;
    
    bool is_oriented() const;
    bool is_weighted() const;
    
private:
    bool oriented;
    bool weighted;
};

typedef std::shared_ptr<view> view_t;
typedef const std::shared_ptr<const view> const_view_t;

} // view
} // sgl
