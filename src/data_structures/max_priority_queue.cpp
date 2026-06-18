#include "data_structures/max_priority_queue.hpp"

#include "algorithms/heap_sort.hpp"

#include <stdexcept>
#include <algorithm>

namespace dsa::data_structures {

MaxPriorityQueue::MaxPriorityQueue(std::size_t capacity)
    : set_(nullptr),
      capacity_(capacity),
      heap_size_(0) {
    if (capacity == 0) {
        throw std::underflow_error("Max Priority Queue capacity must be greater than zero");
    }

    set_ = new Node*[capacity_];
}

MaxPriorityQueue::~MaxPriorityQueue() {
    delete[] set_;
}

MaxPriorityQueue::MaxPriorityQueue(const MaxPriorityQueue& other)
    : set_(new Node*[other.capacity_]),
      capacity_(other.capacity_),
      heap_size_(other.heap_size_) {
    for (std::size_t i = 0; i < heap_size_; ++i) {
        set_[i] = other.set_[i];
    }
    for (std::size_t i = heap_size_; i < capacity_; ++i) {
        set_[i] = nullptr;
    }
}

MaxPriorityQueue& MaxPriorityQueue::operator=(const MaxPriorityQueue& other) {
    if (this == &other) {
        return *this;
    }

    Node** new_data = new Node*[other.capacity_];

    for (std::size_t i = 0; i < other.heap_size_; ++i) {
        new_data[i] = other.set_[i];
    }

    delete[] set_;

    set_ = new_data;
    capacity_ = other.capacity_;
    heap_size_ = other.heap_size_;

    for (std::size_t i = heap_size_; i < capacity_; ++i) {
        set_[i] = nullptr;
    }

    return *this;
}

MaxPriorityQueue::MaxPriorityQueue(MaxPriorityQueue&& other) noexcept
    : set_(other.set_),
      capacity_(other.capacity_),
      heap_size_(other.heap_size_) {
    other.set_ = nullptr;
    other.capacity_ = 0;
    other.heap_size_ = 0;
}

MaxPriorityQueue& MaxPriorityQueue::operator=(MaxPriorityQueue&& other) noexcept {
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

Node* MaxPriorityQueue::maximum() const {
    if (heap_size_ < 1) {
        throw std::underflow_error("Priority queue underflow");
    }

    return set_[0];
}

Node* MaxPriorityQueue::extract_max() {
    Node* max = maximum();

    set_[0] = set_[heap_size_ - 1];
    --heap_size_;

    if (heap_size_ > 0) {
        max_heapify(0);
        set_[heap_size_] = nullptr;
    }

    return max;
}

void MaxPriorityQueue::increase_key(
    Node* node,
    std::size_t new_key
) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (new_key < node->key) {
        throw std::invalid_argument("New key is smaller than current key");
    }

    std::size_t i = find_index(node);
    node->key = new_key;

    while (i > 0) {
        const std::size_t parent_index = dsa::algorithms::parent(i);
        
        if (set_[parent_index]->key >= set_[i]->key) {
            break;
        }

        std::swap(set_[parent_index], set_[i]);
        i = parent_index;
    }
}

void MaxPriorityQueue::insert(Node* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (heap_size_ == capacity_) {
        throw std::overflow_error("Priority queue overflow");
    }

    const std::size_t original_key = node->key;
    
    node->key = 0;
    set_[heap_size_] = node;
    ++heap_size_;

    increase_key(node, original_key);
}

std::size_t MaxPriorityQueue::capacity() const {
    return capacity_;
}

std::size_t MaxPriorityQueue::heap_size() const {
    return heap_size_;
}

std::size_t MaxPriorityQueue::find_index(Node* node) {
    for (std::size_t i = 0; i < heap_size_; ++i) {
        if (set_[i] == node) {
            return i;
        }
    }

    throw std::invalid_argument("Node not found in priority queue");
}

void MaxPriorityQueue::max_heapify(
    std::size_t i
) {
    std::size_t left = dsa::algorithms::left_child(i);
    std::size_t right = dsa::algorithms::right_child(i);
    std::size_t largest = i;

    if (left < heap_size_ && set_[left]->key > set_[largest]->key) {
        largest = left;
    }
    
    if (right < heap_size_ && set_[right]->key > set_[largest]->key) {
        largest = right;
    }

    if (largest != i) {
        std::swap(set_[i], set_[largest]);
        max_heapify(largest);
    }
}

}  // namespace dsa::data_structures