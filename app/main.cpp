#include <print>
#include <cstddef>

#include "algorithms/square_matrix_multiply_recursive.hpp"
#include "utils/print_utils.hpp"

int main() {
    const dsa::algorithms::Matrix A {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    std::size_t mid = A.size() / 2;

    dsa::algorithms::Matrix A11 = dsa::algorithms::submatrix(A, 0, 0, mid);
    dsa::algorithms::Matrix A12 = dsa::algorithms::submatrix(A, 0, mid, 2);
    dsa::algorithms::Matrix A21 = dsa::algorithms::submatrix(A, mid, 0, 2);
    dsa::algorithms::Matrix A22 = dsa::algorithms::submatrix(A, mid, mid, 2);
    
    std::println("Matrix A11:");
    dsa::utils::print_matrix(A11);
    
    std::println("Matrix A11:");
    dsa::utils::print_matrix(A12);
    
    std::println("Matrix A11:");
    dsa::utils::print_matrix(A21);
    
    std::println("Matrix A11:");
    dsa::utils::print_matrix(A22);
    
    dsa::algorithms::Matrix C = dsa::algorithms::add_matrices(A11, A12);
    
    std::println("Matrix C:");
    dsa::utils::print_matrix(C);
    
    dsa::algorithms::Matrix X {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    dsa::algorithms::copy_submatrix(X, C, 0, 0);
    
    std::println("Matrix X:");
    dsa::utils::print_matrix(X);


    dsa::algorithms::Matrix Y {
        {1, 1},
        {1, 1}
    };

    dsa::algorithms::Matrix Z {
        {2, 0},
        {0, 2}
    };

    dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply_recursive(Y, Z);

    std::println("Matrix Result:");
    dsa::utils::print_matrix(result);
}