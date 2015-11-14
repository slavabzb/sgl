#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/core/node.h>
#include <sgl/disjoint/dsu.h>



class dsu_test: public CxxTest::TestSuite
{
    typedef disjoint::dsu dsu_type;
    typedef dsu_type* dsu_ptr_type;

    dsu_ptr_type dsu;

private:
    virtual void setUp() override
    {
        this->dsu = new dsu_type(5);
    }

    virtual void tearDown() override
    {
        delete this->dsu;
    }

public:
    void test_dsu()
    {
        sgl::core::node node;
        TS_ASSERT_THROWS_NOTHING(node = this->dsu->find(1));
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
        TS_ASSERT_EQUALS(node.get_id(), 2);
    }
};
