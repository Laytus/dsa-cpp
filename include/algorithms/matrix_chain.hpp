#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace dsa::algorithms {

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
void validate_matrix(const Matrix<T>& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("Matrix rows must be greater than 0");
    }
    
    if (matrix[0].empty()) {
        throw std::invalid_argument("Matrix columns must be greater than 0");
    }

    const std::size_t cols = matrix[0].size();

    for (const auto& row : matrix) {
        if (row.size() != cols) {
            throw std::invalid_argument("Matrix rows must all have the same number of columns");
        }
    }
}

template <typename T>
Matrix<T> matrix_multiply(const Matrix<T>& A, const Matrix<T>& B) {
    validate_matrix(A);
    validate_matrix(B);

    const std::size_t rows = A.size();
    const std::size_t inner = A[0].size();
    const std::size_t cols = B[0].size();

    if (B.size() != inner) {
        throw std::invalid_argument("A columns must match B rows");
    }
    
    Matrix<T> C(rows, std::vector<T>(cols, T{}));

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            for (std::size_t k = 0; k < inner; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

template <typename T>
std::vector<int> matrix_chain_sizes(const std::vector<Matrix<T>>& matrices) {
    if (matrices.empty()) {
        throw std::invalid_argument("Matrix chain must contain at least one matrix");
    }

    std::vector<int> p;
    p.reserve(matrices.size() + 1);

    validate_matrix(matrices[0]);

    p.push_back(static_cast<int>(matrices[0].size()));
    p.push_back(static_cast<int>(matrices[0][0].size()));

    for (std::size_t i = 1; i < matrices.size(); ++i) {
        validate_matrix(matrices[i]);

        const std::size_t rows = matrices[i].size();
        const std::size_t cols = matrices[i][0].size();

        if (rows != static_cast<std::size_t>(p[i])) {
            throw std::invalid_argument("Matrix rows must match previous matrix columns");
        }

        p.push_back(static_cast<int>(cols));
    }

    return p;
}

std::pair<Matrix<int>, Matrix<std::size_t>> matrix_chain_order(
    const std::vector<int>& p,
    const std::size_t n
) {
    if (n == 0) {
        throw std::invalid_argument("Matrix chain legth must be greater than 0");
    }
    
    if (p.size() != n + 1) {
        throw std::invalid_argument("Dimension vector p must have size n + 1");
    }

    Matrix<int> m(n, std::vector<int>(n, 0));
    Matrix<std::size_t> s(n, std::vector<std::size_t>(n, 0));

    for (std::size_t l = 2; l <= n; ++l) {
        for (std::size_t i = 0; i <= n - l; ++i) {
            const std::size_t j = i + l - 1;

            m[i][j] = std::numeric_limits<int>::max();

            for (std::size_t k = i; k < j; ++k) {
                const int q = 
                    m[i][k] 
                    + m[k + 1][j] 
                    + p[i] * p[k + 1] * p[j + 1];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    return {m, s};
}

template <typename T>
Matrix<T> matrix_chain_multiply_recurrence(
    const std::vector<Matrix<T>>& matrices,
    const Matrix<std::size_t>& s,
    std::size_t i,
    std::size_t j
) {
    if (i == j) {
        return matrices[i];
    }

    const std::size_t k = s[i][j];

    Matrix<T> left = matrix_chain_multiply_recurrence(matrices, s, i, k);
    Matrix<T> right = matrix_chain_multiply_recurrence(matrices, s, k + 1, j);

    return matrix_multiply(left, right);
}

template <typename T>
Matrix<T> matrix_chain_multiply(
    const std::vector<Matrix<T>>& matrices
) {
    const std::size_t n = matrices.size();

    const std::vector<int> p = matrix_chain_sizes(matrices);
    const auto [m, s] = matrix_chain_order(p, n);

    return matrix_chain_multiply_recurrence(matrices, s, 0, n - 1);
}

}  // namespace dsa::algorithms