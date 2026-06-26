#pragma once

#include <string>
#include <vector>

namespace dsa::algorithms {

using Matrix = std::vector<std::vector<int>>;

Matrix LCS_length(
    const std::string& X,
    const std::string& Y
);

std::string build_LCS(
    const std::string& X,
    const std::string& Y,
    const Matrix& C
);

}  // namespace dsa::algorithms