#include <sgl/view/converter.h>



char sgl::view::converter::convert(sgl::view::type view_type)
{
	char converted = 0;

	sgl::view::converter::type_char_map_t::const_iterator it =
		sgl::view::converter::type_char_map.find(view_type);

	if(it != sgl::view::converter::type_char_map.end())
	{
		converted = sgl::view::converter::type_char_map[view_type];
	}

	return converted;
}



sgl::view::type sgl::view::converter::convert(char view_type)
{
	sgl::view::type type = sgl::view::type::unknown;

	sgl::view::converter::char_type_map_t::const_iterator it =
		sgl::view::converter::char_type_map.find(view_type);

	if(it != sgl::view::converter::char_type_map.end())
	{
		type = sgl::view::converter::char_type_map[view_type];
	}

	return type;
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
