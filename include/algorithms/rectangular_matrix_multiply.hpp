#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
void rectangular_matrix_multiply(
    const Matrix<T>& A,
    const Matrix<T>& B,
    Matrix<T>& C,
    std::size_t p,
    std::size_t q,
    std::size_t r
) {
    if (A.size() != p) {
        throw std::invalid_argument("A must have p rows");
    }

    for (const auto& row : A) {
        if (row.size() != q) {
            throw std::invalid_argument("A must have q columns");
        }
    }

    if (B.size() != q) {
        throw std::invalid_argument("B must have q rows");
    }

    for (const auto& row : B) {
        if (row.size() != r) {
            throw std::invalid_argument("B must have r columns");
        }
    }

    if (C.size() != p) {
        throw std::invalid_argument("C must have p rows");
    }

    for (const auto& row : C) {
        if (row.size() != r) {
            throw std::invalid_argument("C must have r columns");
        }
    }

    for (std::size_t i = 0; i < p; ++i) {
        for (std::size_t j = 0; j < r; ++j) {
            for (std::size_t k = 0; k < q; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

}  // namespace dsa::algorithms