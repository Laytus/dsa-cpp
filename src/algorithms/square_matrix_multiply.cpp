#include "algorithms/square_matrix_multiply.hpp"

#include <cstddef>

// using Matrix = std::vector<std::vector<int>>;

namespace dsa::algorithms {

Matrix square_matrix_multiply(const Matrix& A, const Matrix& B) {
    std::size_t n = A.size();
    Matrix C(n, std::vector<int>(n, 0));

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            C[i][j] = 0;
            
            for (std::size_t k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

}  // namespace dsa::algorithms