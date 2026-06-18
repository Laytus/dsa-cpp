#include "data_structures/binary_search_tree.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>

namespace dsa::data_structures {

BinarySearchTree::BinarySearchTree()
    : root_(nullptr),
      size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    clear(root_);
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : root_(nullptr),
      size_(other.size_) {
    root_ = clone_subtree(other.root_, nullptr);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this == &other) {
        return *this;
    }

    clear(root_);

    root_ = clone_subtree(other.root_, nullptr);
    size_ = other.size_;

    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(other.root_),
      size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear(root_);

    root_ = other.root_;
    size_ = other.size_;
    
    other.root_ = nullptr;
    other.size_ = 0;

    return *this;
}

std::vector<int> BinarySearchTree::inorder_tree_walk() const {
    std::vector<int> output;
    output.reserve(size_);
    
    inorder_tree_walk(root_, output);

    return output;
}

void BinarySearchTree::inorder_tree_walk(BSTNode* x, std::vector<int>& output) const {
    if (x == nullptr) {
        return;
    }
    
    inorder_tree_walk(x->left, output);
    output.push_back(x->key);
    inorder_tree_walk(x->right, output);
}

BSTNode* BinarySearchTree::tree_search(BSTNode* x, int k) {
    if (x == nullptr || k == x->key) {
        return x;
    }

    if (k < x->key) {
        return tree_search(x->left, k);
    }

    return tree_search(x->right, k);
}

BSTNode* BinarySearchTree::iterative_tree_search(BSTNode* x, int k) {
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x;
}

BSTNode* BinarySearchTree::minimum(BSTNode* x) {
    if (x == nullptr) {
        throw std::invalid_argument("BSTNode cannot be null");
    }

    while (x->left != nullptr) {
        x = x->left;
    }

    return x;
}


BSTNode* BinarySearchTree::maximum(BSTNode* x) {
    if (x == nullptr) {
        throw std::invalid_argument("BSTNode cannot be null");
    }

    while (x->right != nullptr) {
        x = x->right;
    }

    return x;
}

BSTNode* BinarySearchTree::successor(BSTNode* x) {
    if (x == nullptr) {
        throw std::invalid_argument("BSTNode cannot be full");
    }

    if (x->right != nullptr) {
        return minimum(x->right);
    }

    BSTNode* y = x->p;

    while (y != nullptr && x == y->right) {
        x = y;
        y = y->p;
    }

    return y;
}

BSTNode* BinarySearchTree::predecessor(BSTNode* x) {
    if (x == nullptr) {
        throw std::invalid_argument("BSTNode cannot be full");
    }

    if (x->left != nullptr) {
        return maximum(x->left);
    }

    BSTNode* y = x->p;

    while (y != nullptr && x == y->left) {
        x = y;
        y = y->p;
    }

    return y;
}

void BinarySearchTree::insert(BSTNode* z) {
    if (z == nullptr) {
        throw std::invalid_argument("BSTNode cannot be full");
    }

    z->left = nullptr;
    z->right = nullptr;
    z->p = nullptr;

    BSTNode* x = root_;
    BSTNode* y = nullptr;

    while (x != nullptr) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->p = y;

    if (y == nullptr) {
        root_ = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    ++size_;
}

void BinarySearchTree::transplant(BSTNode* u, BSTNode* v) {
    if (u->p == nullptr) {
        root_ = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }

    if (v != nullptr) {
        v->p = u->p;
    }
}
void BinarySearchTree::tree_delete(BSTNode* z) {
    if (z == nullptr) {
        return;
    }

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        BSTNode* y = minimum(z->right);

        if (y != z->right) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->p = y;
    }

    delete z;

    if (size_ > 0) {
        --size_;
    }
}

BSTNode* BinarySearchTree::root() const {
    return root_;
}

bool BinarySearchTree::empty() const {
    return root_ == nullptr;
}

std::size_t BinarySearchTree::size() const {
    return size_;
}

void BinarySearchTree::clear(BSTNode* x) {
    if (x == nullptr) {
        return;
    }

    clear(x->left);
    clear(x->right);
    delete x;
}

BSTNode* BinarySearchTree::clone_subtree(const BSTNode* x, BSTNode* p) {
    if (x == nullptr) {
        return nullptr;
    }

    BSTNode* copy = new BSTNode{x->key, nullptr, nullptr, p};
    
    copy->left = clone_subtree(x->left, copy);
    copy->right = clone_subtree(x->right, copy);

    return copy;
}

}  // namespace dsa::data_structures