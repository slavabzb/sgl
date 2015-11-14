#pragma once

#include <map>
#include <sgl/view/type.h>

namespace sgl
{
    namespace details
    {
        /**
         * Graph view type - char converter.
         * Converts graph view type to char and back.
         */
        class converter
        {
        public:
            /**
             * Converts graph view type to char.
             * 
             * @param view_type - a graph view type.
             * @return Char which represents the view.
             * @throw std::out_of_range if there is no mapped char for that graph view type.
             */
            static char convert(sgl::view::type view_type);
            
            /**
             * Converts char to graph view type.
             * 
             * @param view_type - a char which represents a graph view type.
             * @return Graph view type.
             * @throw std::out_of_range if there is no mapped view type for that char.
             */
            static sgl::view::type convert(char view_type);

        private:
            using type_char_map_t = std::map<sgl::view::type, char>;
            using char_type_map_t = std::map<char, sgl::view::type>;

            static type_char_map_t type_char_map;
            static char_type_map_t char_type_map;
        };
    } // details
} // sgl
