#include "data_structures/static_hash_chained_table.hpp"

#include <stdexcept>
#include <cmath>
#include <limits>
#include <cstdint>
#include <bit>

namespace dsa::data_structures {

StaticHashChainedTable::StaticHashChainedTable(
    std::size_t capacity,
    HashFunctionType hash_type
)
    : table_(nullptr),
      capacity_(capacity),
      multiplier_(11400714819323198485ull),
      hash_type_(hash_type) {
    if (
        hash_type_ != HashFunctionType::Division &&
        !std::has_single_bit(capacity_)
    ) {
        throw std::invalid_argument(
            "Multiplication-based hash functions require capacity to be a power of two"
        );
    }

    if (capacity_ == 0) {
        throw std::invalid_argument("Direct Access Table capacity must be greater than zero");
    }

    table_ = new LinkedList*[capacity_];

    for (std::size_t i = 0; i < capacity_; ++i) {
        table_[i] = nullptr;
    }
}

StaticHashChainedTable::~StaticHashChainedTable() {
    for (std::size_t i = 0; i < capacity_; ++i) {
        delete table_[i];
    }

    delete[] table_;
}

StaticHashChainedTable::StaticHashChainedTable(const StaticHashChainedTable& other)
    : table_(new LinkedList*[other.capacity_]),
      capacity_(other.capacity_),
      multiplier_(other.multiplier_),
      hash_type_(other.hash_type_) {
    for (std::size_t i = 0; i < capacity_; ++i) {
        if (other.table_[i] == nullptr) {
            table_[i] = nullptr;
        } else {
            table_[i] = new LinkedList(*other.table_[i]);
        }
    }
}

StaticHashChainedTable& StaticHashChainedTable::operator=(const StaticHashChainedTable& other) {
    if (this == &other) {
        return *this;
    }

    LinkedList** new_table = new LinkedList*[other.capacity_];

    for (std::size_t i = 0; i < other.capacity_; ++i) {
        if (other.table_[i] == nullptr) {
            new_table[i] = nullptr;
        } else {
            new_table[i] = new LinkedList(*other.table_[i]);
        }
    }

    for (std::size_t i = 0; i < capacity_; ++i) {
        delete table_[i];
    }

    delete[] table_;

    table_ = new_table;
    capacity_ = other.capacity_;
    multiplier_ = other.multiplier_;
    hash_type_ = other.hash_type_;

    return *this;
}

StaticHashChainedTable::StaticHashChainedTable(StaticHashChainedTable&& other) noexcept
    : table_(other.table_),
      capacity_(other.capacity_),
      multiplier_(other.multiplier_),
      hash_type_(other.hash_type_) {
    other.table_ = nullptr;
    other.capacity_ = 0;
}

StaticHashChainedTable& StaticHashChainedTable::operator=(StaticHashChainedTable&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    for (std::size_t i = 0; i < capacity_; ++i) {
        delete table_[i];
    }

    delete[] table_;

    table_ = other.table_;
    capacity_ = other.capacity_;
    multiplier_ = other.multiplier_;
    hash_type_ = other.hash_type_;

    other.table_ = nullptr;
    other.capacity_ = 0;
    other.multiplier_ = 0;
    other.hash_type_ = HashFunctionType::Division;

    return *this;
}

Node* StaticHashChainedTable::chained_hash_search(
    const std::size_t k
) const {
    std::size_t hash_key = hash_function(k);

    if (hash_key >= capacity_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        return nullptr;
    }

    return linked_list->list_search(static_cast<int>(k));
}

void StaticHashChainedTable::chained_hash_insert(std::size_t k) {
    std::size_t hash_key = hash_function(k);
 
    if (hash_key >= capacity_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        linked_list = new LinkedList();
    }
    
    linked_list->push_front(static_cast<int>(k));
    
    table_[hash_key] = linked_list;
}

void StaticHashChainedTable::chained_hash_delete(std::size_t k) {
    std::size_t hash_key = hash_function(k);

    if (hash_key >= capacity_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        throw std::invalid_argument("Table slot is empty");
    }

    linked_list->remove(static_cast<int>(k));
}

std::size_t StaticHashChainedTable::division_hash(std::size_t k) const {
    return k % capacity_;
}

std::size_t StaticHashChainedTable::multiplication_hash(std::size_t k) const {
    constexpr std::size_t w = std::numeric_limits<std::uint64_t>::digits;

    if (!std::has_single_bit(capacity_)) {
        throw std::invalid_argument("Multiplication hash requires capacity to be a power of two");
    }

    const std::size_t p = static_cast<std::size_t>(std::countr_zero(capacity_));

    const double A = (std::sqrt(5.0) - 1.0) / 2.0;

    const std::uint64_t s = static_cast<std::uint64_t>(
        std::ldexp(A, static_cast<int>(w))
    );

    const std::uint64_t key = static_cast<std::uint64_t>(k);

    const __uint128_t product = static_cast<__uint128_t>(key) * static_cast<__uint128_t>(s);

    const std::uint64_t r0 = static_cast<std::uint64_t>(product);

    return r0 >> (w - p);
}

std::size_t StaticHashChainedTable::multiply_shift_hash(std::size_t k) const {
    constexpr std::size_t w = std::numeric_limits<std::uint64_t>::digits;

    if (!std::has_single_bit(capacity_)) {
        throw std::invalid_argument("Multiply-shift hash requires capacity to be a power of two");
    }

    const std::size_t p = static_cast<std::size_t>(std::countr_zero(capacity_));

    const std::uint64_t a = 11400714819323198485ull;
    const std::uint64_t key = static_cast<std::uint64_t>(k);

    const uint64_t product = a * key;

    return product >> (w - p);
}

std::size_t StaticHashChainedTable::hash_function(std::size_t k) const {
    switch (hash_type_)
    {
        case HashFunctionType::Division:
            return division_hash(k);
        
        case HashFunctionType::Multiplication:
            return multiplication_hash(k);
        
        case HashFunctionType::MultiplyShift:
            return multiply_shift_hash(k);
    }

    throw std::logic_error("Unknown hash function type");
}

}  // namespace dsa::data_structures