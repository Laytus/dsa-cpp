#include "algorithms/huffman_codes.hpp"

#include <queue>

namespace dsa::algorithms {

HuffmanTree greedy_huffman(
    const std::vector<std::pair<char, std::size_t>>& frequencies
) {
    HuffmanTree tree{{}, nullptr};

    if (frequencies.empty()) {
        return tree;
    }

    std::priority_queue<
        HuffmanNode*,
        std::vector<HuffmanNode*>,
        HuffmanCompare
    > queue;

    for (const auto& [symbol, freq] : frequencies) {
        tree.nodes.push_back(
            std::make_unique<HuffmanNode>(
                HuffmanNode{symbol, freq, nullptr, nullptr}
            )
        );

        queue.push(tree.nodes.back().get());
    }

    while (queue.size() > 1) {
        HuffmanNode* x = queue.top();
        queue.pop();
        
        HuffmanNode* y = queue.top();
        queue.pop();

        tree.nodes.push_back(
            std::make_unique<HuffmanNode>(
                HuffmanNode{'\0', x->freq + y->freq, x, y}
            )
        );

        queue.push(tree.nodes.back().get());
    }

    tree.root = queue.top();

    return tree;
}

// REVIEW
HuffmanTree dynamic_alphabetic_huffman(
    const std::vector<std::pair<char, std::size_t>>& frequencies
) {
    HuffmanTree tree{{}, nullptr};

    if (frequencies.empty()) {
        return tree;
    }

    const std::size_t n = frequencies.size();

    std::vector<std::vector<std::size_t>> dp(
        n,
        std::vector<std::size_t>(n, 0)
    );

    std::vector<std::vector<std::size_t>> split(
        n,
        std::vector<std::size_t>(n, 0)
    );

    std::vector<std::size_t> prefix(n + 1, 0);

    for (std::size_t i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + frequencies[i].second;
    }

    auto range_sum = [&](std::size_t i, std::size_t j) -> std::size_t {
        return prefix[j + 1] - prefix[i];
    };

    for (std::size_t length = 2; length <= n; ++length) {
        for (std::size_t i = 0; i + length <= n; ++i) {
            const std::size_t j = i + length - 1;

            dp[i][j] = static_cast<std::size_t>(-1);

            for (std::size_t k = i; k < j; ++k) {
                const std::size_t candidate =
                    dp[i][k]
                    + dp[k + 1][j]
                    + range_sum(i, j);

                if (candidate < dp[i][j]) {
                    dp[i][j] = candidate;
                    split[i][j] = k;
                }
            }
        }
    }

    auto build = [&](auto&& self, std::size_t i, std::size_t j) -> HuffmanNode* {
        if (i == j) {
            tree.nodes.push_back(
                std::make_unique<HuffmanNode>(
                    HuffmanNode{
                        frequencies[i].first,
                        frequencies[i].second,
                        nullptr,
                        nullptr
                    }
                )
            );

            return tree.nodes.back().get();
        }
        
        const std::size_t k = split[i][j];

        HuffmanNode* left = self(self, i, k);
        HuffmanNode* right = self(self, k + 1, j);

        tree.nodes.push_back(
            std::make_unique<HuffmanNode>(
                HuffmanNode{
                    '\0',
                    left->freq + right->freq,
                    left,
                    right
                }
            )
        );

        return tree.nodes.back().get();
    };

    tree.root = build(build, 0, n - 1);

    return tree;
}

}  // namespace dsa::algorithms