#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

enum class IntervalTreeColor {
    red,
    black
};

struct Interval {
    int low;
    int high;
};

struct IntervalTreeNode {
    Interval interval;
    int key; // interval.low
    int max; // maximum interval.high in this node's subtree
    IntervalTreeColor color;
    IntervalTreeNode* left;
    IntervalTreeNode* right;
    IntervalTreeNode* p;
};

class IntervalTree {
public:
    IntervalTree();

    ~IntervalTree();

    IntervalTree(const IntervalTree& other);
    IntervalTree& operator=(const IntervalTree& other);

    IntervalTree(IntervalTree&& other) noexcept;
    IntervalTree& operator=(IntervalTree&& other) noexcept;

    std::vector<Interval> inorder_tree_walk() const;
    
    IntervalTreeNode* tree_search(IntervalTreeNode* x, int k) const;
    IntervalTreeNode* iterative_tree_search(IntervalTreeNode* x, int k) const;
    
    IntervalTreeNode* minimum(IntervalTreeNode* x) const;
    IntervalTreeNode* maximum(IntervalTreeNode* x) const;
    
    IntervalTreeNode* successor(IntervalTreeNode* x) const;
    IntervalTreeNode* predecessor(IntervalTreeNode* x) const;

    void left_rotate(IntervalTreeNode* x);
    void right_rotate(IntervalTreeNode* x);
    
    void insert_fixup(IntervalTreeNode* z);
    void insert(IntervalTreeNode* z);
    
    void transplant(IntervalTreeNode* u, IntervalTreeNode* v);
    
    void tree_delete(IntervalTreeNode* z);
    void tree_delete_fixup(IntervalTreeNode* x);

    IntervalTreeNode* interval_search(const Interval& interval) const;

    IntervalTreeNode* root() const;
    bool empty() const;
    std::size_t size() const;
    
private:
    static bool overlaps(const Interval& lhs, const Interval& rhs);
    
    void clear(IntervalTreeNode* x);
    IntervalTreeNode* clone_subtree(
        const IntervalTreeNode* x,
        const IntervalTreeNode* other_nil,
        IntervalTreeNode* p
    ) const;
    void inorder_tree_walk(IntervalTreeNode* x, std::vector<Interval>& output) const;
    void recompute_max(IntervalTreeNode* x) const;
    void recompute_max_upward(IntervalTreeNode* x);

    IntervalTreeNode* nil_;
    IntervalTreeNode* root_;
    std::size_t size_;
};

}  // namespace dsa::data_structures