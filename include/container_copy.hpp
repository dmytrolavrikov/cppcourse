class allocator_with_new {
public:
    int* allocate(std::size_t size = c_base_size)
    {
        int* buffer = new int[c_base_size];
        return buffer;
    }

    void deallocate(int* buffer)
    {
        delete [] buffer;
    }

    void reallocate(int* buffer, std::size_t new_capacity, std::size_t current_size)
    {

        int* new_buf = allocate(new_capacity);
        for (std::size_t i = 0; i < current_size; ++i) {
            new_buf[i] = buffer[i];
        }

        deallocate(buffer);
        buffer = new_buf;
    }

private:
    std::size_t allocation_count;
};

class allocator_with_malloc {
public:
    int* allocate(std::size_t size = c_base_size)
    {
        int* buffer = (int*)malloc(c_base_size * sizeof(int));
        return buffer;
    }

    void reallocate(int* buffer, std::size_t new_capacity, std::size_t current_size)
    {
        void* new_buffer = realloc(buffer, new_capacity * sizeof(int));
        if (new_buffer != nullptr) {
            buffer = static_cast<int*>(new_buffer);
        }
    }

    void deallocate(int* buffer)
    {
        free(buffer);
    }
private:
    std::size_t allocation_count;
};