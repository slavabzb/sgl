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

namespace disjoint
{
    template<class T>
    class list
    {
        typedef T value_type;
        typedef list<value_type> my_type;
        typedef my_type* my_ptr_type;
        typedef node<value_type> node_type;
        typedef typename node_type::my_ptr_type node_ptr_type;
        typedef typename node_type::node_list_ptr_type node_list_ptr_type;

    private:
        node_ptr_type root;
        
    public:
        list(const node_ptr_type& root)
        {
            this->root = root;
            this->root->parent = this->root;
        }
        
        virtual ~list() {}
        
        node_ptr_type find(const node_ptr_type& node) const
        {
            if(node->get_parent() != node)
            {
                node->set_parent(this->find(node->get_parent()));
            }
            
            return node->get_parent();
        }
        
        void union_sets(const my_ptr_type& list)
        {
            this->link(this->root, list->root, list);
        }
        
    private:
        void link(node_ptr_type& lhs, node_ptr_type& rhs, node_list_ptr_type& list)
        {
            if(lhs->get_rank() > rhs->get_rank())
            {
                rhs->set_parent(lhs);
                lhs->add_child(rhs);
                list->root = lhs;
            }
            else
            {
                lhs->set_parent(rhs);
                rhs->add_child(lhs);
                this->root = rhs;
            }
            
            if(lhs->get_rank() == rhs->get_rank())
            {
                rhs->set_rank(++rhs->get_rank());
            }
        }
    };
} // disjoint
