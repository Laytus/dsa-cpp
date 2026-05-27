#pragma once

#include <cstddef>

namespace dsa::data_structures {

class Queue {
public:
    // Constructor
    explicit Queue(std::size_t capacity);

    // Destructor
    ~Queue();

    // Copy constructor
    Queue(const Queue& other);
    // Copy assignment operator
    Queue& operator=(const Queue& other);

    // Move constructor
    Queue(Queue&& other) noexcept;
    // Move assignment operator
    Queue& operator=(Queue&& other) noexcept;

    void enqueue(int value);
    int dequeue();

    int head() const;
    int tail() const;
    
    bool empty() const;
    bool full() const;

    std::size_t size() const;
    std::size_t capacity() const;

private:
    int* data_;
    std::size_t capacity_;
    std::size_t head_;
    std::size_t tail_;
};

}  // namespace dsa::data_structures