#include "algorithms/heap_sort.hpp"

#include <stdexcept>
#include <algorithm>

namespace dsa::algorithms {

std::size_t parent(std::size_t i) {
    return (i - 1) / 2;
}

std::size_t left_child(std::size_t i) {
    return 2 * i + 1;
}

std::size_t right_child(std::size_t i) {
    return 2 * i + 2;
}

void max_heapify(
    std::vector<int>& values,
    std::size_t heap_size,
    std::size_t i
) {
    std::size_t left = left_child(i);
    std::size_t right = right_child(i);
    std::size_t largest = i;

    if (left < heap_size && values[left] > values[i]) {
        largest = left;
    }
    
    if (right < heap_size && values[right] > values[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(values[i], values[largest]);
        max_heapify(values, heap_size, largest);
    }
}

void min_heapify(
    std::vector<int>& values,
    std::size_t heap_size,
    std::size_t i
) {
    std::size_t left = left_child(i);
    std::size_t right = right_child(i);
    std::size_t smallest = i;

    if (left < heap_size && values[left] < values[i]) {
        smallest = left;
    }
    
    if (right < heap_size && values[right] < values[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        std::swap(values[i], values[smallest]);
        min_heapify(values, heap_size, smallest);
    }
}

void build_max_heap(std::vector<int>& values) {
    if (values.empty()) {
        return;
    }

    for (int i = static_cast<int>(values.size() / 2) - 1; i >= 0; --i) {
        max_heapify(values, values.size(), static_cast<std::size_t>(i));
    }
}

void build_min_heap(std::vector<int>& values) {
    if (values.empty()) {
        return;
    }

    for (int i = static_cast<int>(values.size() / 2) - 1; i >= 0; --i) {
        min_heapify(values, values.size(), static_cast<std::size_t>(i));
    }
}

void heapsort(
    std::vector<int>& values,
    HeapType type
) {
    if (values.empty()) {
        return;
    }

    if (type == HeapType::max_heap) {
        build_max_heap(values);
    } else if (type == HeapType::min_heap) {
        build_min_heap(values);
    } else {
        throw std::invalid_argument("Heap type is not valid");
    }
    
    std::size_t heap_size = values.size();
    
    for (std::size_t i = values.size() - 1; i > 0; --i) {
        std::swap(values[0], values[i]);
        --heap_size;

        if (type == HeapType::max_heap) {
            max_heapify(values, heap_size, 0);
        } else if (type == HeapType::min_heap) {
            min_heapify(values, heap_size, 0);
        }
    }
}

}  // namespace dsa::algorithms