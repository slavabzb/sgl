#pragma once

#include <sgl/view/type.h>

namespace sgl {
namespace view {

class converter
{
public:
	static char convert(type view_type);
	static type convert(char view_type);

private:
	using type_char_map_t = std::map<type, char>;
	using char_type_map_t = std::map<char, type>;

	static type_char_map_t type_char_map;
	static char_type_map_t char_type_map;
};

} // view
} // sgl
