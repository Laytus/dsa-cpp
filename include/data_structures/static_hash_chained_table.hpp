#pragma once

#include "data_structures/linked_list.hpp"

#include <cstddef>
#include <cstdint>

namespace dsa::data_structures {

enum class HashFunctionType {
    Division,
    Multiplication,
    MultiplyShift
};

class StaticHashChainedTable {
public:
    explicit StaticHashChainedTable(
        std::size_t capacity,
        HashFunctionType type
    );

    ~StaticHashChainedTable();

    StaticHashChainedTable(const StaticHashChainedTable& other);
    StaticHashChainedTable& operator=(const StaticHashChainedTable& other);
    
    StaticHashChainedTable(StaticHashChainedTable&& other) noexcept;
    StaticHashChainedTable& operator=(StaticHashChainedTable&& other) noexcept;

    Node* chained_hash_search(const std::size_t k) const;
    void chained_hash_insert(std::size_t k);
    void chained_hash_delete(std::size_t k);
    
private:
    std::size_t division_hash(std::size_t k) const;
    std::size_t multiplication_hash(std::size_t k) const;
    std::size_t multiply_shift_hash(std::size_t k) const;
    std::size_t hash_function(std::size_t k) const;
    
    LinkedList** table_;
    std::size_t capacity_;
    std::uint64_t multiplier_;
    HashFunctionType hash_type_;
};

}  // namespace dsa::data_structures