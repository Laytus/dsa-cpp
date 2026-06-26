#pragma once

#include <utility>
#include <cstddef>
#include <vector>
#include <memory>

namespace dsa::algorithms {

using MatrixSize_t = std::vector<std::vector<std::size_t>>;
using MatrixDouble = std::vector<std::vector<double>>;

struct OptimalBSTResult {
    MatrixDouble e;
    MatrixDouble w;
    MatrixSize_t root;
};

struct OptimalBSTNode {
    std::size_t key_index;
    std::unique_ptr<OptimalBSTNode> left;
    std::unique_ptr<OptimalBSTNode> right;
};

OptimalBSTResult optimal_BST(
    const std::vector<double>& p,
    const std::vector<double>& q
);

std::unique_ptr<OptimalBSTNode> build_optimal_BST(
    const MatrixSize_t& root,
    std::size_t i,
    std::size_t j
);

}  // namespace dsa::algorithms