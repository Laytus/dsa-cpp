#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

enum class OSTreeColor {
    red,
    black
};

struct OSTreeNode {
    int key;
    int size;
    OSTreeColor color;
    OSTreeNode* left;
    OSTreeNode* right;
    OSTreeNode* p;
};

class OrderStatisticTree {
public:
    OrderStatisticTree();

    ~OrderStatisticTree();

    OrderStatisticTree(const OrderStatisticTree& other);
    OrderStatisticTree& operator=(const OrderStatisticTree& other);

    OrderStatisticTree(OrderStatisticTree&& other) noexcept;
    OrderStatisticTree& operator=(OrderStatisticTree&& other) noexcept;

    std::vector<int> inorder_tree_walk() const;
    
    OSTreeNode* tree_search(OSTreeNode* x, int k) const;
    OSTreeNode* iterative_tree_search(OSTreeNode* x, int k) const;
    
    OSTreeNode* minimum(OSTreeNode* x) const;
    OSTreeNode* maximum(OSTreeNode* x) const;
    
    OSTreeNode* successor(OSTreeNode* x) const;
    OSTreeNode* predecessor(OSTreeNode* x) const;

    void left_rotate(OSTreeNode* x);
    void right_rotate(OSTreeNode* x);
    
    void insert_fixup(OSTreeNode* z);
    void insert(OSTreeNode* z);
    
    void transplant(OSTreeNode* u, OSTreeNode* v);
    
    void tree_delete(OSTreeNode* z);
    void tree_delete_fixup(OSTreeNode* x);

    OSTreeNode* tree_select(OSTreeNode* x, int i) const;
    int tree_rank(OSTreeNode* x) const;

    OSTreeNode* root() const;
    bool empty() const;
    std::size_t size() const;
    
private:
    void clear(OSTreeNode* x);
    OSTreeNode* clone_subtree(
        const OSTreeNode* x,
        const OSTreeNode* other_nil,
        OSTreeNode* p
    ) const;
    void inorder_tree_walk(OSTreeNode* x, std::vector<int>& output) const;

    OSTreeNode* nil_;
    OSTreeNode* root_;
    std::size_t size_;
};

}  // namespace dsa::data_structures