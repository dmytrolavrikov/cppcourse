#include <cassert>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include "container.hpp"
#include "container_libc.hpp"

int g_integer = 150;


struct S
{
    int n;
    std::string s;
    float d;

    friend bool operator<(const S& lhs, const S& rhs) noexcept
    {
        // compares lhs.n to rhs.n,
        // then lhs.s to rhs.s,
        // then lhs.d to rhs.d
        // in that order, first non-equal result is returned
        // or false if all elements are equal
        return std::tie(lhs.n, lhs.s, lhs.d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

struct Something {
    int first;
    int second;
};

template <typename T>
struct SomethingRef {
    T& first;
    T& second;

};

struct SomethingPtr {
    int* first;
    int* second;
};

int* function()
{
    return &g_integer;
}

int& funtrion_ref()
{
    return g_integer;
}

void test_container()
{
    cppcourse::container<cppcourse::allocator_with_new> cont{};
    cont.push_back(20);
    cont.assign(5, 21);
    cont.assign(2, 59);

    const auto& res = cont[0];
    cont[0] = 50;

    std::cout << "res = " << res << std::endl;

    for (int i = 0; i < 72; ++i) {
        cont.push_back(i);
        std::cout << "element[" << i << "] = " << cont.at(i) << std::endl;
    }
    std::cout << "=============================" << std::endl;
    cont.erase(5);
    for (int i = 0; i < cont.size(); ++i) {
        std::cout << "element[" << i << "] = " << cont.at(i) << std::endl;
    }
}

void test_container_libc()
{
    cppcourse::container_libc cont{};
    cont.push_back(20);
    cont.assign(5, 21);
    cont.assign(2, 59);

    const auto& res = cont[0];
    cont[0] = 50;

    std::cout << "res = " << res << std::endl;

    for (int i = 0; i < 72; ++i) {
        cont.push_back(i);
        std::cout << "element[" << i << "] = " << cont.at(i) << std::endl;
    }
    std::cout << "=============================" << std::endl;
    cont.erase(5);
    for (int i = 0; i < cont.size(); ++i) {
        std::cout << "element[" << i << "] = " << cont.at(i) << std::endl;
    }
}

int main()
{
    // test_container();

    test_container_libc();

    std::vector<int, std::allocator<int>> vec;


    // add -> push_back
    // size -> size



}

// SomethingRef -> SomethingPtr
// auto [it, inserted] = map.emplace(1, 2); -> see cppref
// int array with struct or class with element access operator + what else may be needed
//


// ession IV 25.9.2024
// Reviewing container

// Next home task:
// Align container with std::vector interface
// add -> push_back
// ...
// operator[]
// no iterator requred atm
// Finish container functionality
// do realloc with actual realloc
// Add unit tests
// publish code to some repo


// 2 containers - one on malloc realloc free
// 2 containers - second with new delete and move
// container with template and structure