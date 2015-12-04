#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/core/node.h>
#include <sgl/disjoint/list.h>

class list_test: public CxxTest::TestSuite
{
    typedef int rank_type;
    typedef sgl::core::node value_type;
    typedef sgl::disjoint::node<value_type> node_type;
    typedef sgl::disjoint::list<value_type> list_type;
    typedef node_type* node_ptr_type;
    typedef list_type* list_ptr_type;

private:
    value_type value;
    node_ptr_type node;
    list_ptr_type list;

private:
    virtual void setUp() override
    {
        /*this->value = 1;
        this->node = new node_type(this->value);
        this->list = new list_type(this->node);*/
    }

    virtual void tearDown() override
    {
        /*delete this->list;
        delete this->node;*/
    }

public:
    void test_constructor()
    {
		list_type list;
		list.make_set(0);
		list.make_set(1);

		auto x = list.find(0);
		std::clog << "\nx = " << x.get_id();

		list_type rhs;
		rhs.make_set(3);
		rhs.make_set(4);

		list.unite(rhs);

        /*value_type root_value = 1;
        node_ptr_type root;
        list_ptr_type list;

        TS_ASSERT_THROWS_NOTHING(list_type(nullptr));
        TS_ASSERT_THROWS_NOTHING(root = new node_type(root_value));
        TS_ASSERT_THROWS_NOTHING(list = new list_type(root));

        delete list;
        delete root;*/
    }

    void test_find()
    {
        /*node_ptr_type node_ptr;
		TS_ASSERT_THROWS(this->list->find(nullptr), std::invalid_argument);
		TS_ASSERT_THROWS_NOTHING(node_ptr = this->list->find(this->node));
        TS_ASSERT_DIFFERS(node_ptr, nullptr);
        TS_ASSERT_DIFFERS(node_ptr->get_parent(), nullptr);
        TS_ASSERT_DIFFERS(node_ptr->get_childs(), nullptr);
        TS_ASSERT_EQUALS(node_ptr, this->node);
        TS_ASSERT_EQUALS(node_ptr->get_childs()->size(), 0);
        TS_ASSERT_EQUALS(node_ptr->get_parent(), this->node);*/
    }

    void test_unite()
    {
        /*value_type value = 2;
        node_ptr_type node = new node_type(value);
        rank_type rank = node->get_rank();
        list_ptr_type other = new list_type(node);

        TS_ASSERT_THROWS(this->list->unite(nullptr), std::invalid_argument);
        TS_ASSERT_THROWS_NOTHING(this->list->unite(other));
        TS_ASSERT_DIFFERS(this->list->find(this->node), this->node);
        TS_ASSERT_DIFFERS(this->list->find(node), this->node);
        TS_ASSERT_EQUALS(other->find(node), node);
        TS_ASSERT_EQUALS(other->find(this->node), node);
        TS_ASSERT_EQUALS(node->get_rank(), rank + 1);

        delete other;
        delete node;*/
    }

    void test_iterators()
    {
        /*const std::size_t size = 10;
        value_type values[size];
        node_ptr_type nodes[size];
        list_ptr_type lists[size];

        for(std::size_t i = 0; i < size; ++i)
        {
            values[i] = i;
            nodes[i] = new node_type(values[i]);
            lists[i] = new list_type(nodes[i]);
        }

        for(std::size_t i = 0; i < 1; ++i)
        {
            this->list->unite(lists[i]);
        }

        std::clog << "\nthis->list: ";
        for(list_type::const_iterator it = this->list->begin(); it != this->list->end(); ++it)
        {
            std::clog << (*it)->get_value().get_id() << " ";
        }

		std::clog << "\nother list: ";
        for(list_type::const_iterator it = lists[0]->begin(); it != lists[0]->end(); ++it)
        {
            std::clog << (*it)->get_value().get_id() << " ";
        }

        for(std::size_t i = 0; i < size; ++i)
        {
            std::clog << "\nlist " << i << ": ";
            for(list_type::iterator it = lists[i]->begin(); it != lists[i]->end(); ++it)
            {
                std::clog << (*it)->get_value().get_id() << " ";
            }
        }

        for(std::size_t i = 0; i < size; ++i)
        {
            delete lists[i];
            delete nodes[i];
        }*/
    }
};
