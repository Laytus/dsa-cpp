#include "algorithms/optimal_BST.hpp"

#include <limits>
#include <memory>
#include <stdexcept>

namespace dsa::algorithms {
    
OptimalBSTResult optimal_BST(
    const std::vector<double>& p,
    const std::vector<double>& q
) {
    const std::size_t n = p.size();

    if (q.size() != n + 1) {
        throw std::invalid_argument("q must have p.size() + 1");
    }

    MatrixDouble e(n + 1, std::vector<double>(n + 1, 0.0));
    MatrixDouble w(n + 1, std::vector<double>(n + 1, 0.0));
    MatrixSize_t root(n, std::vector<std::size_t>(n, 0));

    for (std::size_t i = 0; i <= n; ++i) {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }

    for (std::size_t l = 1; l <= n; ++l) {
        for (std::size_t i = 0; i <= n - l; ++i) {
            const std::size_t j = i + l;

            e[i][j] = std::numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

            for (std::size_t r = i; r < j; ++r) {
                const double t =
                    e[i][r]
                    + e[r + 1][j]
                    + w[i][j];
                
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j - 1] = r;
                }
            }
        }
    }

    return {e, w, root};
}

std::unique_ptr<OptimalBSTNode> build_optimal_BST(
    const MatrixSize_t& root,
    std::size_t i,
    std::size_t j
) {
    if (i > j) {
        return nullptr;
    }

    const std::size_t r = root[i][j];

    auto node = std::make_unique<OptimalBSTNode>();
    node->key_index = r;

    if (r > i) {
        node->left = build_optimal_BST(root, i, r - 1);
    }

    if (r < j) {
        node->right = build_optimal_BST(root, r + 1, j);
    }

    return node;
}

}  // namespace dsa::algorithms