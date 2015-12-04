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

#include <list>

namespace sgl
{
    namespace disjoint
    {
        template<class T>
        class node
        {
            typedef T value_type;
            typedef node my_type;
            typedef my_type* my_ptr_type;
            typedef std::list<my_ptr_type> node_list_type;
            typedef node_list_type* node_list_ptr_type;
            typedef uint32_t rank_type;

        public:
            node(const value_type& value)
                : value(value)
                , parent(this)
				, child(nullptr)
                , childs(new node_list_type())
                , rank(0)
            {}

            virtual ~node() { delete this->childs; }

            void add_child(const my_ptr_type& child) { this->childs->push_front(child); }

            const my_ptr_type& get_parent() const { return this->parent; }
			const my_ptr_type& get_child() const { return this->child; }
            const rank_type& get_rank() const { return this->rank; }
            const node_list_ptr_type& get_childs() { return this->childs; }
            const value_type& get_value() const { return this->value; }

            void set_parent(const my_ptr_type& parent) { this->parent = parent; }
			void set_child(const my_ptr_type& child) { this->child = child; }
            void set_rank(const rank_type& rank) { this->rank = rank; }
            void set_childs(const node_list_ptr_type& childs) { this->childs = childs; }

        private:
            value_type value;
            my_ptr_type parent;
			my_ptr_type child;
            node_list_ptr_type childs;
            rank_type rank;
        };
    } // disjoint
} // sgl
