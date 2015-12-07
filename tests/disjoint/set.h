#pragma once

#include <cxxtest/TestSuite.h>

#include <sgl/core/node.h>
#include <sgl/disjoint/set.h>

class set_test: public CxxTest::TestSuite
{
	typedef sgl::core::node value_type;
	typedef sgl::disjoint::set<value_type> set_type;
	typedef set_type* set_ptr_type;

private:
	set_ptr_type set;

private:
	virtual void setUp() override
	{
		this->set = new set_type();

	}

	virtual void tearDown() override
	{
		delete this->set;
	}

public:
	void test_constructor()
	{
		TS_ASSERT_THROWS_NOTHING(set_type());
	}

	void test_insert()
	{
		TS_ASSERT_THROWS_NOTHING(this->set->insert(0));
		TS_ASSERT_EQUALS(this->set->map.size(), 1);
		TS_ASSERT_EQUALS(this->set->map.at(0).first, 0);
		TS_ASSERT_EQUALS(this->set->map.at(0).second.size(), 1);
		TS_ASSERT_DIFFERS(this->set->map.at(0).second.find(0), this->set->map.at(0).second.end());
		TS_ASSERT_EQUALS(*this->set->map.at(0).second.find(0), value_type(0));

		TS_ASSERT_THROWS(this->set->insert(0), std::invalid_argument);
	}

	void test_find()
	{
		TS_ASSERT_THROWS_NOTHING(this->set->insert(0));

		value_type value;
		TS_ASSERT_THROWS_NOTHING(value = this->set->find(0));
		TS_ASSERT_EQUALS(value, value_type(0));

		TS_ASSERT_THROWS(this->set->find(1), std::out_of_range);
	}

	void test_unite()
	{
		TS_ASSERT_THROWS_NOTHING(this->set->insert(0));
		TS_ASSERT_THROWS_NOTHING(this->set->insert(1));
		TS_ASSERT_THROWS_NOTHING(this->set->insert(2));
		TS_ASSERT_THROWS_NOTHING(this->set->insert(3));

		TS_ASSERT_THROWS_NOTHING(this->set->unite(0, 1));
		TS_ASSERT_EQUALS(this->set->find(0), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(1), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(2), value_type(2));
		TS_ASSERT_EQUALS(this->set->find(3), value_type(3));
		TS_ASSERT_EQUALS(this->set->map.size(), 3);
		TS_ASSERT_THROWS(this->set->map.at(0), std::out_of_range);
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(1));
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(2));
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(3));
		TS_ASSERT_EQUALS(this->set->map.at(1).first, 1);
		TS_ASSERT_EQUALS(this->set->map.at(1).second.size(), 2);
		TS_ASSERT_DIFFERS(this->set->map.at(1).second.find(0), this->set->map.at(1).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(1).second.find(1), this->set->map.at(1).second.end());

		TS_ASSERT_THROWS_NOTHING(this->set->unite(0, 1));
		TS_ASSERT_EQUALS(this->set->find(0), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(1), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(2), value_type(2));
		TS_ASSERT_EQUALS(this->set->find(3), value_type(3));
		TS_ASSERT_EQUALS(this->set->map.size(), 3);
		TS_ASSERT_THROWS(this->set->map.at(0), std::out_of_range);
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(1));
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(2));
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(3));
		TS_ASSERT_EQUALS(this->set->map.at(1).first, 1);
		TS_ASSERT_EQUALS(this->set->map.at(1).second.size(), 2);
		TS_ASSERT_DIFFERS(this->set->map.at(1).second.find(0), this->set->map.at(1).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(1).second.find(1), this->set->map.at(1).second.end());

		TS_ASSERT_THROWS_NOTHING(this->set->unite(2, 3));
		TS_ASSERT_EQUALS(this->set->find(0), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(1), value_type(1));
		TS_ASSERT_EQUALS(this->set->find(2), value_type(3));
		TS_ASSERT_EQUALS(this->set->find(3), value_type(3));
		TS_ASSERT_EQUALS(this->set->map.size(), 2);
		TS_ASSERT_THROWS(this->set->map.at(0), std::out_of_range);
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(1));
		TS_ASSERT_THROWS(this->set->map.at(2), std::out_of_range);
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(3));
		TS_ASSERT_EQUALS(this->set->map.at(3).first, 1);
		TS_ASSERT_EQUALS(this->set->map.at(3).second.size(), 2);
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(2), this->set->map.at(3).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(3), this->set->map.at(3).second.end());

		TS_ASSERT_THROWS_NOTHING(this->set->unite(1, 3));
		TS_ASSERT_EQUALS(this->set->find(0), value_type(3));
		TS_ASSERT_EQUALS(this->set->find(1), value_type(3));
		TS_ASSERT_EQUALS(this->set->find(2), value_type(3));
		TS_ASSERT_EQUALS(this->set->find(3), value_type(3));
		TS_ASSERT_EQUALS(this->set->map.size(), 1);
		TS_ASSERT_THROWS(this->set->map.at(0), std::out_of_range);
		TS_ASSERT_THROWS(this->set->map.at(1), std::out_of_range);
		TS_ASSERT_THROWS(this->set->map.at(2), std::out_of_range);
		TS_ASSERT_THROWS_NOTHING(this->set->map.at(3));
		TS_ASSERT_EQUALS(this->set->map.at(3).first, 2);
		TS_ASSERT_EQUALS(this->set->map.at(3).second.size(), 4);
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(0), this->set->map.at(3).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(1), this->set->map.at(3).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(2), this->set->map.at(3).second.end());
		TS_ASSERT_DIFFERS(this->set->map.at(3).second.find(3), this->set->map.at(3).second.end());
	}
};
