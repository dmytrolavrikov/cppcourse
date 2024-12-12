#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>

int g_integer = 150;

struct S {
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

int* function() { return &g_integer; }

int& funtrion_ref() { return g_integer; }

int func()
{

    auto int_ptr = function();

    *int_ptr = 148;
    *function() = 167;

    funtrion_ref() = 149;

    std::cout << "g_integer = " << g_integer << std::endl;

    Something some;
    some.first = 6;
    some.second = 7;

    Something some2;

    some2 = some;

    SomethingRef<int> sref { some.first, some.second };
    sref.first = 19;
    std::cout << some2.first << ", " << some2.second << std::endl;
    std::cout << some.first << ", " << some.second << std::endl;

    int sss = 1488;
    int sss2 = 8814;

    SomethingPtr s_ptr { &some.first, &some.second };

    std::cout << "s_ptr.first = " << s_ptr.first << std::endl;
    std::cout << "*s_ptr.first = " << *s_ptr.first << std::endl;

    some.second = 1488;

    std::cout << "s_ptr.second = " << s_ptr.second << std::endl;
    std::cout << "*s_ptr.second = " << *s_ptr.second << std::endl;

    // Lexicographical comparison demo:
    std::set<S> set_of_s;

    S value { 42, "Test", 3.14 };
    std::set<S>::iterator iter;
    bool is_inserted;

    // Unpack a pair:
    std::tie(iter, is_inserted) = set_of_s.insert(value);
    assert(is_inserted);

    // std::tie and structured bindings:
    auto position = [](int w) { return std::tuple(1 * w, 2 * w); };

    // auto [x, y] = position(1);
    int x = 0, y = 0;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::tuple<int&, int&>(x, y) = position(18);
    // std::tie(x, y) = position(2); // reuse x, y with tie
    assert(x == 2 && y == 4);

    std::unordered_map<int, int> map;
    const auto& res = map.emplace(1, 2);
    bool b;
    std::tie(std::ignore, b) = map.emplace(1, 2);

    auto [it, inserted] = map.emplace(1, 2);

    std::cout << "x = " << x << ", y = " << y << std::endl;

    // Implicit conversions are permitted:
    std::tuple<char, short> coordinates(6, 9);
    std::tie(x, y) = coordinates;
    assert(x == 6 && y == 9);
}

// SomethingRef -> SomethingPtr
// auto [it, inserted] = map.emplace(1, 2); -> see cppref
// int array with struct or class with element access operator + what else may
// be needed
//
