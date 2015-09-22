#pragma once

#include <sgl/node.h>
#include <sgl/edge.h>

namespace sgl {



class view
{
public:
    virtual ~view() {}
    
    virtual void add_node() = 0;
    virtual void add_edge(const_edge_t& edge) = 0;
    
    virtual void remove_node(const node_t& node) = 0;
    virtual void remove_edge(const_edge_t& edge) = 0;
};



typedef std::shared_ptr<view> view_t;



} // sgl
