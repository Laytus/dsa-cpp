#include "data_structures/universal_hash_chained_table.hpp"

#include <stdexcept>
#include <cmath>
#include <limits>
#include <cstdint>
#include <bit>

namespace dsa::data_structures {

UniversalHashChainedTable::UniversalHashChainedTable(
    std::size_t m,
    std::size_t p, // prime p > m
    std::size_t a, // 1 <= a <= p -1
    std::size_t b // 0 <= b <= p -1
)
    : table_(nullptr),
      m_(m),
      p_(p),
      a_(a),
      b_(b) {
    if (m_ == 0) {
        throw std::invalid_argument("m must be greater than zero");
    }
    
    if (p_ <= m) {
        throw std::invalid_argument("p must be greater than m");
    }
    
    if (a_ == 0 || a >= p) {
        throw std::invalid_argument("a must satisfy 1 <= a < p");
    }
    
    if (b >= p) {
        throw std::invalid_argument("a must satisfy 0 <= b < p");
    }

    table_ = new LinkedList*[m_];

    for (std::size_t i = 0; i < m_; ++i) {
        table_[i] = nullptr;
    }
}

UniversalHashChainedTable::~UniversalHashChainedTable() {
    for (std::size_t i = 0; i < m_; ++i) {
        delete table_[i];
    }

    delete[] table_;
}

UniversalHashChainedTable::UniversalHashChainedTable(const UniversalHashChainedTable& other)
    : table_(new LinkedList*[other.m_]),
      m_(other.m_),
      p_(other.p_),
      a_(other.a_),
      b_(other.b_) {
    for (std::size_t i = 0; i < m_; ++i) {
        if (other.table_[i] == nullptr) {
            table_[i] = nullptr;
        } else {
            table_[i] = new LinkedList(*other.table_[i]);
        }
    }
}

UniversalHashChainedTable& UniversalHashChainedTable::operator=(const UniversalHashChainedTable& other) {
    if (this == &other) {
        return *this;
    }

    LinkedList** new_table = new LinkedList*[other.m_];

    for (std::size_t i = 0; i < other.m_; ++i) {
        if (other.table_[i] == nullptr) {
            new_table[i] = nullptr;
        } else {
            new_table[i] = new LinkedList(*other.table_[i]);
        }
    }

    for (std::size_t i = 0; i < m_; ++i) {
        delete table_[i];
    }

    delete[] table_;

    table_ = new_table;
    m_ = other.m_;
    p_ = other.p_;
    a_ = other.a_;
    b_ = other.b_;

    return *this;
}

UniversalHashChainedTable::UniversalHashChainedTable(UniversalHashChainedTable&& other) noexcept
    : table_(other.table_),
      m_(other.m_),
      p_(other.p_),
      a_(other.a_),
      b_(other.b_) {
    other.table_ = nullptr;
    other.m_ = 0;
    other.p_ = 0;
    other.a_ = 0;
    other.b_ = 0;
}

UniversalHashChainedTable& UniversalHashChainedTable::operator=(UniversalHashChainedTable&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    for (std::size_t i = 0; i < m_; ++i) {
        delete table_[i];
    }

    delete[] table_;

    table_ = other.table_;
    m_ = other.m_;
    p_ = other.p_;
    a_ = other.a_;
    b_ = other.b_;

    other.table_ = nullptr;
    other.m_ = 0;
    other.p_ = 0;
    other.a_ = 0;
    other.b_ = 0;

    return *this;
}

Node* UniversalHashChainedTable::chained_hash_search(
    const std::size_t k
) const {
    std::size_t hash_key = hash_function(k);

    if (hash_key >= m_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        return nullptr;
    }

    return linked_list->list_search(static_cast<int>(k));
}

void UniversalHashChainedTable::chained_hash_insert(std::size_t k) {
    std::size_t hash_key = hash_function(k);
 
    if (hash_key >= m_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        linked_list = new LinkedList();
    }
    
    linked_list->push_front(static_cast<int>(k));
    
    table_[hash_key] = linked_list;
}

void UniversalHashChainedTable::chained_hash_delete(std::size_t k) {
    std::size_t hash_key = hash_function(k);

    if (hash_key >= m_) {
        throw std::out_of_range("Hash key is outside the table range");
    }

    LinkedList* linked_list = table_[hash_key];

    if (linked_list == nullptr) {
        throw std::invalid_argument("Table slot is empty");
    }

    linked_list->remove(static_cast<int>(k));
}

std::size_t UniversalHashChainedTable::hash_function(std::size_t k) const {
    const __uint128_t value = static_cast<__uint128_t>(a_) * static_cast<__uint128_t>(k) + b_;
    
    return static_cast<std::size_t>((value % p_) % m_);
}

}  // namespace dsa::data_structures