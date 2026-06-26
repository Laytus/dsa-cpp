#include <catch2/catch_test_macros.hpp>

#include "algorithms/longest_common_subsequence.hpp"

using dsa::algorithms::LCS_length;
using dsa::algorithms::build_LCS;

TEST_CASE("LCS_length computes CLRS example length") {
    const std::string X = "ABCBDAB";
    const std::string Y = "BDCABA";

    const auto C = LCS_length(X, Y);

    REQUIRE(C[X.size()][Y.size()] == 4);
}

TEST_CASE("build_LCS builds a valid CLRS example LCS") {
    const std::string X = "ABCBDAB";
    const std::string Y = "BDCABA";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(result.size() == 4);

    // With your tie-breaking rule >=, this implementation returns BCBA.
    REQUIRE(result == "BCBA");
}

TEST_CASE("LCS returns full string when strings are equal") {
    const std::string X = "HELLO";
    const std::string Y = "HELLO";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 5);
    REQUIRE(result == "HELLO");
}

TEST_CASE("LCS returns empty string when there is no common subsequence") {
    const std::string X = "ABC";
    const std::string Y = "DEF";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 0);
    REQUIRE(result.empty());
}

TEST_CASE("LCS handles empty first string") {
    const std::string X = "";
    const std::string Y = "ABC";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 0);
    REQUIRE(result.empty());
}

TEST_CASE("LCS handles empty second string") {
    const std::string X = "ABC";
    const std::string Y = "";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 0);
    REQUIRE(result.empty());
}

TEST_CASE("LCS handles both strings empty") {
    const std::string X = "";
    const std::string Y = "";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 0);
    REQUIRE(result.empty());
}

TEST_CASE("LCS handles repeated characters") {
    const std::string X = "AAAA";
    const std::string Y = "AA";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 2);
    REQUIRE(result == "AA");
}

TEST_CASE("LCS handles subsequence inside larger string") {
    const std::string X = "ACE";
    const std::string Y = "ABCDE";

    const auto C = LCS_length(X, Y);
    const auto result = build_LCS(X, Y, C);

    REQUIRE(C[X.size()][Y.size()] == 3);
    REQUIRE(result == "ACE");
}