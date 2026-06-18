#include "data_structures/disjoint_set_forest.hpp"

#include <stdexcept>

namespace dsa::data_structures {

DisjointSetForest::DisjointSetForest()
    : head_(nullptr),
      size_(0) {}

DisjointSetForest::~DisjointSetForest() {
    clear();
}

DisjointSetForest::DisjointSetForest(const DisjointSetForest& other)
    : head_(nullptr),
      size_(0) {
    DSFNode* current = other.head_;

    while (current != nullptr) {
        make_set(current->key);
        current = current->next;
    }
}

DisjointSetForest& DisjointSetForest::operator=(const DisjointSetForest& other) {
    if (this == &other) {
        return *this;
    }

    DisjointSetForest copy(other);

    DSFNode* temp_head = head_;
    const std::size_t temp_size = size_;

    head_ = copy.head_;
    size_ = copy.size_;

    copy.head_ = temp_head;
    copy.size_ = temp_size;

    return *this;
}

DisjointSetForest::DisjointSetForest(DisjointSetForest&& other) noexcept
    : head_(other.head_),
      size_(other.size_) {
    other.head_ = nullptr;
    other.size_ = 0;
}

DisjointSetForest& DisjointSetForest::operator=(DisjointSetForest&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    head_ = other.head_;
    size_ = other.size_;

    other.head_ = nullptr;
    other.size_ = 0;

    return *this;
}

DSFNode* DisjointSetForest::make_set(int key) {
    DSFNode* node = new DSFNode{key, nullptr, 0, nullptr};
    node->p = node;
    node->next = head_;

    head_ = node;
    ++size_;

    return node;
}

DSFNode* DisjointSetForest::find_set(DSFNode* x) {
    if (x == nullptr) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (x != x->p) {
        x->p = find_set(x->p);
    }

    return x->p;
}

void DisjointSetForest::union_sets(DSFNode* x, DSFNode* y) {
    if (x == nullptr || y == nullptr) {
        throw std::invalid_argument("Node cannot be full");
    }
    
    link(find_set(x), find_set(y));
}

bool DisjointSetForest::connected(DSFNode* x, DSFNode* y) {
    if (x == nullptr || y == nullptr) {
        throw std::invalid_argument("Node cannot be full");
    }

    return find_set(x) == find_set(y);
}

std::size_t DisjointSetForest::size() const {
    return size_;
}

void DisjointSetForest::link(DSFNode* x, DSFNode* y) {
    if (x == y) {
        return;
    }

    if (x->rank > y->rank) {
        y->p = x;
    } else {
        x->p = y;

        if (x->rank == y->rank) {
            ++y->rank;
        }
    }
}

void DisjointSetForest::clear() {
    DSFNode* current = head_;

    while (current != nullptr) {
        DSFNode* next = current->next;
        delete current;
        current = next;
    }

    head_ = nullptr;
    size_ = 0;
}

}  // namespace dsa::data_structures