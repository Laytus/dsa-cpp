#include "algorithms/square_matrix_multiply_recursive.hpp"

namespace dsa::algorithms {

namespace {

void multiply_add_block(
    const Matrix& A,
    std::size_t a_row,
    std::size_t a_col,
    const Matrix& B,
    std::size_t b_row,
    std::size_t b_col,
    Matrix& C,
    std::size_t c_row,
    std::size_t c_col,
    std::size_t size
) {
    if (size == 1) {
        C[c_row][c_col] += A[a_row][a_col] * B[b_row][b_col];
        return;
    }

    const std::size_t mid = size / 2;

    // C11 += A11 * B11
    multiply_add_block(
        A, a_row, a_col,
        B, b_row, b_col,
        C, c_row, c_col,
        mid
    );

    // C11 += A12 * B21
    multiply_add_block(
        A, a_row, a_col + mid,
        B, b_row + mid, b_col,
        C, c_row, c_col,
        mid
    );

    // C12 += A11 * B12
    multiply_add_block(
        A, a_row, a_col,
        B, b_row, b_col + mid,
        C, c_row, c_col + mid,
        mid
    );

    // C12 += A12 * B22
    multiply_add_block(
        A, a_row, a_col + mid,
        B, b_row + mid, b_col + mid,
        C, c_row, c_col + mid,
        mid
    );

    // C21 += A21 * B11
    multiply_add_block(
        A, a_row + mid, a_col,
        B, b_row, b_col,
        C, c_row + mid, c_col,
        mid
    );

    // C21 += A22 * B21
    multiply_add_block(
        A, a_row + mid, a_col + mid,
        B, b_row + mid, b_col,
        C, c_row + mid, c_col,
        mid
    );

    // C22 += A21 * B12
    multiply_add_block(
        A, a_row + mid, a_col,
        B, b_row, b_col + mid,
        C, c_row + mid, c_col + mid,
        mid
    );

    // C22 += A22 * B22
    multiply_add_block(
        A, a_row + mid, a_col + mid,
        B, b_row + mid, b_col + mid,
        C, c_row + mid, c_col + mid,
        mid
    );
}

}  // namespace

Matrix submatrix(
    const Matrix& matrix, 
    std::size_t row_start,
    std::size_t col_start,
    std::size_t size
) {
    Matrix result(size, std::vector<int>(size, 0));

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            result[i][j] = matrix[row_start + i][col_start + j];
        }
    }

    return result;
}

Matrix add_matrices(
    const Matrix& A, 
    const Matrix& B
) {
    std::size_t n = A.size();

    Matrix result(n, std::vector<int>(n, 0));

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

void copy_submatrix(
    Matrix& target, 
    const Matrix& block,
    std::size_t row_start,
    std::size_t col_start
) {
    std::size_t n = block.size();

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            target[row_start + i][col_start + j] = block[i][j];
        }
    }
}

Matrix square_matrix_multiply_recursive(
    const Matrix& A,
    const Matrix& B
) {
    const std::size_t n = A.size();

    Matrix C(n, std::vector<int>(n, 0));

    // if (n == 1) {
    //     C[0][0] = A[0][0] * B[0][0];
    //     return C;
    // }

    // std::size_t mid = A.size() / 2;

    // Matrix A11 = submatrix(A, 0, 0, mid);
    // Matrix A12 = submatrix(A, 0, mid, mid);
    // Matrix A21 = submatrix(A, mid, 0, mid);
    // Matrix A22 = submatrix(A, mid, mid, mid);

    // Matrix B11 = submatrix(B, 0, 0, mid);
    // Matrix B12 = submatrix(B, 0, mid, mid);
    // Matrix B21 = submatrix(B, mid, 0, mid);
    // Matrix B22 = submatrix(B, mid, mid, mid);

    // Matrix C11 = add_matrices(
    //     square_matrix_multiply_recursive(A11, B11),
    //     square_matrix_multiply_recursive(A12, B21)
    // );
    
    // Matrix C12 = add_matrices(
    //     square_matrix_multiply_recursive(A11, B12),
    //     square_matrix_multiply_recursive(A12, B22)
    // );
    
    // Matrix C21 = add_matrices(
    //     square_matrix_multiply_recursive(A21, B11),
    //     square_matrix_multiply_recursive(A22, B21)
    // );
    
    // Matrix C22 = add_matrices(
    //     square_matrix_multiply_recursive(A21, B12),
    //     square_matrix_multiply_recursive(A22, B22)
    // );

    // copy_submatrix(C, C11, 0, 0);
    // copy_submatrix(C, C12, 0, mid);
    // copy_submatrix(C, C21, mid, 0);
    // copy_submatrix(C, C22, mid, mid);

    multiply_add_block(
        A, 0, 0,
        B, 0, 0,
        C, 0, 0,
        n
    );

    return C;
}

}  // namespace dsa::algorithms