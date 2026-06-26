#include <catch2/catch_test_macros.hpp>

#include "data_structures/red_black_tree.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {

using dsa::data_structures::RBTNode;
using dsa::data_structures::RBTreeColor;
using dsa::data_structures::RedBlackTree;

RBTNode* make_node(int key) {
    return new RBTNode{key, RBTreeColor::black, nullptr, nullptr, nullptr};
}

bool is_nil(RBTNode* node) {
    return node != nullptr &&
           node->color == RBTreeColor::black &&
           node->left == node &&
           node->right == node;
}

RBTNode* nil_of(const RedBlackTree& tree) {
    RBTNode* root = tree.root();

    if (root == nullptr) {
        return nullptr;
    }

    if (is_nil(root)) {
        return root;
    }

    return root->p;
}

bool is_sorted_non_decreasing(const std::vector<int>& values) {
    return std::is_sorted(values.begin(), values.end());
}

bool check_bst_property(
    RBTNode* node,
    RBTNode* nil,
    int min_value,
    int max_value
) {
    if (node == nullptr || node == nil) {
        return true;
    }

    if (node->key < min_value || node->key > max_value) {
        return false;
    }

    return check_bst_property(node->left, nil, min_value, node->key) &&
           check_bst_property(node->right, nil, node->key, max_value);
}

bool check_no_red_red_violation(RBTNode* node, RBTNode* nil) {
    if (node == nullptr || node == nil) {
        return true;
    }

    if (node->color == RBTreeColor::red) {
        if (node->left->color == RBTreeColor::red ||
            node->right->color == RBTreeColor::red) {
            return false;
        }
    }

    return check_no_red_red_violation(node->left, nil) &&
           check_no_red_red_violation(node->right, nil);
}

int black_height_or_negative_one(RBTNode* node, RBTNode* nil) {
    if (node == nullptr) {
        return -1;
    }

    if (node == nil) {
        return 1;
    }

    const int left_black_height = black_height_or_negative_one(node->left, nil);
    const int right_black_height = black_height_or_negative_one(node->right, nil);

    if (left_black_height == -1 ||
        right_black_height == -1 ||
        left_black_height != right_black_height) {
        return -1;
    }

    const int self_black = node->color == RBTreeColor::black ? 1 : 0;

    return left_black_height + self_black;
}

bool check_all_real_node_children_are_non_null(RBTNode* node, RBTNode* nil) {
    if (node == nullptr || node == nil) {
        return true;
    }

    if (node->left == nullptr || node->right == nullptr || node->p == nullptr) {
        return false;
    }

    return check_all_real_node_children_are_non_null(node->left, nil) &&
           check_all_real_node_children_are_non_null(node->right, nil);
}

void require_valid_red_black_tree(const RedBlackTree& tree) {
    RBTNode* root = tree.root();

    REQUIRE(root != nullptr);

    RBTNode* nil = nil_of(tree);

    REQUIRE(nil != nullptr);
    REQUIRE(nil->color == RBTreeColor::black);
    REQUIRE(nil->left == nil);
    REQUIRE(nil->right == nil);

    if (tree.empty()) {
        REQUIRE(tree.size() == 0);
        REQUIRE(root == nil);
        return;
    }

    REQUIRE(root != nil);
    REQUIRE(root->color == RBTreeColor::black);
    REQUIRE(root->p == nil);

    REQUIRE(check_all_real_node_children_are_non_null(root, nil));
    REQUIRE(check_bst_property(
        root,
        nil,
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    ));
    REQUIRE(check_no_red_red_violation(root, nil));
    REQUIRE(black_height_or_negative_one(root, nil) != -1);
    REQUIRE(is_sorted_non_decreasing(tree.inorder_tree_walk()));
}

RedBlackTree make_sample_tree() {
    RedBlackTree tree;

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

TEST_CASE("RedBlackTree starts empty with nil sentinel as root") {
    RedBlackTree tree;

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(is_nil(tree.root()));
    REQUIRE(tree.inorder_tree_walk().empty());

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree insert one node") {
    RedBlackTree tree;

    tree.insert(make_node(10));

    REQUIRE_FALSE(tree.empty());
    REQUIRE(tree.size() == 1);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(tree.root()->key == 10);
    REQUIRE(tree.root()->color == RBTreeColor::black);

    RBTNode* nil = nil_of(tree);

    REQUIRE(tree.root()->p == nil);
    REQUIRE(tree.root()->left == nil);
    REQUIRE(tree.root()->right == nil);

    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10});

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree insert builds sorted inorder traversal") {
    RedBlackTree tree = make_sample_tree();

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree remains valid after increasing insertions") {
    RedBlackTree tree;

    for (int value = 1; value <= 50; ++value) {
        tree.insert(make_node(value));
        require_valid_red_black_tree(tree);
    }

    REQUIRE(tree.size() == 50);

    std::vector<int> expected;
    expected.reserve(50);

    for (int value = 1; value <= 50; ++value) {
        expected.push_back(value);
    }

    REQUIRE(tree.inorder_tree_walk() == expected);
}

TEST_CASE("RedBlackTree remains valid after decreasing insertions") {
    RedBlackTree tree;

    for (int value = 50; value >= 1; --value) {
        tree.insert(make_node(value));
        require_valid_red_black_tree(tree);
    }

    REQUIRE(tree.size() == 50);

    std::vector<int> expected;
    expected.reserve(50);

    for (int value = 1; value <= 50; ++value) {
        expected.push_back(value);
    }

    REQUIRE(tree.inorder_tree_walk() == expected);
}

TEST_CASE("RedBlackTree recursive search finds existing key") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* found = tree.tree_search(tree.root(), 13);

    REQUIRE(found != nil_of(tree));
    REQUIRE(found != nullptr);
    REQUIRE(found->key == 13);
}

TEST_CASE("RedBlackTree recursive search returns nil for missing key") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* found = tree.tree_search(tree.root(), 100);

    REQUIRE(found == nil_of(tree));
}

TEST_CASE("RedBlackTree iterative search finds existing key") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* found = tree.iterative_tree_search(tree.root(), 17);

    REQUIRE(found != nil_of(tree));
    REQUIRE(found != nullptr);
    REQUIRE(found->key == 17);
}

TEST_CASE("RedBlackTree iterative search returns nil for missing key") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* found = tree.iterative_tree_search(tree.root(), -1);

    REQUIRE(found == nil_of(tree));
}

TEST_CASE("RedBlackTree minimum returns smallest node") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* min = tree.minimum(tree.root());

    REQUIRE(min != nil_of(tree));
    REQUIRE(min->key == 2);
}

TEST_CASE("RedBlackTree maximum returns largest node") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* max = tree.maximum(tree.root());

    REQUIRE(max != nil_of(tree));
    REQUIRE(max->key == 20);
}

TEST_CASE("RedBlackTree minimum throws on nil root") {
    RedBlackTree tree;

    REQUIRE_THROWS_AS(tree.minimum(tree.root()), std::invalid_argument);
}

TEST_CASE("RedBlackTree maximum throws on nil root") {
    RedBlackTree tree;

    REQUIRE_THROWS_AS(tree.maximum(tree.root()), std::invalid_argument);
}

TEST_CASE("RedBlackTree successor works when node has right subtree") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 6);
    RBTNode* succ = tree.successor(node);

    REQUIRE(succ != nil_of(tree));
    REQUIRE(succ->key == 7);
}

TEST_CASE("RedBlackTree successor works when node has no right subtree") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 13);
    RBTNode* succ = tree.successor(node);

    REQUIRE(succ != nil_of(tree));
    REQUIRE(succ->key == 15);
}

TEST_CASE("RedBlackTree successor of maximum returns nil") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 20);
    RBTNode* succ = tree.successor(node);

    REQUIRE(succ == nil_of(tree));
}

TEST_CASE("RedBlackTree predecessor works when node has left subtree") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 6);
    RBTNode* pred = tree.predecessor(node);

    REQUIRE(pred != nil_of(tree));
    REQUIRE(pred->key == 4);
}

TEST_CASE("RedBlackTree predecessor works when node has no left subtree") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 7);
    RBTNode* pred = tree.predecessor(node);

    REQUIRE(pred != nil_of(tree));
    REQUIRE(pred->key == 6);
}

TEST_CASE("RedBlackTree predecessor of minimum returns nil") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 2);
    RBTNode* pred = tree.predecessor(node);

    REQUIRE(pred == nil_of(tree));
}

TEST_CASE("RedBlackTree insert nullptr throws") {
    RedBlackTree tree;

    REQUIRE_THROWS_AS(tree.insert(nullptr), std::invalid_argument);
}

TEST_CASE("RedBlackTree supports duplicate keys") {
    RedBlackTree tree;

    tree.insert(make_node(10));
    tree.insert(make_node(10));
    tree.insert(make_node(10));

    REQUIRE(tree.size() == 3);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10, 10, 10});

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete leaf node") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 2);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 2) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete node with one child") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 7);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 7) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete node with two children") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* node = tree.tree_search(tree.root(), 6);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 6) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete root node") {
    RedBlackTree tree = make_sample_tree();

    RBTNode* old_root = tree.root();
    const int old_root_key = old_root->key;

    tree.tree_delete(old_root);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), old_root_key) == nil_of(tree));

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete only node leaves tree empty") {
    RedBlackTree tree;

    tree.insert(make_node(10));

    RBTNode* node = tree.root();
    tree.tree_delete(node);

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(is_nil(tree.root()));
    REQUIRE(tree.inorder_tree_walk().empty());

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree delete nullptr does nothing") {
    RedBlackTree tree = make_sample_tree();

    tree.tree_delete(nullptr);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree remains valid after deleting many values") {
    RedBlackTree tree;

    for (int value = 1; value <= 40; ++value) {
        tree.insert(make_node(value));
    }

    require_valid_red_black_tree(tree);

    const std::vector<int> values_to_delete{
        1, 40, 20, 10, 30, 5, 35, 15, 25
    };

    for (int value : values_to_delete) {
        RBTNode* node = tree.tree_search(tree.root(), value);

        REQUIRE(node != nil_of(tree));

        tree.tree_delete(node);

        REQUIRE(tree.tree_search(tree.root(), value) == nil_of(tree));
        require_valid_red_black_tree(tree);
    }
}

TEST_CASE("RedBlackTree copy constructor performs deep copy") {
    RedBlackTree original = make_sample_tree();

    RedBlackTree copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());

    REQUIRE(copy.root() != nullptr);
    REQUIRE(original.root() != nullptr);
    REQUIRE(copy.root() != original.root());

    REQUIRE(copy.root()->p == nil_of(copy));

    RBTNode* copied_node = copy.tree_search(copy.root(), 13);
    RBTNode* original_node = original.tree_search(original.root(), 13);

    REQUIRE(copied_node != nil_of(copy));
    REQUIRE(original_node != nil_of(original));
    REQUIRE(copied_node != original_node);

    require_valid_red_black_tree(original);
    require_valid_red_black_tree(copy);
}

TEST_CASE("RedBlackTree copy assignment performs deep copy") {
    RedBlackTree original = make_sample_tree();

    RedBlackTree copy;
    copy.insert(make_node(100));
    copy.insert(make_node(200));

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());
    REQUIRE(copy.root() != original.root());
    REQUIRE(copy.root()->p == nil_of(copy));

    require_valid_red_black_tree(original);
    require_valid_red_black_tree(copy);
}

TEST_CASE("RedBlackTree copy assignment handles self assignment") {
    RedBlackTree tree = make_sample_tree();

    tree = tree;

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}

TEST_CASE("RedBlackTree move constructor transfers ownership") {
    RedBlackTree original = make_sample_tree();
    RBTNode* original_root = original.root();

    RedBlackTree moved(std::move(original));

    REQUIRE(moved.size() == 11);
    REQUIRE(moved.root() == original_root);
    REQUIRE(moved.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    REQUIRE(original.size() == 0);
    REQUIRE(original.root() == nullptr);
    REQUIRE(original.empty());

    require_valid_red_black_tree(moved);
}

TEST_CASE("RedBlackTree move assignment transfers ownership") {
    RedBlackTree original = make_sample_tree();
    RBTNode* original_root = original.root();

    RedBlackTree moved;
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

    require_valid_red_black_tree(moved);
}

TEST_CASE("RedBlackTree move assignment handles self assignment") {
    RedBlackTree tree = make_sample_tree();

    tree = std::move(tree);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_red_black_tree(tree);
}