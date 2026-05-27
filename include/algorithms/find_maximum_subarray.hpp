#include <cstddef>
#include <tuple>
#include <vector>

namespace dsa::algorithms {

std::tuple<std::size_t, std::size_t, int> find_max_crossing_subarray(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t mid,
    std::size_t high
);

std::tuple<std::size_t, std::size_t, int> find_maximum_subarray(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t high
);

}  // namespace dsa::algorithms