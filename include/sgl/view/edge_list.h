#pragma once

#include <map>
#include <set>

#include <sgl/view/view.h>

class edge_list_test;

namespace sgl
{
    namespace view
    {
        class edge_list: public view
        {
        #ifdef TESTS
            friend class ::edge_list_test;
        #endif

        public:
            edge_list(bool oriented = false, bool weighted = false);
            edge_list(const view& other);
            virtual ~edge_list();

            virtual void add_node(const sgl::core::node& node) override;
            virtual void add_edge(const sgl::core::edge& edge) override;

            virtual void remove_node(const sgl::core::node& node) override;
            virtual void remove_edge(const sgl::core::edge& edge) override;

            virtual type get_type() const override;
            virtual sgl::core::node_set_t get_nodes() const override;
            virtual sgl::core::edge_set_t get_edges() const override;

            virtual bool exists(const sgl::core::edge& edge) const override;
            virtual bool exists(const sgl::core::node& node) const override;

            bool operator==(const edge_list& rhs) const;

            edge_list& operator=(const edge_list& rhs);
            edge_list& operator=(const view& rhs);

        private:
            sgl::core::edge_set_t edges;
            sgl::core::node_set_t nodes;
        };

        typedef std::shared_ptr<edge_list> edge_list_t;
        typedef const std::shared_ptr<const edge_list> const_edge_list_t;

    } // view
} // sgl
