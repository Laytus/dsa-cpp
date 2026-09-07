#include "data_structures/direct_access_table.hpp"

#include <stdexcept>

namespace dsa::data_structures {

DirectAccessTable::DirectAccessTable(std::size_t capacity)
    : table_(nullptr),
      capacity_(capacity) {
    if (capacity_ == 0) {
        throw std::invalid_argument("Direct Access Table capacity must be greater than zero");
    }

    table_ = new Node*[capacity_];

    for (std::size_t i = 0; i < capacity_; ++i) {
        table_[i] = nullptr;
    }
}

DirectAccessTable::~DirectAccessTable() {
    delete[] table_;
}

DirectAccessTable::DirectAccessTable(const DirectAccessTable& other)
    : table_(new Node*[other.capacity_]),
      capacity_(other.capacity_) {
    for (std::size_t i = 0; i < capacity_; ++i) {
        table_[i] = other.table_[i];
    }
}

DirectAccessTable& DirectAccessTable::operator=(const DirectAccessTable& other) {
    if (this == &other) {
        return *this;
    }

    Node** new_data = new Node*[other.capacity_];

    for (std::size_t i = 0; i < other.capacity_; ++i) {
        new_data[i] = other.table_[i];
    }

    delete[] table_;

    table_ = new_data;
    capacity_ = other.capacity_;

    return *this;
}

DirectAccessTable::DirectAccessTable(DirectAccessTable&& other) noexcept
    : table_(other.table_),
      capacity_(other.capacity_) {
    other.table_ = nullptr;
    other.capacity_ = 0;
}

DirectAccessTable& DirectAccessTable::operator=(DirectAccessTable&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] table_;

    table_ = other.table_;
    capacity_ = other.capacity_;

    other.table_ = nullptr;
    other.capacity_ = 0;

    return *this;
}

Node* DirectAccessTable::direct_access_search(const std::size_t k) const {
    if (k >= capacity_) {
        throw std::out_of_range("Key is outside the table range");
    }

    return table_[k];
}

void DirectAccessTable::direct_access_insert(Node* x) {
    if (x == nullptr) {
        throw std::invalid_argument("x cannot be a null pointer");
    }
    
    if (x->key >= capacity_) {
        throw std::out_of_range("Key is outside the table range");
    }

    table_[x->key] = x;
}

void DirectAccessTable::direct_access_delete(Node* x) {
    if (x == nullptr) {
        throw std::invalid_argument("x cannot be a null pointer");
    }
    
    if (static_cast<std::size_t>(x->key) >= capacity_) {
        throw std::out_of_range("Key is outside the table range");
    }

    table_[x->key] = nullptr;
}

}  // namespace dsa::data_structures