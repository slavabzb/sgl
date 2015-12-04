/**
 * @cond
 *
 * Copyright (c) 2015-2016
 *
 * Bezborodov, V.A. vyacheslav.bezborodov@gmail.com
 * Golodov, V.A. avaksa@gmail.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * @endcond
 */

/**
 * @cond
 *
 * Copyright (c) 2015-2016
 *
 * Bezborodov, V.A. vyacheslav.bezborodov@gmail.com
 * Golodov, V.A. avaksa@gmail.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * @endcond
 */

#pragma once

#include <sgl/disjoint/node.h>

namespace sgl
{
    namespace disjoint
    {
        template<typename T, typename R = std::size_t>
        class list
        {
            typedef T value_type;
            typedef R rank_type;
            typedef list<value_type> my_type;
            typedef my_type* my_ptr_type;
            typedef disjoint::node<value_type> node_type;
            typedef node_type* node_ptr_type;
            typedef std::list<node_ptr_type> node_list_type;
            typedef node_list_type* node_list_ptr_type;

        public:
            typedef typename node_list_type::iterator iterator;
            typedef typename node_list_type::const_iterator const_iterator;

        private:
            node_ptr_type root;

        public:
            list()
            {
                this->root = nullptr;
            }

            virtual ~list()
            {
				while(this->root)
				{
					node_ptr_type current = this->root->get_child();
					delete this->root;
					this->root = current;
				}
            }

			void make_set(const value_type& value)
			{
				node_ptr_type node = new node_type(value);
				node->set_child(this->root);
				this->root = node;
			}

			const value_type& find(const value_type& value) const
			{
                return this->find_node(this->find_value(value))->get_value();
			}

			void unite(my_type& rhs)
            {
                this->link(this->root, rhs.root, &rhs);
            }

		private:
			node_ptr_type find_value(const value_type& value) const
			{
				node_ptr_type node = nullptr;
				for(node = this->root; node != nullptr; node = node->get_child())
				{
					if(node->get_value() == value)
					{
						break;
					}
				}

				return node;
			}

            node_ptr_type find_node(const node_ptr_type& node) const
            {
				this->validate(node, "find", "node");

                if(node->get_parent() != node)
                {
                    node->set_parent(this->find_node(node->get_parent()));
                }

                return node->get_parent();
            }

        private:
            void link(const node_ptr_type& lhs, const node_ptr_type& rhs, const my_ptr_type& list)
            {
				this->validate(lhs, "link", "lhs");
				this->validate(rhs, "link", "rhs");
				this->validate(list, "link", "list");

                if(lhs->get_rank() > rhs->get_rank())
                {
                    rhs->set_parent(lhs);
                    lhs->add_child(rhs);
                    list->root = lhs;
					//this->root = nullptr;
                }
                else
                {
                    lhs->set_parent(rhs);
                    rhs->set_child(lhs);
                    this->root = rhs;
					//list->root = nullptr;
                }

                if(lhs->get_rank() == rhs->get_rank())
                {
                    rhs->set_rank(rhs->get_rank() + 1);
                }
            }

            void get_childs(const node_list_ptr_type& list, const node_ptr_type& node) const
            {
				typename node_list_type::const_iterator it = node->get_childs()->begin();
				list->push_front(node);

				for(; it != node->get_childs()->end(); ++it)
				{
					this->get_childs(list, *it);
				}
            }

			template<typename _Tpointer>
			void validate(const _Tpointer& ptr, const std::string& method, const std::string& ptr_name) const
			{
				if(!ptr)
				{
					throw std::invalid_argument("list::" + method + ": " + ptr_name + " is nullptr");
				}
			}
        };

		template<typename T, typename R = std::size_t>
		class set
		{
		private:

		};

    } // disjoint
} // sgl
