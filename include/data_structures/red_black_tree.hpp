#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

enum class RBTreeColor {
    red,
    black
};

struct RBTNode {
    int key;
    RBTreeColor color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* p;
};

class RedBlackTree {
public:
    RedBlackTree();

    ~RedBlackTree();

    RedBlackTree(const RedBlackTree& other);
    RedBlackTree& operator=(const RedBlackTree& other);

    RedBlackTree(RedBlackTree&& other) noexcept;
    RedBlackTree& operator=(RedBlackTree&& other) noexcept;

    std::vector<int> inorder_tree_walk() const;
    
    RBTNode* tree_search(RBTNode* x, int k) const;
    RBTNode* iterative_tree_search(RBTNode* x, int k) const;
    
    RBTNode* minimum(RBTNode* x) const;
    RBTNode* maximum(RBTNode* x) const;
    
    RBTNode* successor(RBTNode* x) const;
    RBTNode* predecessor(RBTNode* x) const;

    void left_rotate(RBTNode* x);
    void right_rotate(RBTNode* x);
    
    void insert_fixup(RBTNode* z);
    void insert(RBTNode* z);
    
    void transplant(RBTNode* u, RBTNode* v);
    
    void tree_delete(RBTNode* z);
    void tree_delete_fixup(RBTNode* x);

    RBTNode* root() const;
    bool empty() const;
    std::size_t size() const;
    
private:
    void clear(RBTNode* x);
    RBTNode* clone_subtree(
        const RBTNode* x,
        const RBTNode* other_nil,
        RBTNode* p
    ) const;
    void inorder_tree_walk(RBTNode* x, std::vector<int>& output) const;

    RBTNode* nil_;
    RBTNode* root_;
    std::size_t size_;
};

}  // namespace dsa::data_structures