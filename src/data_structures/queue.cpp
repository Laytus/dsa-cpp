#include "data_structures/queue.hpp"

#include <stdexcept>

namespace dsa::data_structures {

// Constructor
Queue::Queue(std::size_t capacity)
    : data_(nullptr),
      capacity_(capacity),
      head_(0),
      tail_(0) {
    if (capacity_ == 0) {
        throw std::underflow_error("Queue capacity must be greater than zero");
    }

    data_ = new int[capacity];
}

// Destructor
Queue::~Queue() {
    delete[] data_;
}

// Copy constructor
Queue::Queue(const Queue& other)
    : data_(new int[other.capacity_]),
      capacity_(other.capacity_),
      head_(other.head_),
      tail_(other.tail_) {
    for (std::size_t i = 0; i < capacity_; ++i) {
        data_[i] = other.data_[i];
    }
}

// Copy assignment operator
Queue& Queue::operator=(const Queue& other) {
    if (this == &other) {
        return *this;
    }

    int* new_data = new int[other.capacity_];

    for (std::size_t i = 0; i < other.capacity_; ++i) {
        new_data[i] = other.data_[i];
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = other.capacity_;
    head_ = other.head_;
    tail_ = other.tail_;

    return *this;
}

// Move constructor
Queue::Queue(Queue&& other) noexcept
    : data_(other.data_),
      capacity_(other.capacity_),
      head_(other.head_),
      tail_(other.tail_) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.head_ = 0;
    other.tail_ = 0;
}

// Move assignment operator
Queue& Queue::operator=(Queue&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    capacity_ = other.capacity_;
    head_ = other.head_;
    tail_ = other.tail_;
    
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.head_ = 0;
    other.tail_ = 0;

    return *this;
}

void Queue::enqueue(int value) {
    if (full()) {
        throw std::overflow_error("Queue overflow");
    }

    data_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
}

int Queue::dequeue() {
    if (empty()) {
        throw std::underflow_error("Queue underflow");
    }

    const int value = data_[head_];
    head_ = (head_ + 1) % capacity_;
    
    return value;
}

int Queue::head() const {
    if (empty()) {
        throw std::underflow_error("Queue underflow");
    }

    return data_[head_];
}

int Queue::tail() const {
    if (empty()) {
        throw std::underflow_error("Queue underflow");
    }

    const std::size_t last_index = (tail_ + capacity_ - 1) % capacity_;
    return data_[last_index];
}

bool Queue::empty() const {
    return head_ == tail_;
}

bool Queue::full() const {
    return (tail_ + 1) % capacity_ == head_;
}

std::size_t Queue::size() const {
    if (tail_ >= head_) {
        return tail_ - head_;
    }

    return capacity_ - head_ + tail_;
}

std::size_t Queue::capacity() const {
    return capacity_;
}

}  // namespace dsa::data_structures