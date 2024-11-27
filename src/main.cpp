#include <iostream>
#include <functional>
#include "../include/unique_ptr.hpp"

int main()
{

    cppcourse::unique_ptr<int> unique_ptr_test;
    auto test_one = cppcourse::make_unique<int>();

    struct TestStruct {
        TestStruct(int first) : m_first(first){};
        int m_first;
    };


    auto test_two = cppcourse::make_unique<TestStruct>(6);
    std::cout << "test_two.first = " << test_two.get()->m_first << std::endl;


}