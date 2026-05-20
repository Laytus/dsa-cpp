#pragma once

#include <cstddef>
#include <optional>
#include <vector>

namespace dsa::algorithms {

std::optional<std::size_t> linear_search(const std::vector<int>& values, int value);

}  // namespace dsa::algorithms