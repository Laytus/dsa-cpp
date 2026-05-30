#include "data_structures/open_addressing_hash_table.hpp"
#include "data_structures/static_hash_chained_table.hpp"
#include "data_structures/universal_hash_chained_table.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <print>
#include <string>

#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace {

using dsa::data_structures::HashFunctionType;
using dsa::data_structures::OpenAddressingHashTable;
using dsa::data_structures::ProbingType;
using dsa::data_structures::StaticHashChainedTable;
using dsa::data_structures::UniversalHashChainedTable;

void print_check(const std::string& label, bool result) {
    std::println("{}: {}", label, result ? "PASS" : "FAIL");
}

void print_section(const std::string& title) {
    std::println("\n=== {} ===", title);
}

void stl_unordered_set_example() {
    print_section("std::unordered_set");
    
    std::unordered_set<std::size_t> keys;
    
    keys.insert(8);
    keys.insert(14);
    keys.insert(25);
    
    print_check("contains 14", keys.contains(14));
    print_check("does not contain 99", !keys.contains(99));
    
    keys.erase(14);
    
    print_check("14 removed", !keys.contains(14));

    std::println("size: {}", keys.size());
    std::println("bucket count: {}", keys.bucket_count());
    std::println("load factor: {}", keys.load_factor());
}

void stl_unordered_map_example() {
    print_section("std::unordered_map");

    std::unordered_map<std::size_t, std::string> table;
    
    table[8] = "eight";
    table[14] = "fourteen";
    table[25] = "twenty-five";

    print_check("contains key 14", table.contains(14));
    print_check("value at key 14 is fourteen", table.at(14) == "fourteen");
    
    table.erase(14);
    
    print_check("14 removed", !table.contains(14));

    std::println("size: {}", table.size());
    std::println("bucket count: {}", table.bucket_count());
    std::println("load factor: {}", table.load_factor());
}


void custom_static_chained_table_example() {
    print_section("Custom StaticHashChainedTable with division hashing");

    StaticHashChainedTable table(11, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(12);
    table.chained_hash_insert(23);

    print_check("contains 1", table.chained_hash_search(1) != nullptr);
    print_check("contains 12", table.chained_hash_search(12) != nullptr);
    print_check("contains 23", table.chained_hash_search(23) != nullptr);
    print_check("does not contain 34", table.chained_hash_search(34) == nullptr);

    table.chained_hash_delete(12);

    print_check("12 removed", table.chained_hash_search(12) == nullptr);
    print_check("1 still exists after deleting 12", table.chained_hash_search(1) != nullptr);
    print_check("23 still exists after deleting 12", table.chained_hash_search(23) != nullptr);
}

void custom_universal_chained_table_example() {
    print_section("Custom UniversalHashChainedTable");

    // h(k) = ((37k + 17) mod 101) mod 11
    UniversalHashChainedTable table(11, 101, 37, 17);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);
    table.chained_hash_insert(25);

    print_check("contains 8", table.chained_hash_search(8) != nullptr);
    print_check("contains 14", table.chained_hash_search(14) != nullptr);
    print_check("contains 25", table.chained_hash_search(25) != nullptr);
    print_check("does not contain 99", table.chained_hash_search(99) == nullptr);

    table.chained_hash_delete(14);

    print_check("14 removed", table.chained_hash_search(14) == nullptr);
}

void custom_open_addressing_linear_example() {
    print_section("Custom OpenAddressingHashTable with linear probing");

    OpenAddressingHashTable table(11, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(12);
    table.hash_insert(23);

    print_check("contains 1", table.hash_search(1) != nullptr);
    print_check("contains 12", table.hash_search(12) != nullptr);
    print_check("contains 23", table.hash_search(23) != nullptr);
    print_check("does not contain 34", table.hash_search(34) == nullptr);

    table.hash_delete(12);

    print_check("12 removed", table.hash_search(12) == nullptr);
    print_check("search continues after deleted slot", table.hash_search(23) != nullptr);
}

void custom_open_addressing_double_hashing_example() {
    print_section("Custom OpenAddressingHashTable with double hashing");

    // Capacity must be prime and greater than 2 in this implementation.
    OpenAddressingHashTable table(11, ProbingType::Double_hashing);

    table.hash_insert(1);
    table.hash_insert(12);
    table.hash_insert(23);

    print_check("contains 1", table.hash_search(1) != nullptr);
    print_check("contains 12", table.hash_search(12) != nullptr);
    print_check("contains 23", table.hash_search(23) != nullptr);
    print_check("does not contain 34", table.hash_search(34) == nullptr);

    table.hash_delete(12);

    print_check("12 removed", table.hash_search(12) == nullptr);
    print_check("search continues after deleted slot", table.hash_search(23) != nullptr);
}

void compare_set_like_behavior() {
    print_section("Behavior comparison: STL set vs custom hash tables");

    const std::vector<std::size_t> keys{1, 12, 23, 3, 14, 25};
    const std::vector<std::size_t> queries{1, 12, 23, 100};

    std::unordered_set<std::size_t> stl_set;
    StaticHashChainedTable chained_table(11, HashFunctionType::Division);
    OpenAddressingHashTable open_table(11, ProbingType::Linear_probing);

    for (const std::size_t key : keys) {
        stl_set.insert(key);
        chained_table.chained_hash_insert(key);
        open_table.hash_insert(key);
    }

    for (const std::size_t query : queries) {
        const bool stl_result = stl_set.contains(query);
        const bool chained_result = chained_table.chained_hash_search(query) != nullptr;
        const bool open_result = open_table.hash_search(query) != nullptr;

        std::println(
            "key {} -> unordered_set={}, chained={}, open_addressing={}",
            query,
            stl_result,
            chained_result,
            open_result
        );
    }
}

void simple_lookup_timing_comparison() {
    print_section("Simple lookup timing comparison");

    constexpr std::size_t capacity = 2003;
    constexpr std::size_t n = 1000;
    constexpr std::size_t repetitions = 1000;

    std::vector<std::size_t> keys;
    keys.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
        keys.push_back(i * 7 + 3);
    }

    std::unordered_set<std::size_t> stl_set;
    StaticHashChainedTable chained_table(capacity, HashFunctionType::Division);
    OpenAddressingHashTable open_table(capacity, ProbingType::Linear_probing);

    for (const std::size_t key : keys) {
        stl_set.insert(key);
        chained_table.chained_hash_insert(key);
        open_table.hash_insert(key);
    }

    auto time_stl = [&]() {
        std::size_t found = 0;
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t r = 0; r < repetitions; ++r) {
            for (const std::size_t key : keys) {
                if (stl_set.contains(key)) {
                    ++found;
                }
            }
        }

        const auto end = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::println("std::unordered_set lookup time: {} us | found={}", elapsed.count(), found);
    };

    auto time_chained = [&]() {
        std::size_t found = 0;
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t r = 0; r < repetitions; ++r) {
            for (const std::size_t key : keys) {
                if (chained_table.chained_hash_search(key) != nullptr) {
                    ++found;
                }
            }
        }

        const auto end = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::println("custom chained lookup time: {} us | found={}", elapsed.count(), found);
    };

    auto time_open = [&]() {
        std::size_t found = 0;
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t r = 0; r < repetitions; ++r) {
            for (const std::size_t key : keys) {
                if (open_table.hash_search(key) != nullptr) {
                    ++found;
                }
            }
        }

        const auto end = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::println("custom open addressing lookup time: {} us | found={}", elapsed.count(), found);
    };

    time_stl();
    time_chained();
    time_open();
}

}  // namespace

int main() {
    stl_unordered_set_example();
    stl_unordered_map_example();

    custom_static_chained_table_example();
    custom_universal_chained_table_example();
    custom_open_addressing_linear_example();
    custom_open_addressing_double_hashing_example();

    compare_set_like_behavior();
    simple_lookup_timing_comparison();
}