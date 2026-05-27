#pragma once

#include <cstddef>

namespace dsa::data_structures {

class Stack {
public:
    // Constructor
    explicit Stack(std::size_t capacity);

    // Destructor
    ~Stack();

    // Copy constructor
    Stack(const Stack& other);
    // Copy assignment operator
    Stack& operator=(const Stack& other);

    // Move constructor
    Stack(Stack&& other) noexcept;
    // Move assignment operator
    Stack& operator=(Stack&& other) noexcept;

    void push(int value);
    int pop();
    int top() const;

    bool empty() const;
    bool full() const;

    std::size_t size() const;
    std::size_t capacity() const;

private:
    int* data_;
    std::size_t capacity_;
    std::size_t top_;
};

}  // namespace dsa::data_structures