#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode* p;
};

class BinarySearchTree {
public:
    BinarySearchTree();

    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);

    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    std::vector<int> inorder_tree_walk() const;
    
    BSTNode* tree_search(BSTNode* x, int k);
    BSTNode* iterative_tree_search(BSTNode* x, int k);
    
    BSTNode* minimum(BSTNode* x);
    BSTNode* maximum(BSTNode* x);
    
    BSTNode* successor(BSTNode* x);
    BSTNode* predecessor(BSTNode* x);
    
    void insert(BSTNode* z);
    
    void transplant(BSTNode* u, BSTNode* v);
    void tree_delete(BSTNode* z);

    BSTNode* root() const;
    bool empty() const;
    std::size_t size() const;
    
private:
    void clear(BSTNode* x);
    BSTNode* clone_subtree(const BSTNode* x, BSTNode* p);
    void inorder_tree_walk(BSTNode* x, std::vector<int>& output) const;

    BSTNode* root_;
    std::size_t size_;
};

}  // namespace dsa::data_structures