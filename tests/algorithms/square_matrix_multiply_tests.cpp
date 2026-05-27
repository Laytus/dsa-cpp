#include <catch2/catch_test_macros.hpp>

#include "algorithms/square_matrix_multiply.hpp"

TEST_CASE("square_matrix_multiply works with 1x1 matrices") {
    const dsa::algorithms::Matrix A{{2}};
    const dsa::algorithms::Matrix B{{3}};

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, B);

    REQUIRE(result == dsa::algorithms::Matrix{{6}});
}

TEST_CASE("square_matrix_multiply works with 2x2 matrices") {
    const dsa::algorithms::Matrix A{
        {1, 2},
        {3, 4}
    };

    const dsa::algorithms::Matrix B{
        {5, 6},
        {7, 8}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, B);

    const dsa::algorithms::Matrix expected{
        {19, 22},
        {43, 50}
    };

    REQUIRE(result == expected);
}

TEST_CASE("square_matrix_multiply works with 3x3 matrices") {
    const dsa::algorithms::Matrix A{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const dsa::algorithms::Matrix B{
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, B);

    const dsa::algorithms::Matrix expected{
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };

    REQUIRE(result == expected);
}

TEST_CASE("square_matrix_multiply works with the identity matrix on the right") {
    const dsa::algorithms::Matrix A{
        {4, 7, 2},
        {3, 5, 1},
        {9, 8, 6}
    };

    const dsa::algorithms::Matrix I{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, I);

    REQUIRE(result == A);
}

TEST_CASE("square_matrix_multiply works with the identity matrix on the left") {
    const dsa::algorithms::Matrix I{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    const dsa::algorithms::Matrix B{
        {4, 7, 2},
        {3, 5, 1},
        {9, 8, 6}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(I, B);

    REQUIRE(result == B);
}

TEST_CASE("square_matrix_multiply works with the zero matrix") {
    const dsa::algorithms::Matrix A{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const dsa::algorithms::Matrix Z{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, Z);

    REQUIRE(result == Z);
}

TEST_CASE("square_matrix_multiply works with negative values") {
    const dsa::algorithms::Matrix A{
        {1, -2},
        {-3, 4}
    };

    const dsa::algorithms::Matrix B{
        {-5, 6},
        {7, -8}
    };

    const dsa::algorithms::Matrix result = dsa::algorithms::square_matrix_multiply(A, B);

    const dsa::algorithms::Matrix expected{
        {-19, 22},
        {43, -50}
    };

    REQUIRE(result == expected);
}