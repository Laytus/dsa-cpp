#include "data_structures/open_addressing_hash_table.hpp"

#include <stdexcept>

namespace {

bool is_prime(std::size_t value) {
    if (value < 2) {
        return false;
    }

    if (value == 2) {
        return true;
    }

    if (value % 2 == 0) {
        return false;
    }

    for (std::size_t divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }

    return true;
}

std::size_t previous_prime(std::size_t value) {
    if (value <= 2) {
        throw std::invalid_argument("No prime exists below the given capacity");
    }

    for (std::size_t candidate = value - 1; candidate >= 2; --candidate) {
        if (is_prime(candidate)) {
            return candidate;
        }
    }

    throw std::invalid_argument("No prime exists below the given capacity");
}

}  // namespace

namespace dsa::data_structures {

OpenAddressingHashTable::OpenAddressingHashTable(
    std::size_t capacity,
    ProbingType type
)
    : capacity_(capacity),
      size_(0),
      probing_type_(type) {
    if (capacity_ == 0) {
        throw std::invalid_argument("Open Addressing Hash Table capacity must be greater than zero");
    }

    if (
        probing_type_ == ProbingType::Double_hashing && 
        (capacity_ <= 2 || !is_prime(capacity_))
    ) {
        throw std::invalid_argument("Double hashing requires prime capacity greater than two");
    }

    table_ = new Entry[capacity_];
}

OpenAddressingHashTable::~OpenAddressingHashTable() {
    delete[] table_;
}

OpenAddressingHashTable::OpenAddressingHashTable(const OpenAddressingHashTable& other)
    : table_(new Entry[other.capacity_]),
      capacity_(other.capacity_),
      size_(other.size_),
      probing_type_{other.probing_type_} {
    for (std::size_t i = 0; i < capacity_; ++i) {
        table_[i] = other.table_[i];
    }
}

OpenAddressingHashTable& OpenAddressingHashTable::operator=(const OpenAddressingHashTable& other) {
    if (this == &other) {
        return *this;
    }

    Entry* new_table = new Entry[other.capacity_];

    for (std::size_t i = 0; i < other.capacity_; ++i) {
        new_table[i] = other.table_[i];
    }

    delete[] table_;

    table_ = new_table;
    capacity_ = other.capacity_;
    size_ = other.size_;
    probing_type_ = other.probing_type_;

    return *this;
}

OpenAddressingHashTable::OpenAddressingHashTable(OpenAddressingHashTable&& other) noexcept
    : table_(other.table_),
      capacity_(other.capacity_),
      size_(other.size_),
      probing_type_(other.probing_type_) {
    other.table_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.probing_type_ = ProbingType::Linear_probing;
}

OpenAddressingHashTable& OpenAddressingHashTable::operator=(OpenAddressingHashTable&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] table_;

    table_ = other.table_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    probing_type_ = other.probing_type_;

    other.table_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.probing_type_ = ProbingType::Linear_probing;

    return *this;
}

Entry* OpenAddressingHashTable::hash_search(
    const std::size_t k
) const {
    for (std::size_t i = 0; i < capacity_; ++i) {
        std::size_t q = hash_function(k, i);

        if (table_[q].state == SlotState::Empty) {
            return nullptr;
        }
    
        if (
            table_[q].state == SlotState::Occupied &&
            table_[q].key == k
        ) {
            return &table_[q];
        }
    }

    return nullptr;
}

std::size_t OpenAddressingHashTable::hash_insert(
    std::size_t k
) {
    Entry x = Entry();
    x.key = k;
    x.data = static_cast<int>(k);

    if (hash_search(k) != nullptr) {
        throw std::invalid_argument("Key already inserted in hash table");
    }

    return table_insert(x);
}
void OpenAddressingHashTable::hash_delete(
    std::size_t k
) {
    Entry* x = hash_search(k);
    
    if (x != nullptr) {
        if (x->state == SlotState::Occupied) {
            x->state = SlotState::Deleted;
            --size_;
        }
    }
}

std::size_t OpenAddressingHashTable::capacity() const {
    return capacity_;
}

std::size_t OpenAddressingHashTable::size() const {
    return size_;
}
    
std::size_t OpenAddressingHashTable::table_insert(
    Entry x
) {
    for (std::size_t i = 0; i < capacity_; ++i) {
        std::size_t q = hash_function(x.key, i);

        if (table_[q].state != SlotState::Occupied) {
            table_[q] = x;
            table_[q].state = SlotState::Occupied;
            ++size_;
            return q;
        }
    }

    throw std::overflow_error("Hash table overflow");
}

std::size_t OpenAddressingHashTable::linear_probing(
    std::size_t k,
    std::size_t i
) const {
    std::size_t h1 = k % capacity_;
    
    return (h1 + i) % capacity_;
}

std::size_t OpenAddressingHashTable::double_hashing(
    std::size_t k,
    std::size_t i
) const {
    const std::size_t h1 = k % capacity_;

    const std::size_t smaller_prime = previous_prime(capacity_);
    // const std::size_t h2 = smaller_prime - (k % smaller_prime);
    const std::size_t h2 = 1 + (k % smaller_prime);

    return (h1 + i * h2) % capacity_;
}

std::size_t OpenAddressingHashTable::hash_function(
    std::size_t k,
    std::size_t i
) const {
    switch (probing_type_)
    {
    case ProbingType::Linear_probing:
        return linear_probing(k, i);

    case ProbingType::Double_hashing:
        return double_hashing(k, i);
    }

    throw std::invalid_argument("Unknown probing type");
}

}  // namespace dsa::data_structures