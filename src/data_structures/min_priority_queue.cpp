#include "data_structures/min_priority_queue.hpp"

#include "algorithms/heap_sort.hpp"

#include <stdexcept>
#include <algorithm>
#include <limits>

namespace dsa::data_structures {

MinPriorityQueue::MinPriorityQueue(std::size_t capacity)
    : set_(nullptr),
      capacity_(capacity),
      heap_size_(0) {
    if (capacity == 0) {
        throw std::underflow_error("Min Priority Queue capacity must be greater than zero");
    }

    set_ = new Node*[capacity_];

    for (std::size_t i = 0; i < capacity_; ++i) {
        set_[i] = nullptr;
    }
}

MinPriorityQueue::~MinPriorityQueue() {
    delete[] set_;
}

MinPriorityQueue::MinPriorityQueue(const MinPriorityQueue& other)
    : set_(new Node*[other.capacity_]),
      capacity_(other.capacity_),
      heap_size_(other.heap_size_) {
    for (std::size_t i = 0; i < heap_size_; ++i) {
        set_[i] = other.set_[i];
        set_[i]->heap_index = i;
    }

    for (std::size_t i = heap_size_; i < capacity_; ++i) {
        set_[i] = nullptr;
    }
}

MinPriorityQueue& MinPriorityQueue::operator=(const MinPriorityQueue& other) {
    if (this == &other) {
        return *this;
    }

    Node** new_data = new Node*[other.capacity_];

    for (std::size_t i = 0; i < other.heap_size_; ++i) {
        new_data[i] = other.set_[i];
        new_data[i]->heap_index = i;
    }

    for (std::size_t i = other.heap_size_; i < other.capacity_; ++i) {
        new_data[i] = nullptr;
    }

    delete[] set_;

    set_ = new_data;
    capacity_ = other.capacity_;
    heap_size_ = other.heap_size_;

    return *this;
}

MinPriorityQueue::MinPriorityQueue(MinPriorityQueue&& other) noexcept
    : set_(other.set_),
      capacity_(other.capacity_),
      heap_size_(other.heap_size_) {
    other.set_ = nullptr;
    other.capacity_ = 0;
    other.heap_size_ = 0;
}

MinPriorityQueue& MinPriorityQueue::operator=(MinPriorityQueue&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] set_;

    set_ = other.set_;
    capacity_ = other.capacity_;
    heap_size_ = other.heap_size_;
    
    other.set_ = nullptr;
    other.capacity_ = 0;
    other.heap_size_ = 0;

    return *this;
}

Node* MinPriorityQueue::minimum() const {
    if (heap_size_ < 1) {
        throw std::underflow_error("Priority queue underflow");
    }

    return set_[0];
}

Node* MinPriorityQueue::extract_min() {
    Node* min = minimum();

    set_[0] = set_[heap_size_ - 1];
    --heap_size_;
    set_[heap_size_] = nullptr;

    min->heap_index = std::numeric_limits<std::size_t>::max();

    if (heap_size_ > 0) {
        set_[0]->heap_index = 0;
        min_heapify(0);
    }

    return min;
}

void MinPriorityQueue::decrease_key(
    Node* node,
    std::size_t new_key
) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (new_key > node->key) {
        throw std::invalid_argument("New key is greater than current key");
    }

    std::size_t i = find_index(node);
    node->key = new_key;

    while (i > 0) {
        const std::size_t parent_index = dsa::algorithms::parent(i);
        
        if (set_[parent_index]->key <= set_[i]->key) {
            break;
        }

        std::swap(set_[parent_index], set_[i]);
        set_[parent_index]->heap_index = parent_index;
        set_[i]->heap_index = i;

        i = parent_index;
    }
}

void MinPriorityQueue::insert(Node* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (heap_size_ == capacity_) {
        throw std::overflow_error("Priority queue overflow");
    }

    const std::size_t original_key = node->key;
    
    node->key = std::numeric_limits<std::size_t>::max();
    node->heap_index = heap_size_;
    set_[heap_size_] = node;
    ++heap_size_;

    decrease_key(node, original_key);
}

std::size_t MinPriorityQueue::capacity() const {
    return capacity_;
}

std::size_t MinPriorityQueue::heap_size() const {
    return heap_size_;
}

std::size_t MinPriorityQueue::find_index(Node* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    const std::size_t i = node->heap_index;

    if (i >= heap_size_ || set_[i] != node) {
        throw std::invalid_argument("Node not found in priority queue");
    }

    return i;
}

void MinPriorityQueue::min_heapify(
    std::size_t i
) {
    std::size_t left = dsa::algorithms::left_child(i);
    std::size_t right = dsa::algorithms::right_child(i);
    std::size_t smallest = i;

    if (left < heap_size_ && set_[left]->key < set_[smallest]->key) {
        smallest = left;
    }
    
    if (right < heap_size_ && set_[right]->key < set_[smallest]->key) {
        smallest = right;
    }

    if (smallest != i) {
        std::swap(set_[i], set_[smallest]);
        set_[i]->heap_index = i;
        set_[smallest]->heap_index = smallest;
        
        min_heapify(smallest);
    }
}

}  // namespace dsa::data_structures