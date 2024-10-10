
#include <cstddef>
#include <cstdlib>
#include <new>
#include <type_traits>
#include <utility>
#include <iostream>

namespace cppcourse {

class container_libc
{

public:

    explicit container_libc()
    {
        buffer = (int*)malloc(c_base_size * sizeof(int));
    };

    container_libc(int* buf)
        : buffer(buf)
    {};

    container_libc(const container_libc& other)
        : container_libc(other.buffer)
    {};

    container_libc(container_libc&& other) noexcept
        : buffer(std::exchange(other.buffer, nullptr))
    {};

    container_libc& operator=(const container_libc& other)
    {
        if (this == &other)
            return *this;

        container_libc temp(other);
        std::swap(buffer, temp.buffer);

        return *this;
    };

    container_libc& operator=(container_libc&& other)
    {
        container_libc temp(std::move(other));
        std::swap(buffer, temp.buffer);
        return *this;
    };

    int& operator[](std::size_t index)
    {
        return buffer[index];
    };

    ~container_libc()
    {
        free(buffer);
    };

    void push_back(int element)
    {
        if (current_size > capacity) {
            realloc_(capacity * 2);
        }

        buffer[current_size] = element;
        current_size++;

    };

    int at(std::size_t index)
    {
        if (index > current_size) {
            return -1;
        }
        return buffer[index];
    };

    void assign(std::size_t index, int element)
    {
        if (index > current_size) {
            return;
        }
        buffer[index] = element;
        if (index > current_size) {
            current_size = index + 1;
        }
    };

    void erase(std::size_t index)
    {
        if (index > c_base_size) {
            return;
        }
        if (index == current_size) {
            current_size--;
        }
        buffer[index] = 0;
    };

    std::size_t size()
    {
        return current_size;
    };

private:
    void realloc_(std::size_t new_size)
    {

        std::cout << __PRETTY_FUNCTION__ << "new_size = " << new_size << std::endl;
        void* new_buffer = realloc(buffer, new_size * sizeof(int));
        if (new_buffer != nullptr) {
            buffer = (int*)new_buffer;
            capacity = new_size;
        }
    }

    static constexpr std::size_t c_base_size = 16;

    int* buffer;
    std::size_t current_size = 0;
    std::size_t capacity = c_base_size;

};

} // cppcourse