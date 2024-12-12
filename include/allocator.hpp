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

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <new>

static constexpr std::size_t c_base_size = 16;

class allocator_with_new {
public:
    int* allocate(std::size_t size = c_base_size)
    {
        int* buffer = new int[size];
        return buffer;
    }

    void deallocate(int* buffer) { delete[] buffer; }

    void reallocate(int* buffer, std::size_t new_capacity,
        std::size_t current_size)
    {

        int* new_buf = allocate(new_capacity);
        for (std::size_t i = 0; i < current_size; ++i) {
            new_buf[i] = buffer[i];
        }

        deallocate(buffer);
        buffer = new_buf;
    }
};

class allocator_with_malloc {
public:
    int* allocate(std::size_t size = c_base_size)
    {
        int* buffer = (int*)malloc(size * sizeof(int));
        return buffer;
    }

    void reallocate(int* buffer, std::size_t new_capacity,
        std::size_t current_size)
    {
        void* new_buffer = realloc(buffer, new_capacity * sizeof(int));
        if (new_buffer != nullptr) {
            buffer = static_cast<int*>(new_buffer);
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(int* buffer) { free(buffer); }
};