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
