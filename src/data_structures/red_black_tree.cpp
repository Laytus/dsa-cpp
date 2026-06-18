#include "data_structures/red_black_tree.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>

namespace dsa::data_structures {

RedBlackTree::RedBlackTree()
    : nil_(new RBTNode{0, RBTreeColor::black, nullptr, nullptr, nullptr}),
      root_(nil_),
      size_(0) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;
}

RedBlackTree::~RedBlackTree() {
    clear(root_);
    delete nil_;
    size_ = 0;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other)
    : nil_(new RBTNode{0, RBTreeColor::black, nullptr, nullptr, nullptr}),
      root_(nil_),
      size_(other.size_) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;

    root_ = clone_subtree(other.root_, other.nil_, nil_);
}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    if (this == &other) {
        return *this;
    }

    clear(root_);

    root_ = clone_subtree(other.root_, other.nil_, nil_);
    size_ = other.size_;

    return *this;
}

RedBlackTree::RedBlackTree(RedBlackTree&& other) noexcept
    : nil_(other.nil_),
      root_(other.root_),
      size_(other.size_) {
    other.nil_ = nullptr;
    other.root_ = nullptr;
    other.size_ = 0;
}

RedBlackTree& RedBlackTree::operator=(RedBlackTree&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear(root_);
    delete nil_;

    nil_ = other.nil_;
    root_ = other.root_;
    size_ = other.size_;
    
    other.nil_ = nullptr;
    other.root_ = nullptr;
    other.size_ = 0;

    return *this;
}

std::vector<int> RedBlackTree::inorder_tree_walk() const {
    std::vector<int> output;
    output.reserve(size_);
    
    inorder_tree_walk(root_, output);

    return output;
}

void RedBlackTree::inorder_tree_walk(RBTNode* x, std::vector<int>& output) const {
    if (x == nullptr || x == nil_) {
        return;
    }
    
    inorder_tree_walk(x->left, output);
    output.push_back(x->key);
    inorder_tree_walk(x->right, output);
}

RBTNode* RedBlackTree::tree_search(RBTNode* x, int k) const {
    if (x == nullptr || x == nil_) {
        return nil_;
    }

    if (k == x->key) {
        return x;
    }

    if (k < x->key) {
        return tree_search(x->left, k);
    }

    return tree_search(x->right, k);
}

RBTNode* RedBlackTree::iterative_tree_search(RBTNode* x, int k) const {
    if (x == nullptr) {
        return nil_;
    }

    while (x != nil_ && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x;
}

RBTNode* RedBlackTree::minimum(RBTNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Red Black Tree cannot be empty");
    }

    while (x->left != nil_) {
        x = x->left;
    }

    return x;
}


RBTNode* RedBlackTree::maximum(RBTNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Red Black Tree cannot be empty");
    }

    while (x->right != nil_) {
        x = x->right;
    }

    return x;
}

RBTNode* RedBlackTree::successor(RBTNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Red Black Tree cannot be empty");
    }

    if (x->right != nil_) {
        return minimum(x->right);
    }

    RBTNode* y = x->p;

    while (y != nil_ && x == y->right) {
        x = y;
        y = y->p;
    }

    return y;
}

RBTNode* RedBlackTree::predecessor(RBTNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Red Black Tree cannot be empty");
    }

    if (x->left != nil_) {
        return maximum(x->left);
    }

    RBTNode* y = x->p;

    while (y != nil_ && x == y->left) {
        x = y;
        y = y->p;
    }

    return y;
}

void RedBlackTree::left_rotate(RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;

    if (y->left != nil_) {
        y->left->p = x;
    }

    y->p = x->p;

    if (x->p == nil_) {
        root_ = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    
    y->left = x;
    x->p = y;
}

void RedBlackTree::right_rotate(RBTNode* x) {
    RBTNode* y = x->left;
    x->left = y->right;

    if (y->right != nil_) {
        y->right->p = x;
    }

    y->p = x->p;

    if (x->p == nil_) {
        root_ = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    
    y->right = x;
    x->p = y;
}

void RedBlackTree::insert_fixup(RBTNode* z) {
    while (z->p->color == RBTreeColor::red) {
        if (z->p == z->p->p->left) {
            RBTNode* y = z->p->p->right;
            if (y->color == RBTreeColor::red) {
                z->p->color = RBTreeColor::black;
                y->color = RBTreeColor::black;
                z->p->p->color = RBTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(z);
                }

                z->p->color = RBTreeColor::black;
                z->p->p->color = RBTreeColor::red;
                right_rotate(z->p->p);
            }
        } else {
            RBTNode* y = z->p->p->left;
            if (y->color == RBTreeColor::red) {
                z->p->color = RBTreeColor::black;
                y->color = RBTreeColor::black;
                z->p->p->color = RBTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(z);
                }

                z->p->color = RBTreeColor::black;
                z->p->p->color = RBTreeColor::red;
                left_rotate(z->p->p);
            }
        }
    }

    root_->color = RBTreeColor::black;
}

void RedBlackTree::insert(RBTNode* z) {
    if (z == nullptr || z == nil_) {
        throw std::invalid_argument("Red Black Tree cannot be empty");
    }

    z->left = nil_;
    z->right = nil_;
    z->p = nil_;

    RBTNode* x = root_;
    RBTNode* y = nil_;

    while (x != nil_) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->p = y;

    if (y == nil_) {
        root_ = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = nil_;
    z->right = nil_;
    z->color = RBTreeColor::red;

    ++size_;

    insert_fixup(z);
}

void RedBlackTree::transplant(RBTNode* u, RBTNode* v) {
    if (u->p == nil_) {
        root_ = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }

    v->p = u->p;
}
void RedBlackTree::tree_delete(RBTNode* z) {
    if (z == nullptr || z == nil_) {
        return;
    }

    RBTNode* x;
    RBTNode* y = z;
    RBTreeColor y_original_color = y->color;

    if (z->left == nil_) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil_) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        
        y_original_color = y->color;
        x = y->right;

        if (y != z->right) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        } else {
            x->p = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if (size_ > 0) {
        --size_;
    }

    if (y_original_color == RBTreeColor::black) {
        tree_delete_fixup(x);
    }

    delete z;
}

void RedBlackTree::tree_delete_fixup(RBTNode* x) {
    RBTNode* w;
    while (x != root_ && x->color == RBTreeColor::black) {
        if (x == x->p->left) {
            w = x->p->right;

            if (w->color == RBTreeColor::red) {
                w->color = RBTreeColor::black;
                x->p->color = RBTreeColor::red;
                left_rotate(x->p);
                w = x->p->right;
            }

            if (w->left->color == RBTreeColor::black && w->right->color == RBTreeColor::black) {
                w->color = RBTreeColor::red;
                x = x->p;
            } else {
                if (w->right->color == RBTreeColor::black) {
                    w->left->color = RBTreeColor::black;
                    w->color = RBTreeColor::red;
                    right_rotate(w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = RBTreeColor::black;
                w->right->color = RBTreeColor::black;
                left_rotate(x->p);
                x = root_;
            }
        } else {
            w = x->p->left;

            if (w->color == RBTreeColor::red) {
                w->color = RBTreeColor::black;
                x->p->color = RBTreeColor::red;
                right_rotate(x->p);
                w = x->p->left;
            }

            if (w->right->color == RBTreeColor::black && w->left->color == RBTreeColor::black) {
                w->color = RBTreeColor::red;
                x = x->p;
            } else {
                if (w->left->color == RBTreeColor::black) {
                    w->right->color = RBTreeColor::black;
                    w->color = RBTreeColor::red;
                    left_rotate(w);
                    w = x->p->left;
                }

                w->color = x->p->color;
                x->p->color = RBTreeColor::black;
                w->left->color = RBTreeColor::black;
                right_rotate(x->p);
                x = root_;
            }
        }
    }

    x->color = RBTreeColor::black;
}

RBTNode* RedBlackTree::root() const {
    return root_;
}

bool RedBlackTree::empty() const {
    return root_ == nil_;
}

std::size_t RedBlackTree::size() const {
    return size_;
}

void RedBlackTree::clear(RBTNode* x) {
    if (x == nullptr || x == nil_) {
        return;
    }

    clear(x->left);
    clear(x->right);
    delete x;
}

RBTNode* RedBlackTree::clone_subtree(
    const RBTNode* x,
    const RBTNode* other_nil,
    RBTNode* p
) const {
    if (x == nullptr || x == other_nil) {
        return nil_;
    }

    RBTNode* copy = new RBTNode{x->key, x->color, nil_, nil_, p};
    
    copy->left = clone_subtree(x->left, other_nil, copy);
    copy->right = clone_subtree(x->right, other_nil, copy);

    return copy;
}

}  // namespace dsa::data_structures