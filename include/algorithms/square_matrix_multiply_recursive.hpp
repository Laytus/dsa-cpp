#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

using Matrix = std::vector<std::vector<int>>;

Matrix submatrix(
    const Matrix& matrix, 
    std::size_t row_start,
    std::size_t col_start,
    std::size_t size
);

Matrix add_matrices(
    const Matrix& A, 
    const Matrix& B
);

void copy_submatrix(
    Matrix& target, 
    const Matrix& block,
    std::size_t row_start,
    std::size_t col_start
);

Matrix square_matrix_multiply_recursive(
    const Matrix& A,
    const Matrix& B
);

}  // namespace dsa::algorithms