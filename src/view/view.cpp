#include <sgl/view/view.h>



sgl::view::view::view()
    : oriented(false)
    , weighted(false)
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



void sgl::view::view::set_oriented(bool oriented)
{
    this->oriented = oriented;
}



void sgl::view::view::set_weighted(bool weighted)
{
    this->weighted = weighted;
}
