#pragma once

#include "data_structures/min_priority_queue.hpp"

#include <cstddef>
#include <vector>
#include <string>
#include <utility>
#include <memory>

namespace dsa::algorithms {

struct HuffmanNode {
    char symbol;
    std::size_t freq;
    HuffmanNode* left;
    HuffmanNode* right;
};

struct HuffmanTree {
    std::vector<std::unique_ptr<HuffmanNode>> nodes;
    HuffmanNode* root;
};

struct HuffmanCompare {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b) const {
        return a->freq > b->freq;
    }
};

HuffmanTree greedy_huffman(
    const std::vector<std::pair<char, std::size_t>>& frequencies
);

// REVIEW
HuffmanTree dynamic_alphabetic_huffman(
    const std::vector<std::pair<char, std::size_t>>& frequencies
);

}  // namespace dsa::algorithms