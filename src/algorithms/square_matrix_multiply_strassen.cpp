#include "algorithms/square_matrix_multiply_strassen.hpp"

#include "algorithms/square_matrix_multiply_recursive.hpp"

#include <cstddef>

namespace dsa::algorithms {

namespace {

Matrix substract_matrices(
    const Matrix& A, 
    const Matrix& B
) {
    std::size_t n = A.size();

    Matrix result(n, std::vector<int>(n, 0));

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }

    return result;
}

}  // namespace

Matrix square_matrix_multiply_strassen(
    const Matrix& A,
    const Matrix& B
) {
    const std::size_t n = A.size();

    Matrix C(n, std::vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    std::size_t mid = A.size() / 2;

    Matrix A11 = submatrix(A, 0, 0, mid);
    Matrix A12 = submatrix(A, 0, mid, mid);
    Matrix A21 = submatrix(A, mid, 0, mid);
    Matrix A22 = submatrix(A, mid, mid, mid);

    Matrix B11 = submatrix(B, 0, 0, mid);
    Matrix B12 = submatrix(B, 0, mid, mid);
    Matrix B21 = submatrix(B, mid, 0, mid);
    Matrix B22 = submatrix(B, mid, mid, mid);

    Matrix S1 = substract_matrices(B12, B22);
    Matrix S2 = add_matrices(A11, A12);
    Matrix S3 = add_matrices(A21, A22);
    Matrix S4 = substract_matrices(B21, B11);
    Matrix S5 = add_matrices(A11, A22);
    Matrix S6 = add_matrices(B11, B22);
    Matrix S7 = substract_matrices(A12, A22);
    Matrix S8 = add_matrices(B21, B22);
    Matrix S9 = substract_matrices(A11, A21);
    Matrix S10 = add_matrices(B11, B12);

    Matrix P1 = square_matrix_multiply_strassen(A11, S1);
    Matrix P2 = square_matrix_multiply_strassen(S2, B22);
    Matrix P3 = square_matrix_multiply_strassen(S3, B11);
    Matrix P4 = square_matrix_multiply_strassen(A22, S4);
    Matrix P5 = square_matrix_multiply_strassen(S5, S6);
    Matrix P6 = square_matrix_multiply_strassen(S7, S8);
    Matrix P7 = square_matrix_multiply_strassen(S9, S10);

    for (std::size_t i = 0; i < mid; ++i) {
        for (std::size_t j = 0; j < mid; ++j) {
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            C[i][mid + j] = P1[i][j] + P2[i][j];
            C[mid + i][j] = P3[i][j] + P4[i][j];
            C[mid + i][mid + j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    return C;
}

}  // dsa::algorithms