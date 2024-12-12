#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../include/unique_ptr.hpp"

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

struct Functor {
public:
    Functor(int& val)
        : m_value(val) {};

    void operator()() const
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "m_value = " << m_value << std::endl;
    };

private:
    int& m_value;
};

struct FunctorNew {
public:
    FunctorNew(void (*func_ptr)())
        : m_func_ptr(func_ptr) {};

    void operator()()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_func_ptr();
    };

private:
    void (*m_func_ptr)();
};

struct FunctorNewWithArg {
public:
    FunctorNewWithArg(void (*func_ptr)(int arg))
        : m_func_ptr(func_ptr) {};

    void operator()(int arg)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_func_ptr(arg);
    };

private:
    void (*m_func_ptr)(int arg);
};

template <typename Callable>
void func(const Callable& callable) { callable(); }

template <typename Callable, typename T>
void func(Callable& callable, T& value)
{
    callable(value);
}

void other_function() { }

extern void function_test(int i);

int main()
{

    cppcourse::unique_ptr<int> unique_ptr_test;
    auto test_one = cppcourse::make_unique<int>();

    struct TestStruct {
        TestStruct(int first)
            : m_first(first) {};
        int m_first;
    };

    auto test_two = cppcourse::make_unique<TestStruct>(6);
    std::cout << "test_two.first = " << test_two.get()->m_first << std::endl;

    function_test(5);

    int test = 10;
    Functor f(test);
    f();

    func(f);

    auto my_white_lambda = [&test]() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "test = " << test << std::endl;
    };
    my_white_lambda();
    func(my_white_lambda);

    auto lambda_with_param = [](auto& arg) {
        std::cout << "arg = " << arg << std::endl;
    };
    lambda_with_param(test);
    lambda_with_param("auto &arg");

    func(lambda_with_param, "hello_world");

    FunctorNew fn(other_function);
    fn();

    std::function<void()> fn2([]() { std::cout << "AAAAA" << std::endl; });
    fn2();
    func(fn2);
    func([]() { std::cout << "AAAAA" << std::endl; });

    std::vector<int> vec;
    std::iterator<int, int> iter;
}

// SomethingRef -> SomethingPtr
// auto [it, inserted] = map.emplace(1, 2); -> see cppref
// int array with struct or class with element access operator + what else may
// be needed
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