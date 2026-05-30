#pragma once

#include <cstddef>

namespace dsa::data_structures {

enum class SlotState {
    Empty,
    Occupied,
    Deleted
};

enum class ProbingType {
    Linear_probing,
    Double_hashing
};

struct Entry {
    std::size_t key{};
    int data{};
    SlotState state{SlotState::Empty};
};

class OpenAddressingHashTable {
public:
    explicit OpenAddressingHashTable(
        std::size_t capacity,
        ProbingType type
    );

    ~OpenAddressingHashTable();

    OpenAddressingHashTable(const OpenAddressingHashTable& other);
    OpenAddressingHashTable& operator=(const OpenAddressingHashTable& other);
    
    OpenAddressingHashTable(OpenAddressingHashTable&& other) noexcept;
    OpenAddressingHashTable& operator=(OpenAddressingHashTable&& other) noexcept;

    Entry* hash_search(const std::size_t k) const;
    std::size_t hash_insert(std::size_t k);
    void hash_delete(std::size_t k);

    std::size_t capacity() const;
    std::size_t size() const;
    
private:
    std::size_t table_insert(Entry x);

    std::size_t linear_probing(std::size_t k, std::size_t i) const;
    std::size_t double_hashing(std::size_t k, std::size_t i) const;
    std::size_t hash_function(std::size_t k, std::size_t i) const;

    Entry* table_;
    std::size_t capacity_;
    std::size_t size_; //?
    ProbingType probing_type_;
};

}  // namespace dsa::data_structures