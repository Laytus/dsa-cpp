#include "data_structures/interval_tree.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace dsa::data_structures {

IntervalTree::IntervalTree()
    : nil_(new IntervalTreeNode{
          Interval{0, std::numeric_limits<int>::min()},
          0,
          std::numeric_limits<int>::min(),
          IntervalTreeColor::black,
          nullptr,
          nullptr,
          nullptr
      }),
      root_(nil_),
      size_(0) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;
}

IntervalTree::~IntervalTree() {
    clear(root_);
    delete nil_;
    size_ = 0;
}

IntervalTree::IntervalTree(const IntervalTree& other)
    : nil_(new IntervalTreeNode{
          Interval{0, std::numeric_limits<int>::min()},
          0,
          std::numeric_limits<int>::min(),
          IntervalTreeColor::black,
          nullptr,
          nullptr,
          nullptr
      }),
      root_(nil_),
      size_(other.size_) {
    nil_->p = nil_;
    nil_->left = nil_;
    nil_->right = nil_;

    root_ = clone_subtree(other.root_, other.nil_, nil_);
}

IntervalTree& IntervalTree::operator=(const IntervalTree& other) {
    if (this == &other) {
        return *this;
    }

    clear(root_);

    root_ = clone_subtree(other.root_, other.nil_, nil_);
    size_ = other.size_;

    return *this;
}

IntervalTree::IntervalTree(IntervalTree&& other) noexcept
    : nil_(other.nil_),
      root_(other.root_),
      size_(other.size_) {
    other.nil_ = nullptr;
    other.root_ = nullptr;
    other.size_ = 0;
}

IntervalTree& IntervalTree::operator=(IntervalTree&& other) noexcept {
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

std::vector<Interval> IntervalTree::inorder_tree_walk() const {
    std::vector<Interval> output;
    output.reserve(size_);

    inorder_tree_walk(root_, output);

    return output;
}

void IntervalTree::inorder_tree_walk(
    IntervalTreeNode* x,
    std::vector<Interval>& output
) const {
    if (x == nullptr || x == nil_) {
        return;
    }

    inorder_tree_walk(x->left, output);
    output.push_back(x->interval);
    inorder_tree_walk(x->right, output);
}

IntervalTreeNode* IntervalTree::tree_search(IntervalTreeNode* x, int k) const {
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

IntervalTreeNode* IntervalTree::iterative_tree_search(
    IntervalTreeNode* x,
    int k
) const {
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

IntervalTreeNode* IntervalTree::minimum(IntervalTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Interval Tree cannot be empty");
    }

    while (x->left != nil_) {
        x = x->left;
    }

    return x;
}

IntervalTreeNode* IntervalTree::maximum(IntervalTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Interval Tree cannot be empty");
    }

    while (x->right != nil_) {
        x = x->right;
    }

    return x;
}

IntervalTreeNode* IntervalTree::successor(IntervalTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Interval Tree cannot be empty");
    }

    if (x->right != nil_) {
        return minimum(x->right);
    }

    IntervalTreeNode* y = x->p;

    while (y != nil_ && x == y->right) {
        x = y;
        y = y->p;
    }

    return y;
}

IntervalTreeNode* IntervalTree::predecessor(IntervalTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        throw std::invalid_argument("Interval Tree cannot be empty");
    }

    if (x->left != nil_) {
        return maximum(x->left);
    }

    IntervalTreeNode* y = x->p;

    while (y != nil_ && x == y->left) {
        x = y;
        y = y->p;
    }

    return y;
}

void IntervalTree::left_rotate(IntervalTreeNode* x) {
    IntervalTreeNode* y = x->right;
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

    y->max = x->max;
    recompute_max(x);
}

void IntervalTree::right_rotate(IntervalTreeNode* x) {
    IntervalTreeNode* y = x->left;
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

    y->max = x->max;
    recompute_max(x);
}

void IntervalTree::insert_fixup(IntervalTreeNode* z) {
    while (z->p->color == IntervalTreeColor::red) {
        if (z->p == z->p->p->left) {
            IntervalTreeNode* y = z->p->p->right;

            if (y->color == IntervalTreeColor::red) {
                z->p->color = IntervalTreeColor::black;
                y->color = IntervalTreeColor::black;
                z->p->p->color = IntervalTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(z);
                }

                z->p->color = IntervalTreeColor::black;
                z->p->p->color = IntervalTreeColor::red;
                right_rotate(z->p->p);
            }
        } else {
            IntervalTreeNode* y = z->p->p->left;

            if (y->color == IntervalTreeColor::red) {
                z->p->color = IntervalTreeColor::black;
                y->color = IntervalTreeColor::black;
                z->p->p->color = IntervalTreeColor::red;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(z);
                }

                z->p->color = IntervalTreeColor::black;
                z->p->p->color = IntervalTreeColor::red;
                left_rotate(z->p->p);
            }
        }
    }

    root_->color = IntervalTreeColor::black;
}

void IntervalTree::insert(IntervalTreeNode* z) {
    if (z == nullptr || z == nil_) {
        throw std::invalid_argument("Node cannot be null");
    }

    if (z->interval.low > z->interval.high) {
        throw std::invalid_argument("Interval low cannot be greater than high");
    }

    z->key = z->interval.low;
    z->max = z->interval.high;
    z->left = nil_;
    z->right = nil_;
    z->p = nil_;

    IntervalTreeNode* x = root_;
    IntervalTreeNode* y = nil_;

    while (x != nil_) {
        y = x;
        x->max = std::max(x->max, z->max);

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
    z->color = IntervalTreeColor::red;
    z->max = z->interval.high;

    ++size_;

    insert_fixup(z);
}

void IntervalTree::transplant(IntervalTreeNode* u, IntervalTreeNode* v) {
    if (u->p == nil_) {
        root_ = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }

    v->p = u->p;
}

void IntervalTree::tree_delete(IntervalTreeNode* z) {
    if (z == nullptr || z == nil_) {
        return;
    }

    IntervalTreeNode* y = z;
    IntervalTreeNode* x = nil_;
    IntervalTreeNode* max_fix_start = nil_;

    IntervalTreeColor y_original_color = y->color;

    if (z->left == nil_) {
        x = z->right;
        max_fix_start = z->p;

        transplant(z, z->right);
    } else if (z->right == nil_) {
        x = z->left;
        max_fix_start = z->p;

        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->p == z) {
            x->p = y;
            max_fix_start = y;
        } else {
            IntervalTreeNode* old_y_p = y->p;

            transplant(y, y->right);

            y->right = z->right;
            y->right->p = y;

            max_fix_start = old_y_p;
        }

        transplant(z, y);

        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    recompute_max_upward(max_fix_start);

    if (size_ > 0) {
        --size_;
    }

    if (y_original_color == IntervalTreeColor::black) {
        tree_delete_fixup(x);
    }

    delete z;
}

void IntervalTree::tree_delete_fixup(IntervalTreeNode* x) {
    IntervalTreeNode* w;

    while (x != root_ && x->color == IntervalTreeColor::black) {
        if (x == x->p->left) {
            w = x->p->right;

            if (w->color == IntervalTreeColor::red) {
                w->color = IntervalTreeColor::black;
                x->p->color = IntervalTreeColor::red;
                left_rotate(x->p);
                w = x->p->right;
            }

            if (w->left->color == IntervalTreeColor::black &&
                w->right->color == IntervalTreeColor::black) {
                w->color = IntervalTreeColor::red;
                x = x->p;
            } else {
                if (w->right->color == IntervalTreeColor::black) {
                    w->left->color = IntervalTreeColor::black;
                    w->color = IntervalTreeColor::red;
                    right_rotate(w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = IntervalTreeColor::black;
                w->right->color = IntervalTreeColor::black;
                left_rotate(x->p);
                x = root_;
            }
        } else {
            w = x->p->left;

            if (w->color == IntervalTreeColor::red) {
                w->color = IntervalTreeColor::black;
                x->p->color = IntervalTreeColor::red;
                right_rotate(x->p);
                w = x->p->left;
            }

            if (w->right->color == IntervalTreeColor::black &&
                w->left->color == IntervalTreeColor::black) {
                w->color = IntervalTreeColor::red;
                x = x->p;
            } else {
                if (w->left->color == IntervalTreeColor::black) {
                    w->right->color = IntervalTreeColor::black;
                    w->color = IntervalTreeColor::red;
                    left_rotate(w);
                    w = x->p->left;
                }

                w->color = x->p->color;
                x->p->color = IntervalTreeColor::black;
                w->left->color = IntervalTreeColor::black;
                right_rotate(x->p);
                x = root_;
            }
        }
    }

    x->color = IntervalTreeColor::black;
}

IntervalTreeNode* IntervalTree::interval_search(const Interval& interval) const {
    if (interval.low > interval.high) {
        throw std::invalid_argument("Interval low cannot be greater than high");
    }

    IntervalTreeNode* x = root_;

    while (x != nil_ && !overlaps(x->interval, interval)) {
        if (x->left != nil_ && x->left->max >= interval.low) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return x;
}

IntervalTreeNode* IntervalTree::root() const {
    return root_;
}

bool IntervalTree::empty() const {
    return root_ == nil_;
}

std::size_t IntervalTree::size() const {
    return size_;
}

bool IntervalTree::overlaps(const Interval& lhs, const Interval& rhs) {
    return lhs.low <= rhs.high && rhs.low <= lhs.high;
}

void IntervalTree::clear(IntervalTreeNode* x) {
    if (x == nullptr || x == nil_) {
        return;
    }

    clear(x->left);
    clear(x->right);
    delete x;
}

IntervalTreeNode* IntervalTree::clone_subtree(
    const IntervalTreeNode* x,
    const IntervalTreeNode* other_nil,
    IntervalTreeNode* p
) const {
    if (x == nullptr || x == other_nil) {
        return nil_;
    }

    IntervalTreeNode* copy = new IntervalTreeNode{
        x->interval,
        x->key,
        x->max,
        x->color,
        nil_,
        nil_,
        p
    };

    copy->left = clone_subtree(x->left, other_nil, copy);
    copy->right = clone_subtree(x->right, other_nil, copy);
    recompute_max(copy);

    return copy;
}

void IntervalTree::recompute_max(IntervalTreeNode* x) const {
    if (x == nullptr || x == nil_) {
        return;
    }

    x->max = std::max({x->interval.high, x->left->max, x->right->max});
}

void IntervalTree::recompute_max_upward(IntervalTreeNode* x) {
    while (x != nil_) {
        recompute_max(x);
        x = x->p;
    }
}

}  // namespace dsa::data_structures