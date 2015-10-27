#include <sgl/core/graph.h>



sgl::graph::graph(const sgl::view::view_t& view)
{
    this->set_view(view);
}



sgl::view::const_view_t sgl::graph::get_view() const
{
    return this->view;
}



sgl::view::view_t sgl::graph::get_view()
{
    return this->view;
}


void sgl::graph::set_view(const sgl::view::view_t& view)
{
    if(!view)
    {
        throw std::invalid_argument("graph::set_view: can't set view: view is nullptr");
    }

    this->view = view;
}
