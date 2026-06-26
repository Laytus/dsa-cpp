#include "algorithms/longest_common_subsequence.hpp"

namespace dsa::algorithms {

Matrix LCS_length(
    const std::string& X,
    const std::string& Y
) {
    const std::size_t m = X.size();
    const std::size_t n = Y.size();

    Matrix C(m + 1, std::vector<int>(n + 1, 0));

    for (std::size_t i = 1; i <= m; ++i) {
        for (std::size_t j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            } else if (C[i - 1][j] >= C[i][j - 1]) {
                C[i][j] = C[i - 1][j];
            } else {
                C[i][j] = C[i][j - 1];
            }
        }
    }

    return C;
}

std::string build_LCS(
    const std::string& X,
    const std::string& Y,
    const Matrix& C
) {
    std::size_t i = X.size();
    std::size_t j = Y.size();
    
    std::string result(static_cast<std::size_t>(C[i][j]), '\0');
    std::size_t index = result.size();

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result[--index] = X[i - 1];
            --i;
            --j;
        } else if (C[i - 1][j] >= C[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    return result;
}

}  // namespace dsa::algorithms