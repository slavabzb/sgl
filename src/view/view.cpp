#include <sgl/view/view.h>



sgl::view::view::view(bool oriented, bool weighted)
    : oriented(oriented)
    , weighted(weighted)
{

}



sgl::view::view::~view()
{

}



bool sgl::view::view::is_oriented() const
{
    return this->oriented;
}



bool sgl::view::view::is_weighted() const
{
    return this->weighted;
}



bool sgl::view::view::operator==(const sgl::view::view& rhs) const
{
    if(this->is_oriented() != rhs.is_oriented())
    {
        return false;
    }

    if(this->is_weighted() != rhs.is_weighted())
    {
        return false;
    }

    if(this->get_nodes() != rhs.get_nodes())
    {
        return false;
    }

    if(this->get_edges() != rhs.get_edges())
    {
        return false;
    }

    return true;
}



bool sgl::view::view::operator!=(const sgl::view::view& rhs) const
{
    return !(*this == rhs);
}
