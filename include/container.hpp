/** Copyright 2024 Dmytro Lavrikov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>
#include "allocator.hpp"

namespace cppcourse {

template <typename Allocator = allocator_with_new>
class container
{

public:
  explicit container() : buffer(allocator.allocate()){};

  container(size_t initial_capacity)
      : capacity(initial_capacity), buffer(allocator.allocate(initial_capacity)) {}

  container(int *buf) : buffer(buf){};

  container(const container &other)
      : current_size(other.current_size),
        buffer(copy(other.buffer, other.current_size)) {}

  container(container &&other) noexcept
      : buffer(std::exchange(other.buffer, nullptr)){};

  container &operator=(const container &other) {
    if (this != &other) {
        // check for leak
        buffer = copy(other, current_size);
    }
    return *this;
  };

    container& operator=(container&& other)
    {
        container temp(std::move(other));
        std::swap(buffer, temp.buffer);
        return *this;
    };

    int& operator[](std::size_t index)
    {
        return buffer[index];
    };

    ~container()
    {
        allocator.deallocate(buffer);
    };

    void push_back(int element)
    {
        if (current_size >= capacity) {
            realloc_(capacity * 2);
        }

        buffer[current_size] = element;
        current_size++;
    };

    int at(std::size_t index)
    {
        if (index + 1 > current_size) {
            return -1;
        }
        return buffer[index];
    };

    void assign(std::size_t index, int element)
    {
        if (index >= current_size) {
            return;
        }
        buffer[index] = element;
        if (index > current_size) {
            current_size = index + 1;
        }
    };

    void erase(std::size_t index)
    {
        if (index >= current_size) {
            return;
        }

        current_size--;
        buffer[index] = 0;
    };

    std::size_t size()
    {
        return current_size;
    };

    bool empty()
    {
        return current_size == 0;
    };

private:
    void realloc_(std::size_t new_capacity)
    {
        allocator.reallocate(buffer, new_capacity, current_size);
        capacity = new_capacity;
    }

    int* copy(int* src, int size)
    {
        int* new_buf = allocator.allocate(size);
        for (std::size_t i = 0; i < size; ++i) {
            new_buf[i] = src[i];
        }
        return new_buf;
    }

    int* buffer;
    std::size_t current_size = 0;
    std::size_t capacity = c_base_size;
    Allocator allocator;
};
} // namespace cppcourse