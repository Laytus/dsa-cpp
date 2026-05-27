#pragma once

#include <vector>

namespace dsa::algorithms {

using Matrix = std::vector<std::vector<int>>;

Matrix square_matrix_multiply(const Matrix& A, const Matrix& B);

}  // namespace dsa::algorithms