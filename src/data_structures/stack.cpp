#include "data_structures/stack.hpp"

#include <stdexcept>

namespace dsa::data_structures {

Stack::Stack(std::size_t capacity)
    : data_(nullptr),
      capacity_(capacity),
      top_(0) {
    if (capacity == 0) {
        throw std::underflow_error("Stack capacity must be greater than zero");
    }

    data_ = new int[capacity];
}

Stack::~Stack() {
    delete[] data_;
}

Stack::Stack(const Stack& other)
    : data_(new int[other.capacity_]),
      capacity_(other.capacity_),
      top_(other.top_) {
    for (std::size_t i = 0; i < top_; ++i) {
        data_[i] = other.data_[i];
    }
}

Stack& Stack::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    int* new_data = new int[other.capacity_];

    for (std::size_t i = 0; i < other.top_; ++i) {
        new_data[i] = other.data_[i];
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = other.capacity_;
    top_ = other.top_;

    return *this;
}

Stack::Stack(Stack&& other) noexcept
    : data_(other.data_),
      capacity_(other.capacity_),
      top_(other.top_) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.top_ = 0;
}

Stack& Stack::operator=(Stack&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    capacity_ = other.capacity_;
    top_ = other.top_;

    other.data_ = nullptr;
    other.capacity_ = 0;
    other.top_ = 0;

    return *this;
}

void Stack::push(int value) {
    if (top_ == capacity_) {
        throw std::overflow_error("Stack overflow");
    }

    data_[top_] = value;
    ++top_;
}

int Stack::pop() {
    if (empty()) {
        throw std::underflow_error("Stack underflow");
    }

    --top_;
    return data_[top_];
}

int Stack::top() const {
    if (empty()) {
        throw std::underflow_error("Stack underflow");
    }

    return data_[top_ - 1];
}

bool Stack::empty() const {
    return top_ == 0;
}

bool Stack::full() const {
    return top_ == capacity_;
}

std::size_t Stack::size() const {
    return top_;
}

std::size_t Stack::capacity() const {
    return capacity_;
}

}  // dsa::data_structures