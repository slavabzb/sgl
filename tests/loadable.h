#pragma once

#include <fakeit.hpp>
#include <sgl/loadable.h>
#include <cxxtest/TestSuite.h>

using namespace fakeit;



class loadable_stub: public sgl::loadable<int32_t>
{
    typedef sgl::loadable<int32_t> base_t;
    
public:
    loadable_stub(const value_t& value)
        : base_t(value)
    {
        
    }
    
    virtual bool loading_criteria() const
    {
        return true;
    }
    
    virtual value_t load()
    {
        return value_t(1);
    }
};

class loadable_test: public CxxTest::TestSuite
{
    typedef int32_t value_t;
    typedef sgl::loadable<value_t> loadable_instantiation_t;
    typedef std::shared_ptr<loadable_instantiation_t> loadable_t;
    
public:
    loadable_test()
        : value(1)
    {
        this->loadable = std::make_shared<loadable_stub>(value);
    }
    
    void test_constructor()
    {
        value_t value = 1;
        
        TS_ASSERT_THROWS_NOTHING(this->loadable =
            std::make_shared<loadable_stub>(value));
        
        TS_ASSERT(this->loadable);
        TS_ASSERT_EQUALS(this->loadable->value, value);
    }
    
    void test_get()
    {
        TS_ASSERT_EQUALS(this->loadable->get(), this->value);
    }
    
private:
    loadable_t loadable;
    value_t value;
};
