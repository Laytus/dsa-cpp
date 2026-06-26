#include <catch2/catch_test_macros.hpp>

#include "algorithms/matrix_chain.hpp"

using dsa::algorithms::Matrix;
using dsa::algorithms::matrix_chain_multiply;
using dsa::algorithms::matrix_chain_order;
using dsa::algorithms::matrix_chain_sizes;
using dsa::algorithms::matrix_multiply;

TEST_CASE("matrix_multiply multiplies two integer matrices") {
    Matrix<int> A{
        {1, 2, 3},
        {4, 5, 6}
    };

    Matrix<int> B{
        {7, 8},
        {9, 10},
        {11, 12}
    };

    Matrix<int> expected{
        {58, 64},
        {139, 154}
    };

    REQUIRE(matrix_multiply(A, B) == expected);
}

TEST_CASE("matrix_multiply multiplies two double matrices") {
    Matrix<double> A{
        {1.5, 2.0},
        {3.0, 4.5}
    };

    Matrix<double> B{
        {2.0, 1.0},
        {0.5, 3.0}
    };

    Matrix<double> expected{
        {4.0, 7.5},
        {8.25, 16.5}
    };

    REQUIRE(matrix_multiply(A, B) == expected);
}

TEST_CASE("matrix_multiply throws when dimensions are incompatible") {
    Matrix<int> A{
        {1, 2, 3}
    };

    Matrix<int> B{
        {1, 2},
        {3, 4}
    };

    REQUIRE_THROWS_AS(matrix_multiply(A, B), std::invalid_argument);
}

TEST_CASE("matrix_multiply throws when matrix is empty") {
    Matrix<int> A{};
    Matrix<int> B{
        {1, 2},
        {3, 4}
    };

    REQUIRE_THROWS_AS(matrix_multiply(A, B), std::invalid_argument);
}

TEST_CASE("matrix_multiply throws when matrix rows have different sizes") {
    Matrix<int> A{
        {1, 2},
        {3}
    };

    Matrix<int> B{
        {1, 2},
        {3, 4}
    };

    REQUIRE_THROWS_AS(matrix_multiply(A, B), std::invalid_argument);
}

TEST_CASE("matrix_chain_sizes builds dimension vector p") {
    std::vector<Matrix<int>> matrices{
        Matrix<int>(3, std::vector<int>(4, 1)),
        Matrix<int>(4, std::vector<int>(5, 1)),
        Matrix<int>(5, std::vector<int>(10, 1)),
        Matrix<int>(10, std::vector<int>(3, 1)),
        Matrix<int>(3, std::vector<int>(2, 1))
    };

    std::vector<int> expected{3, 4, 5, 10, 3, 2};

    REQUIRE(matrix_chain_sizes(matrices) == expected);
}

TEST_CASE("matrix_chain_sizes throws when chain is empty") {
    std::vector<Matrix<int>> matrices{};

    REQUIRE_THROWS_AS(matrix_chain_sizes(matrices), std::invalid_argument);
}

TEST_CASE("matrix_chain_sizes throws when adjacent matrices are incompatible") {
    std::vector<Matrix<int>> matrices{
        Matrix<int>(3, std::vector<int>(4, 1)),
        Matrix<int>(5, std::vector<int>(2, 1))
    };

    REQUIRE_THROWS_AS(matrix_chain_sizes(matrices), std::invalid_argument);
}

TEST_CASE("matrix_chain_order computes CLRS example cost") {
    std::vector<int> p{30, 35, 15, 5, 10, 20, 25};

    auto [m, s] = matrix_chain_order(p, 6);

    REQUIRE(m[0][5] == 15125);
}

TEST_CASE("matrix_chain_order throws when p has invalid size") {
    std::vector<int> p{10, 20, 30};

    REQUIRE_THROWS_AS(matrix_chain_order(p, 5), std::invalid_argument);
}

TEST_CASE("matrix_chain_multiply multiplies a full chain optimally") {
    Matrix<int> A{
        {1, 2},
        {3, 4}
    };

    Matrix<int> B{
        {5, 6},
        {7, 8}
    };

    Matrix<int> C{
        {9, 10},
        {11, 12}
    };

    std::vector<Matrix<int>> matrices{A, B, C};

    Matrix<int> expected = matrix_multiply(matrix_multiply(A, B), C);

    REQUIRE(matrix_chain_multiply(matrices) == expected);
}

TEST_CASE("matrix_chain_multiply works with one matrix") {
    Matrix<int> A{
        {1, 2},
        {3, 4}
    };

    std::vector<Matrix<int>> matrices{A};

    REQUIRE(matrix_chain_multiply(matrices) == A);
}