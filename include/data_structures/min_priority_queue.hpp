#pragma once

#include "data_structures/priority_queue_node.hpp"

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

class MinPriorityQueue {
public:
    explicit MinPriorityQueue(std::size_t capacity);

    ~MinPriorityQueue();

    MinPriorityQueue(const MinPriorityQueue& other);
    MinPriorityQueue& operator=(const MinPriorityQueue& other);
    
    MinPriorityQueue(MinPriorityQueue&& other) noexcept;
    MinPriorityQueue& operator=(MinPriorityQueue&& other) noexcept;

    Node* minimum() const;
    Node* extract_min();

    void decrease_key(Node* node, std::size_t new_key);
    void insert(Node* node);

    std::size_t capacity() const;
    std::size_t heap_size() const;
private:
    std::size_t find_index(Node* node);
    void min_heapify(std::size_t i);
    
    Node** set_;
    std::size_t capacity_;
    std::size_t heap_size_;
};

}  // namespace dsa::data_structures