#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

enum class HeapType {
    max_heap,
    min_heap
};

std::size_t parent(std::size_t i);
std::size_t left_child(std::size_t i);
std::size_t right_child(std::size_t i);

void max_heapify(
    std::vector<int>& values,
    std::size_t heap_size,
    std::size_t i
);

void min_heapify(
    std::vector<int>& values,
    std::size_t heap_size,
    std::size_t i
);

void build_max_heap(std::vector<int>& values);
void build_min_heap(std::vector<int>& values);

void heapsort(
    std::vector<int>& values,
    HeapType type = HeapType::max_heap
);

}  // namespace dsa::algorithms