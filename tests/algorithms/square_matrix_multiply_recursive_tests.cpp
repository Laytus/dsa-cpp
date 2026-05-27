#include <catch2/catch_test_macros.hpp>

#include "algorithms/square_matrix_multiply_recursive.hpp"

TEST_CASE("square_matrix_multiply_recursive works with 1x1 matrices") {
    const dsa::algorithms::Matrix A{{2}};
    const dsa::algorithms::Matrix B{{3}};

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, B);

    REQUIRE(result == dsa::algorithms::Matrix{{6}});
}

TEST_CASE("square_matrix_multiply_recursive works with 2x2 matrices") {
    const dsa::algorithms::Matrix A{
        {1, 2},
        {3, 4}
    };

    const dsa::algorithms::Matrix B{
        {5, 6},
        {7, 8}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, B);

    const dsa::algorithms::Matrix expected{
        {19, 22},
        {43, 50}
    };

    REQUIRE(result == expected);
}

TEST_CASE("square_matrix_multiply_recursive works with 4x4 matrices") {
    const dsa::algorithms::Matrix A{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const dsa::algorithms::Matrix B{
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, B);

    const dsa::algorithms::Matrix expected{
        {80, 70, 60, 50},
        {240, 214, 188, 162},
        {400, 358, 316, 274},
        {560, 502, 444, 386}
    };

    REQUIRE(result == expected);
}

TEST_CASE("square_matrix_multiply_recursive works with the identity matrix on the right") {
    const dsa::algorithms::Matrix A{
        {4, 7, 2, 1},
        {3, 5, 1, 9},
        {9, 8, 6, 2},
        {1, 0, 3, 5}
    };

    const dsa::algorithms::Matrix I{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, I);

    REQUIRE(result == A);
}

TEST_CASE("square_matrix_multiply_recursive works with the identity matrix on the left") {
    const dsa::algorithms::Matrix I{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    const dsa::algorithms::Matrix B{
        {4, 7, 2, 1},
        {3, 5, 1, 9},
        {9, 8, 6, 2},
        {1, 0, 3, 5}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(I, B);

    REQUIRE(result == B);
}

TEST_CASE("square_matrix_multiply_recursive works with the zero matrix") {
    const dsa::algorithms::Matrix A{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const dsa::algorithms::Matrix Z{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, Z);

    REQUIRE(result == Z);
}

TEST_CASE("square_matrix_multiply_recursive works with negative values") {
    const dsa::algorithms::Matrix A{
        {1, -2},
        {-3, 4}
    };

    const dsa::algorithms::Matrix B{
        {-5, 6},
        {7, -8}
    };

    const dsa::algorithms::Matrix result =
        dsa::algorithms::square_matrix_multiply_recursive(A, B);

    const dsa::algorithms::Matrix expected{
        {-19, 22},
        {43, -50}
    };

    REQUIRE(result == expected);
}