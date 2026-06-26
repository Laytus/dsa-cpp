#include <catch2/catch_test_macros.hpp>

#include "data_structures/binary_search_tree.hpp"

#include <stdexcept>
#include <vector>

namespace {

using dsa::data_structures::BinarySearchTree;
using dsa::data_structures::BSTNode;

BSTNode* make_node(int key) {
    return new BSTNode{key, nullptr, nullptr, nullptr};
}

BinarySearchTree make_sample_tree() {
    BinarySearchTree tree;

    tree.insert(make_node(15));
    tree.insert(make_node(6));
    tree.insert(make_node(18));
    tree.insert(make_node(3));
    tree.insert(make_node(7));
    tree.insert(make_node(17));
    tree.insert(make_node(20));
    tree.insert(make_node(2));
    tree.insert(make_node(4));
    tree.insert(make_node(13));
    tree.insert(make_node(9));

    return tree;
}

}  // namespace

TEST_CASE("BinarySearchTree starts empty") {
    BinarySearchTree tree;

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() == nullptr);
    REQUIRE(tree.inorder_tree_walk().empty());
}

TEST_CASE("BinarySearchTree insert one node") {
    BinarySearchTree tree;

    BSTNode* node = make_node(10);
    tree.insert(node);

    REQUIRE_FALSE(tree.empty());
    REQUIRE(tree.size() == 1);
    REQUIRE(tree.root() == node);
    REQUIRE(tree.root()->key == 10);
    REQUIRE(tree.root()->p == nullptr);
    REQUIRE(tree.root()->left == nullptr);
    REQUIRE(tree.root()->right == nullptr);

    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10});
}

TEST_CASE("BinarySearchTree insert builds a valid BST") {
    BinarySearchTree tree = make_sample_tree();

    REQUIRE_FALSE(tree.empty());
    REQUIRE(tree.size() == 11);

    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree recursive search finds existing keys") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* found = tree.tree_search(tree.root(), 13);

    REQUIRE(found != nullptr);
    REQUIRE(found->key == 13);
}

TEST_CASE("BinarySearchTree recursive search returns nullptr for missing key") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* found = tree.tree_search(tree.root(), 100);

    REQUIRE(found == nullptr);
}

TEST_CASE("BinarySearchTree iterative search finds existing keys") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* found = tree.iterative_tree_search(tree.root(), 17);

    REQUIRE(found != nullptr);
    REQUIRE(found->key == 17);
}

TEST_CASE("BinarySearchTree iterative search returns nullptr for missing key") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* found = tree.iterative_tree_search(tree.root(), -1);

    REQUIRE(found == nullptr);
}

TEST_CASE("BinarySearchTree minimum returns smallest node") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* min = tree.minimum(tree.root());

    REQUIRE(min != nullptr);
    REQUIRE(min->key == 2);
}

TEST_CASE("BinarySearchTree maximum returns largest node") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* max = tree.maximum(tree.root());

    REQUIRE(max != nullptr);
    REQUIRE(max->key == 20);
}

TEST_CASE("BinarySearchTree minimum throws on nullptr") {
    BinarySearchTree tree;

    REQUIRE_THROWS_AS(tree.minimum(nullptr), std::invalid_argument);
}

TEST_CASE("BinarySearchTree maximum throws on nullptr") {
    BinarySearchTree tree;

    REQUIRE_THROWS_AS(tree.maximum(nullptr), std::invalid_argument);
}

TEST_CASE("BinarySearchTree successor works when node has right subtree") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 6);
    BSTNode* succ = tree.successor(node);

    REQUIRE(succ != nullptr);
    REQUIRE(succ->key == 7);
}

TEST_CASE("BinarySearchTree successor works when node has no right subtree") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 13);
    BSTNode* succ = tree.successor(node);

    REQUIRE(succ != nullptr);
    REQUIRE(succ->key == 15);
}

TEST_CASE("BinarySearchTree successor of maximum is nullptr") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 20);
    BSTNode* succ = tree.successor(node);

    REQUIRE(succ == nullptr);
}

TEST_CASE("BinarySearchTree predecessor works when node has left subtree") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 6);
    BSTNode* pred = tree.predecessor(node);

    REQUIRE(pred != nullptr);
    REQUIRE(pred->key == 4);
}

TEST_CASE("BinarySearchTree predecessor works when node has no left subtree") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 7);
    BSTNode* pred = tree.predecessor(node);

    REQUIRE(pred != nullptr);
    REQUIRE(pred->key == 6);
}

TEST_CASE("BinarySearchTree predecessor of minimum is nullptr") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 2);
    BSTNode* pred = tree.predecessor(node);

    REQUIRE(pred == nullptr);
}

TEST_CASE("BinarySearchTree delete leaf node") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 2);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 2) == nullptr);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree delete node with one child") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 7);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 7) == nullptr);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree delete node with two children") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* node = tree.tree_search(tree.root(), 6);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 6) == nullptr);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree delete root node") {
    BinarySearchTree tree = make_sample_tree();

    BSTNode* root = tree.root();
    REQUIRE(root->key == 15);

    tree.tree_delete(root);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 15) == nullptr);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 17, 18, 20
    });

    REQUIRE(tree.root() != nullptr);
    REQUIRE(tree.root()->p == nullptr);
}

TEST_CASE("BinarySearchTree delete only node leaves tree empty") {
    BinarySearchTree tree;

    tree.insert(make_node(10));

    BSTNode* node = tree.root();
    tree.tree_delete(node);

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() == nullptr);
    REQUIRE(tree.inorder_tree_walk().empty());
}

TEST_CASE("BinarySearchTree delete nullptr does nothing") {
    BinarySearchTree tree = make_sample_tree();

    tree.tree_delete(nullptr);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree supports duplicate keys") {
    BinarySearchTree tree;

    tree.insert(make_node(10));
    tree.insert(make_node(10));
    tree.insert(make_node(10));

    REQUIRE(tree.size() == 3);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10, 10, 10});
}

TEST_CASE("BinarySearchTree copy constructor performs deep copy") {
    BinarySearchTree original = make_sample_tree();

    BinarySearchTree copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());

    REQUIRE(copy.root() != nullptr);
    REQUIRE(original.root() != nullptr);
    REQUIRE(copy.root() != original.root());
    REQUIRE(copy.root()->p == nullptr);

    BSTNode* copied_node = copy.tree_search(copy.root(), 13);
    BSTNode* original_node = original.tree_search(original.root(), 13);

    REQUIRE(copied_node != nullptr);
    REQUIRE(original_node != nullptr);
    REQUIRE(copied_node != original_node);
}

TEST_CASE("BinarySearchTree copy assignment performs deep copy") {
    BinarySearchTree original = make_sample_tree();

    BinarySearchTree copy;
    copy.insert(make_node(100));
    copy.insert(make_node(200));

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());
    REQUIRE(copy.root() != original.root());
    REQUIRE(copy.root()->p == nullptr);
}

TEST_CASE("BinarySearchTree copy assignment handles self assignment") {
    BinarySearchTree tree = make_sample_tree();

    tree = tree;

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree move constructor transfers ownership") {
    BinarySearchTree original = make_sample_tree();
    BSTNode* original_root = original.root();

    BinarySearchTree moved(std::move(original));

    REQUIRE(moved.size() == 11);
    REQUIRE(moved.root() == original_root);
    REQUIRE(moved.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    REQUIRE(original.size() == 0);
    REQUIRE(original.root() == nullptr);
    REQUIRE(original.empty());
}

TEST_CASE("BinarySearchTree move assignment transfers ownership") {
    BinarySearchTree original = make_sample_tree();
    BSTNode* original_root = original.root();

    BinarySearchTree moved;
    moved.insert(make_node(100));
    moved.insert(make_node(200));

    moved = std::move(original);

    REQUIRE(moved.size() == 11);
    REQUIRE(moved.root() == original_root);
    REQUIRE(moved.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    REQUIRE(original.size() == 0);
    REQUIRE(original.root() == nullptr);
    REQUIRE(original.empty());
}

TEST_CASE("BinarySearchTree move assignment handles self assignment") {
    BinarySearchTree tree = make_sample_tree();

    tree = std::move(tree);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });
}

TEST_CASE("BinarySearchTree insert nullptr throws") {
    BinarySearchTree tree;

    REQUIRE_THROWS_AS(tree.insert(nullptr), std::invalid_argument);
}

TEST_CASE("BinarySearchTree successor nullptr throws") {
    BinarySearchTree tree;

    REQUIRE_THROWS_AS(tree.successor(nullptr), std::invalid_argument);
}

TEST_CASE("BinarySearchTree predecessor nullptr throws") {
    BinarySearchTree tree;

    REQUIRE_THROWS_AS(tree.predecessor(nullptr), std::invalid_argument);
}