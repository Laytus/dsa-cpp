#pragma once

#include "data_structures/priority_queue_node.hpp"

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

class MaxPriorityQueue {
public:
    explicit MaxPriorityQueue(std::size_t capacity);

    ~MaxPriorityQueue();

    MaxPriorityQueue(const MaxPriorityQueue& other);
    MaxPriorityQueue& operator=(const MaxPriorityQueue& other);
    
    MaxPriorityQueue(MaxPriorityQueue&& other) noexcept;
    MaxPriorityQueue& operator=(MaxPriorityQueue&& other) noexcept;

    Node* maximum() const;
    Node* extract_max();

    void increase_key(Node* node, std::size_t new_key);
    void insert(Node* node);

    std::size_t capacity() const;
    std::size_t heap_size() const;
private:
    std::size_t find_index(Node* node);
    void max_heapify(std::size_t i);
    
    Node** set_;
    std::size_t capacity_;
    std::size_t heap_size_;
};

}  // namespace dsa::data_structures