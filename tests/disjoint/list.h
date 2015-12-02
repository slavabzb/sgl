#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/core/node.h>
#include <sgl/disjoint/list.h>

class list_test: public CxxTest::TestSuite
{
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
        this->value = 1;
        this->node = new node_type(this->value);
        this->list = new list_type(this->node);
    }

    virtual void tearDown() override
    {
        delete this->list;
        delete this->node;
    }

public:
    void test_constructor()
    {
        value_type root_value = 1;
        node_ptr_type root;
        TS_ASSERT_THROWS_NOTHING(root = new node_type(root_value));
        
        list_ptr_type list;
        TS_ASSERT_THROWS_NOTHING(list = new list_type(root));
                
        delete list;
        delete root;
    }
        
    void test_find()
    {
        node_ptr_type node_ptr;
        TS_ASSERT_THROWS_NOTHING(node_ptr = this->list->find(this->node));
        TS_ASSERT(node_ptr != nullptr);
        TS_ASSERT(node_ptr->get_parent() != nullptr);
        TS_ASSERT(node_ptr->get_childs() != nullptr);
        TS_ASSERT_EQUALS(node_ptr, this->node);
        TS_ASSERT_EQUALS(node_ptr->get_childs()->size(), 0);
        TS_ASSERT_EQUALS(node_ptr->get_parent(), this->node);
    }
    
    
    void test_dsu()
    {             
        /*TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(1));
        TS_ASSERT_EQUALS(node.get_id(), 1);

        TS_ASSERT_THROWS_NOTHING(this->dsu->unite(0, 4));
        TS_ASSERT_THROWS_NOTHING(this->dsu->unite(1, 3));

        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(0));
        TS_ASSERT_EQUALS(node.get_id(), 0);
        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(4));
        TS_ASSERT_EQUALS(node.get_id(), 0);
        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(3));
        TS_ASSERT_EQUALS(node.get_id(), 1);

        TS_ASSERT_THROWS_NOTHING(this->dsu->unite(4, 3));

        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(4));
        TS_ASSERT_EQUALS(node.get_id(), 0);
        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(2));
        TS_ASSERT_EQUALS(node.get_id(), 2);*/
    }
};
