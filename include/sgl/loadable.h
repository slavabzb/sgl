#pragma once

#include <memory>

namespace sgl {



template<typename T>
class loadable
{
protected:
    typedef T value_t;
    
public:
    loadable(const value_t& value = value_t(0))
        : value(value)
    {
        
    }
    
    virtual ~loadable() {}
    
    value_t get()
    {
        if(this->loading_criteria())
        {
            this->value = this->load();
        }
        
        return this->value;
    }
    
    const value_t get() const
    {
        if(this->loading_criteria())
        {
            this->value = this->load();
        }
        
        return this->value;
    }
    
    virtual bool loading_criteria() const = 0;
    virtual value_t load() = 0;
    
#ifndef TESTS
private:
#endif
    value_t value;
};



} // sgl
