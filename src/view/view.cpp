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



void sgl::view::view::check_flags(const sgl::view::view& view) const
{
    if(this->is_oriented() != view.is_oriented() || this->is_weighted() != view.is_weighted())
    {
        throw std::invalid_argument("view::check_flags: oriented / weighted flags mismatch");
    }
}
