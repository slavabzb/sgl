#pragma once

#include <map>
#include <sgl/view/type.h>

namespace sgl
{
	namespace details
	{
		class converter
		{
		public:
			static char convert(sgl::view::type view_type);
			static sgl::view::type convert(char view_type);

		private:
			using type_char_map_t = std::map<sgl::view::type, char>;
			using char_type_map_t = std::map<char, sgl::view::type>;

			static type_char_map_t type_char_map;
			static char_type_map_t char_type_map;
		};

	} // details
} // sgl
