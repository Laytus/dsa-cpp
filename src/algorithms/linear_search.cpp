#include "algorithms/linear_search.hpp"

namespace dsa::algorithms {

std::optional<std::size_t> linear_search(const std::vector<int>& values, int value) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] == value) {
            return i;
        }
    }

    return std::nullopt;
}

}  // namespace dsa::algorithms