#pragma once

#include <list>

namespace disjoint
{
    template<class T>
    class node
    {
    public:
        typedef T value_type;
        typedef node my_type;
        typedef node* my_ptr_type;
        typedef std::list<my_ptr_type> node_list_type;
        typedef node_list_type* node_list_ptr_type;
        typedef uint32_t rank_type;
        
    public:
        node(const value_type& value)
            : value(value)
            , parent(nullptr)
            , childs(new node_list_type())
            , rank(0)
        {}
            
        virtual ~node()
        {
            delete this->childs;
        }
        
        void add_child(const my_ptr_type& child)
        {
            this->childs->push_front(child);
        }
        
        const value_type& get_value() const { return this->value; }
        const my_ptr_type& get_parent() const { return this->parent; }
        const node_list_ptr_type& get_childs() const { return this->childs; }
        const rank_type& get_rank() const { return this->rank; }
        
        void set_value(const value_type& value) { this->value = value; }
        void set_parent(const my_ptr_type& parent) { this->parent = parent; }
        void set_childs(const node_list_ptr_type& childs) { this->childs = childs; }
        void set_rank(const rank_type& rank) { this->rank = rank; }
        
    private:
        value_type value;
        my_ptr_type parent;
        node_list_ptr_type childs;
        rank_type rank;
    };
} // disjoint
