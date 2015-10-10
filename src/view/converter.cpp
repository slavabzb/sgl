#include <sgl/view/converter.h>



char sgl::view::converter::convert(sgl::view::type view_type)
{
    return sgl::view::converter::type_char_map.at(view_type);
}



sgl::view::type sgl::view::converter::convert(char view_type)
{
    return sgl::view::converter::char_type_map.at(view_type);
}



std::map<sgl::view::type, char> sgl::view::converter::type_char_map =
{
    {sgl::view::type::adjacency_matrix, 'C'},
    {sgl::view::type::adjacency_list, 'L'},
    {sgl::view::type::edge_list, 'E'}
};



std::map<char, sgl::view::type> sgl::view::converter::char_type_map =
{
    {'C', sgl::view::type::adjacency_matrix},
    {'L', sgl::view::type::adjacency_list},
    {'E', sgl::view::type::edge_list}
};
