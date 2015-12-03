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
        template<typename T>
        class list_iterator;
        
        template<typename T, typename Rank = std::size_t>
        class list
        {
            typedef T value_type;
            typedef Rank rank_type;
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
            mutable node_list_ptr_type childs;

        public:        
            list(const node_ptr_type& root)
            {
                if(!root)
                {
                    throw std::invalid_argument("list::list: root is nullptr");
                }
                
                this->root = root;
                this->root->set_parent(root);
                this->childs = new node_list_type();
            }

            virtual ~list()
            {
                delete this->childs;
            }

            /*node_ptr_type get_root()
            {
                return this->root;
            }*/
            
            node_ptr_type find(const node_ptr_type& node) const
            {
                if(node->get_parent() != node)
                {
                    node->set_parent(this->find(node->get_parent()));
                }

                return node->get_parent();
            }

            void unite(const my_ptr_type& list)
            {
                if(!list)
                {
                    throw std::invalid_argument("list::unite: list is nullptr");
                }
                
                this->link(this->root, list->root, list);
            }

            iterator begin()
            {
                this->childs->clear();
                this->get_childs(this->childs, this->root);
                
                return this->childs->begin();
            }
            
            const_iterator begin() const
            {
                this->childs->clear();
                this->get_childs(this->childs, this->root);
                
                return this->childs->begin();
            }
            
            iterator end()
            {
                return this->childs->end();
            }
            
            const_iterator end() const
            {
                return this->childs->end();
            }
            
        private:
            void link(node_ptr_type& lhs, node_ptr_type& rhs, const my_ptr_type& set)
            {
                if(lhs->get_rank() > rhs->get_rank())
                {
                    rhs->set_parent(lhs);
                    lhs->add_child(rhs);
                    set->root = lhs;
                }
                else
                {
                    lhs->set_parent(rhs);
                    rhs->add_child(lhs);
                    this->root = rhs;
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
        };
    } // disjoint
} // sgl
