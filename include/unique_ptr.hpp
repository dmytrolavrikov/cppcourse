#pragma once

#include <memory>
#include <utility>
namespace cppcourse {

template <typename T>
class unique_ptr {

public:
    unique_ptr()
        : m_data(nullptr) {};

    unique_ptr(T* data)
        : m_data(data) {};

    unique_ptr(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other)
        : m_data(other.m_data)
    {
        other.m_data = nullptr;
    };

    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr& operator=(unique_ptr&& other)
    {
        m_data = other.m_data;
        other.m_data = nullptr;
    };

    ~unique_ptr() { reset(nullptr); }

    T* get() const { return m_data; };

    void reset(T* data)
    {
        auto ptr = get();
        if (ptr) {
            delete ptr;
        }
        m_data = data;
    };

private:
    T* m_data;
};

// template <typename T>
// unique_ptr<T> make_unique() {
//     T* data = new T();
//     return unique_ptr<T>(data);
// };

// template <typename T, typename ARG>
// unique_ptr<T> make_unique(ARG arg) {
//     T* data = new T(arg);
//     return unique_ptr<T>(data);
// };

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... arg)
{
    auto ptr = new T(std::forward<Args>(arg)...);
    return unique_ptr<T>(ptr);
};

// TODO deleter

} // namespace cppcourse