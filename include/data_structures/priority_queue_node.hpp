#pragma once

#include <cstddef>

namespace dsa::data_structures {

struct Node {
    std::size_t key;
    int data;
    std::size_t heap_index = 0;
};

}  // dsa::data_structures