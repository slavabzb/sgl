#pragma once

#include <cxxtest/TestSuite.h>
#include <sgl/details/converter.h>

class converter_test: public CxxTest::TestSuite
{
public:
    void setUp()
    {
        this->types = new sgl::view::type[this->array_size];
        this->types[0] = sgl::view::type::adjacency_list;
        this->types[1] = sgl::view::type::adjacency_matrix;
        this->types[2] = sgl::view::type::edge_list;

        this->char_types = new char[this->array_size];
        this->char_types[0] = 'L';
        this->char_types[1] = 'C';
        this->char_types[2] = 'E';
    }



    void tearDown()
    {
        delete [] this->types;
        delete [] this->char_types;
    }



private:
    const std::size_t array_size = 3;
    sgl::view::type* types;
    char* char_types;



public:
    void test_convert()
    {
        for(std::size_t i = 0; i < this->array_size; ++i)
        {
            char char_type;

            TS_ASSERT_THROWS_NOTHING(
                char_type = sgl::details::converter::convert(this->types[i])
            );

            TS_ASSERT_EQUALS(
                char_type,
                this->char_types[i]
            );

            sgl::view::type type;

            TS_ASSERT_THROWS_NOTHING(
                type = sgl::details::converter::convert(this->char_types[i])
            );

            TS_ASSERT_EQUALS(
                type,
                this->types[i]
            );
        }

        TS_ASSERT_THROWS(
            sgl::details::converter::convert('X'),
            std::out_of_range
        );

        TS_ASSERT_THROWS(
            sgl::details::converter::convert(static_cast<sgl::view::type>(100)),
            std::out_of_range
        );
    }
};
