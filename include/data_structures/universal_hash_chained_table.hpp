#pragma once

#include "data_structures/linked_list.hpp"

#include <cstddef>

namespace dsa::data_structures {

class UniversalHashChainedTable {
public:
    explicit UniversalHashChainedTable(
        std::size_t m,
        std::size_t p, // prime p > m
        std::size_t a, // 1 <= a <= p -1
        std::size_t b // 0 <= b <= p -1
    );

    ~UniversalHashChainedTable();

    UniversalHashChainedTable(const UniversalHashChainedTable& other);
    UniversalHashChainedTable& operator=(const UniversalHashChainedTable& other);
    
    UniversalHashChainedTable(UniversalHashChainedTable&& other) noexcept;
    UniversalHashChainedTable& operator=(UniversalHashChainedTable&& other) noexcept;

    Node* chained_hash_search(const std::size_t k) const;
    void chained_hash_insert(std::size_t k);
    void chained_hash_delete(std::size_t k);
    
private:
    std::size_t hash_function(std::size_t k) const;
    
    LinkedList** table_;
    std::size_t m_;
    std::size_t p_;
    std::size_t a_;
    std::size_t b_;
};

}  // namespace dsa::data_structures