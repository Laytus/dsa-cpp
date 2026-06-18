#include "data_structures/order_statistic_tree.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>

namespace dsa::data_structures {

OrderStatisticTree::OrderStatisticTree()
    : nil_(new OSTreeNode{0, 0, OSTreeColor::black, nullptr, nullptr, nullptr}),
      root_(nil_),
      size_(0) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;
    nil_->size = 0;
}

OrderStatisticTree::~OrderStatisticTree() {
    clear(root_);
    delete nil_;
    size_ = 0;
}

OrderStatisticTree::OrderStatisticTree(const OrderStatisticTree& other)
    : nil_(new OSTreeNode{0, 0, OSTreeColor::black, nullptr, nullptr, nullptr}),
      root_(nil_),
      size_(other.size_) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;
    nil_->size = 0;

    root_ = clone_subtree(other.root_, other.nil_, nil_);
}

OrderStatisticTree& OrderStatisticTree::operator=(const OrderStatisticTree& other) {
    if (this == &other) {
        return *this;
    }

    clear(root_);

    root_ = clone_subtree(other.root_, other.nil_, nil_);
    size_ = other.size_;

    return *this;
}

OrderStatisticTree::OrderStatisticTree(OrderStatisticTree&& other) noexcept
    : nil_(other.nil_),
      root_(other.root_),
      size_(other.size_) {
    other.nil_ = nullptr;
    other.root_ = nullptr;
    other.size_ = 0;
}

OrderStatisticTree& OrderStatisticTree::operator=(OrderStatisticTree&& other) noexcept {
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

std::vector<int> OrderStatisticTree::inorder_tree_walk() const {
    std::vector<int> output;
    output.reserve(size_);
    
    inorder_tree_walk(root_, output);

    return output;
}

void OrderStatisticTree::inorder_tree_walk(OSTreeNode* x, std::vector<int>& output) const {
    if (x == nullptr || x == nil_) {
        return;
    }
    
    inorder_tree_walk(x->left, output);
    output.push_back(x->key);
    inorder_tree_walk(x->right, output);
}

OSTreeNode* OrderStatisticTree::tree_search(OSTreeNode* x, int k) const {
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

OSTreeNode* OrderStatisticTree::iterative_tree_search(OSTreeNode* x, int k) const {
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

OSTreeNode* OrderStatisticTree::minimum(OSTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Order Statistic Tree cannot be empty");
    }

    while (x->left != nil_) {
        x = x->left;
    }

    return x;
}


OSTreeNode* OrderStatisticTree::maximum(OSTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Order Statistic Tree cannot be empty");
    }

    while (x->right != nil_) {
        x = x->right;
    }

    return x;
}

OSTreeNode* OrderStatisticTree::successor(OSTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Order Statistic Tree cannot be empty");
    }

    if (x->right != nil_) {
        return minimum(x->right);
    }

    OSTreeNode* y = x->p;

    while (y != nil_ && x == y->right) {
        x = y;
        y = y->p;
    }

    return y;
}

OSTreeNode* OrderStatisticTree::predecessor(OSTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Order Statistic Tree cannot be empty");
    }

    if (x->left != nil_) {
        return maximum(x->left);
    }

    OSTreeNode* y = x->p;

    while (y != nil_ && x == y->left) {
        x = y;
        y = y->p;
    }

    return y;
}

void OrderStatisticTree::left_rotate(OSTreeNode* x) {
    OSTreeNode* y = x->right;
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

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void OrderStatisticTree::right_rotate(OSTreeNode* x) {
    OSTreeNode* y = x->left;
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

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

void OrderStatisticTree::insert_fixup(OSTreeNode* z) {
    while (z->p->color == OSTreeColor::red) {
        if (z->p == z->p->p->left) {
            OSTreeNode* y = z->p->p->right;
            if (y->color == OSTreeColor::red) {
                z->p->color = OSTreeColor::black;
                y->color = OSTreeColor::black;
                z->p->p->color = OSTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(z);
                }

                z->p->color = OSTreeColor::black;
                z->p->p->color = OSTreeColor::red;
                right_rotate(z->p->p);
            }
        } else {
            OSTreeNode* y = z->p->p->left;
            if (y->color == OSTreeColor::red) {
                z->p->color = OSTreeColor::black;
                y->color = OSTreeColor::black;
                z->p->p->color = OSTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(z);
                }

                z->p->color = OSTreeColor::black;
                z->p->p->color = OSTreeColor::red;
                left_rotate(z->p->p);
            }
        }
    }

    root_->color = OSTreeColor::black;
}

void OrderStatisticTree::insert(OSTreeNode* z) {
    if (z == nullptr || z == nil_) {
        throw std::invalid_argument("Order Statistic Tree cannot be empty");
    }

    z->left = nil_;
    z->right = nil_;
    z->p = nil_;

    OSTreeNode* x = root_;
    OSTreeNode* y = nil_;

    while (x != nil_) {
        y = x;
        ++x->size;

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
    z->color = OSTreeColor::red;
    z->size = 1;

    ++size_;

    insert_fixup(z);
}

void OrderStatisticTree::transplant(OSTreeNode* u, OSTreeNode* v) {
    if (u->p == nil_) {
        root_ = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }

    v->p = u->p;
}
void OrderStatisticTree::tree_delete(OSTreeNode* z) {
    if (z == nullptr || z == nil_) {
        return;
    }

    OSTreeNode* y = z;
    OSTreeNode* x = nil_;
    OSTreeNode* size_fix_start = nil_;

    OSTreeColor y_original_color = y->color;

    if (z->left == nil_) {
        x = z->right;
        size_fix_start = z->p;

        transplant(z, z->right);
    } else if (z->right == nil_) {
        x = z->left;
        size_fix_start = z->p;

        transplant(z, z->left);
    } else {
        y = minimum(z->right);

        y_original_color = y->color;
        x = y->right;

        if (y->p == z) {
            x->p = y;
            size_fix_start = y;
        } else {
            OSTreeNode* old_y_p = y->p;

            transplant(y, y->right);

            y->right = z->right;
            y->right->p = y;

            size_fix_start = old_y_p;
        }

        transplant(z, y);

        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    OSTreeNode* current = size_fix_start;

    while (current != nil_) {
        current->size = current->left->size + current->right->size + 1;
        current = current->p;
    }

    if (size_ > 0) {
        --size_;
    }

    if (y_original_color == OSTreeColor::black) {
        tree_delete_fixup(x);
    }

    delete z;
}

void OrderStatisticTree::tree_delete_fixup(OSTreeNode* x) {
    OSTreeNode* w;
    while (x != root_ && x->color == OSTreeColor::black) {
        if (x == x->p->left) {
            w = x->p->right;

            if (w->color == OSTreeColor::red) {
                w->color = OSTreeColor::black;
                x->p->color = OSTreeColor::red;
                left_rotate(x->p);
                w = x->p->right;
            }

            if (w->left->color == OSTreeColor::black && w->right->color == OSTreeColor::black) {
                w->color = OSTreeColor::red;
                x = x->p;
            } else {
                if (w->right->color == OSTreeColor::black) {
                    w->left->color = OSTreeColor::black;
                    w->color = OSTreeColor::red;
                    right_rotate(w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = OSTreeColor::black;
                w->right->color = OSTreeColor::black;
                left_rotate(x->p);
                x = root_;
            }
        } else {
            w = x->p->left;

            if (w->color == OSTreeColor::red) {
                w->color = OSTreeColor::black;
                x->p->color = OSTreeColor::red;
                right_rotate(x->p);
                w = x->p->left;
            }

            if (w->right->color == OSTreeColor::black && w->left->color == OSTreeColor::black) {
                w->color = OSTreeColor::red;
                x = x->p;
            } else {
                if (w->left->color == OSTreeColor::black) {
                    w->right->color = OSTreeColor::black;
                    w->color = OSTreeColor::red;
                    left_rotate(w);
                    w = x->p->left;
                }

                w->color = x->p->color;
                x->p->color = OSTreeColor::black;
                w->left->color = OSTreeColor::black;
                right_rotate(x->p);
                x = root_;
            }
        }
    }

    x->color = OSTreeColor::black;
}

OSTreeNode* OrderStatisticTree::tree_select(OSTreeNode* x, int i) const {
    if (x == nullptr || x == nil_ || i <= 0 || i > static_cast<int>(x->size)) {
        return nil_;
    }

    const int r = static_cast<int>(x->left->size) + 1;

    if (i == r) {
        return x;
    } else if (i < r) {
        return tree_select(x->left, i);
    } else {
        return tree_select(x->right, i - r);
    }
}

int OrderStatisticTree::tree_rank(OSTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        return 0;
    }

    int r = x->left->size + 1;
    OSTreeNode* y = x;

    while (y != root_) {
        if (y == y->p->right) {
            r += y->p->left->size + 1;
        }

        y = y->p;
    }

    return r;
}

OSTreeNode* OrderStatisticTree::root() const {
    return root_;
}

bool OrderStatisticTree::empty() const {
    return root_ == nil_;
}

std::size_t OrderStatisticTree::size() const {
    return size_;
}

void OrderStatisticTree::clear(OSTreeNode* x) {
    if (x == nullptr || x == nil_) {
        return;
    }

    clear(x->left);
    clear(x->right);
    delete x;
}

OSTreeNode* OrderStatisticTree::clone_subtree(
    const OSTreeNode* x,
    const OSTreeNode* other_nil,
    OSTreeNode* p
) const {
    if (x == nullptr || x == other_nil) {
        return nil_;
    }

    OSTreeNode* copy = new OSTreeNode{x->key, x->size, x->color, nil_, nil_, p};
    
    copy->left = clone_subtree(x->left, other_nil, copy);
    copy->right = clone_subtree(x->right, other_nil, copy);
    copy->size = copy->left->size + copy->right->size + 1;

    return copy;
}

}  // namespace dsa::data_structures