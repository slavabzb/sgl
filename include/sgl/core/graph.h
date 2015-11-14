#pragma once

#include <sgl/view/view.h>

namespace sgl
{
    namespace core
    {
        /**
         * Graph.
         * Graph represented in selected view.     
         */
        class graph
        {
        public:
            /**
             * Constructor.
             * Constructs a graph with given view.
             * 
             * @param view - view of the graph.
             * @throw std::invalid_argument if view is nullptr.
             */
            graph(const sgl::view::view_t& view);

            /**
             * Retrieves the view of the graph.
             * 
             * @return The view of the graph.
             */
            sgl::view::view_t get_view();

            /**
             * Retrieves the view of the constant graph.
             * 
             * @return The view of the constant graph.
             */
            sgl::view::const_view_t get_view() const;

            /**
             * Assigns new view to the graph.
             * 
             * @param view - new view of the graph.
             * @throw std::invalid_argument if view is nullptr.
             */
            void set_view(const sgl::view::view_t& view);

        private:
            sgl::view::view_t view;
        };
    } // core
} // sgl
