#include <catch2/catch_test_macros.hpp>

#include "data_structures/order_statistic_tree.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {

using dsa::data_structures::Node;
using dsa::data_structures::OrderStatisticTree;
using dsa::data_structures::RBTreeColor;

Node* make_node(int key) {
    return new Node{
        key,
        1,
        RBTreeColor::black,
        nullptr,
        nullptr,
        nullptr
    };
}

bool is_nil(Node* node) {
    return node != nullptr &&
           node->color == RBTreeColor::black &&
           node->left == node &&
           node->right == node &&
           node->size == 0;
}

Node* nil_of(const OrderStatisticTree& tree) {
    Node* root = tree.root();

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
    Node* node,
    Node* nil,
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

bool check_no_red_red_violation(Node* node, Node* nil) {
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

int black_height_or_negative_one(Node* node, Node* nil) {
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

bool check_all_real_node_links_are_non_null(Node* node, Node* nil) {
    if (node == nullptr || node == nil) {
        return true;
    }

    if (node->left == nullptr || node->right == nullptr || node->p == nullptr) {
        return false;
    }

    return check_all_real_node_links_are_non_null(node->left, nil) &&
           check_all_real_node_links_are_non_null(node->right, nil);
}

int subtree_size_or_negative_one(Node* node, Node* nil) {
    if (node == nullptr) {
        return -1;
    }

    if (node == nil) {
        return 0;
    }

    const int left_size = subtree_size_or_negative_one(node->left, nil);
    const int right_size = subtree_size_or_negative_one(node->right, nil);

    if (left_size == -1 || right_size == -1) {
        return -1;
    }

    const int expected_size = left_size + right_size + 1;

    if (node->size != expected_size) {
        return -1;
    }

    return expected_size;
}

void require_valid_order_statistic_tree(const OrderStatisticTree& tree) {
    Node* root = tree.root();

    REQUIRE(root != nullptr);

    Node* nil = nil_of(tree);

    REQUIRE(nil != nullptr);
    REQUIRE(nil->color == RBTreeColor::black);
    REQUIRE(nil->left == nil);
    REQUIRE(nil->right == nil);
    REQUIRE(nil->size == 0);

    if (tree.empty()) {
        REQUIRE(tree.size() == 0);
        REQUIRE(root == nil);
        return;
    }

    REQUIRE(root != nil);
    REQUIRE(root->color == RBTreeColor::black);
    REQUIRE(root->p == nil);

    REQUIRE(check_all_real_node_links_are_non_null(root, nil));

    REQUIRE(check_bst_property(
        root,
        nil,
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    ));

    REQUIRE(check_no_red_red_violation(root, nil));
    REQUIRE(black_height_or_negative_one(root, nil) != -1);

    const int root_subtree_size = subtree_size_or_negative_one(root, nil);

    REQUIRE(root_subtree_size != -1);
    REQUIRE(root_subtree_size == static_cast<int>(tree.size()));

    REQUIRE(is_sorted_non_decreasing(tree.inorder_tree_walk()));
}

OrderStatisticTree make_sample_tree() {
    OrderStatisticTree tree;

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

TEST_CASE("OrderStatisticTree starts empty with nil sentinel as root") {
    OrderStatisticTree tree;

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(is_nil(tree.root()));
    REQUIRE(tree.inorder_tree_walk().empty());

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree insert one node") {
    OrderStatisticTree tree;

    tree.insert(make_node(10));

    REQUIRE_FALSE(tree.empty());
    REQUIRE(tree.size() == 1);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(tree.root()->key == 10);
    REQUIRE(tree.root()->color == RBTreeColor::black);
    REQUIRE(tree.root()->size == 1);

    Node* nil = nil_of(tree);

    REQUIRE(tree.root()->p == nil);
    REQUIRE(tree.root()->left == nil);
    REQUIRE(tree.root()->right == nil);

    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10});

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree insert builds sorted inorder traversal") {
    OrderStatisticTree tree = make_sample_tree();

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree remains valid after increasing insertions") {
    OrderStatisticTree tree;

    for (int value = 1; value <= 50; ++value) {
        tree.insert(make_node(value));
        require_valid_order_statistic_tree(tree);
    }

    REQUIRE(tree.size() == 50);

    std::vector<int> expected;
    expected.reserve(50);

    for (int value = 1; value <= 50; ++value) {
        expected.push_back(value);
    }

    REQUIRE(tree.inorder_tree_walk() == expected);
}

TEST_CASE("OrderStatisticTree remains valid after decreasing insertions") {
    OrderStatisticTree tree;

    for (int value = 50; value >= 1; --value) {
        tree.insert(make_node(value));
        require_valid_order_statistic_tree(tree);
    }

    REQUIRE(tree.size() == 50);

    std::vector<int> expected;
    expected.reserve(50);

    for (int value = 1; value <= 50; ++value) {
        expected.push_back(value);
    }

    REQUIRE(tree.inorder_tree_walk() == expected);
}

TEST_CASE("OrderStatisticTree recursive search finds existing key") {
    OrderStatisticTree tree = make_sample_tree();

    Node* found = tree.tree_search(tree.root(), 13);

    REQUIRE(found != nil_of(tree));
    REQUIRE(found != nullptr);
    REQUIRE(found->key == 13);
}

TEST_CASE("OrderStatisticTree recursive search returns nil for missing key") {
    OrderStatisticTree tree = make_sample_tree();

    Node* found = tree.tree_search(tree.root(), 100);

    REQUIRE(found == nil_of(tree));
}

TEST_CASE("OrderStatisticTree iterative search finds existing key") {
    OrderStatisticTree tree = make_sample_tree();

    Node* found = tree.iterative_tree_search(tree.root(), 17);

    REQUIRE(found != nil_of(tree));
    REQUIRE(found != nullptr);
    REQUIRE(found->key == 17);
}

TEST_CASE("OrderStatisticTree iterative search returns nil for missing key") {
    OrderStatisticTree tree = make_sample_tree();

    Node* found = tree.iterative_tree_search(tree.root(), -1);

    REQUIRE(found == nil_of(tree));
}

TEST_CASE("OrderStatisticTree minimum returns smallest node") {
    OrderStatisticTree tree = make_sample_tree();

    Node* min = tree.minimum(tree.root());

    REQUIRE(min != nil_of(tree));
    REQUIRE(min->key == 2);
}

TEST_CASE("OrderStatisticTree maximum returns largest node") {
    OrderStatisticTree tree = make_sample_tree();

    Node* max = tree.maximum(tree.root());

    REQUIRE(max != nil_of(tree));
    REQUIRE(max->key == 20);
}

TEST_CASE("OrderStatisticTree minimum throws on nil root") {
    OrderStatisticTree tree;

    REQUIRE_THROWS_AS(tree.minimum(tree.root()), std::invalid_argument);
}

TEST_CASE("OrderStatisticTree maximum throws on nil root") {
    OrderStatisticTree tree;

    REQUIRE_THROWS_AS(tree.maximum(tree.root()), std::invalid_argument);
}

TEST_CASE("OrderStatisticTree successor works when node has right subtree") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 6);
    Node* succ = tree.successor(node);

    REQUIRE(succ != nil_of(tree));
    REQUIRE(succ->key == 7);
}

TEST_CASE("OrderStatisticTree successor works when node has no right subtree") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 13);
    Node* succ = tree.successor(node);

    REQUIRE(succ != nil_of(tree));
    REQUIRE(succ->key == 15);
}

TEST_CASE("OrderStatisticTree successor of maximum returns nil") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 20);
    Node* succ = tree.successor(node);

    REQUIRE(succ == nil_of(tree));
}

TEST_CASE("OrderStatisticTree predecessor works when node has left subtree") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 6);
    Node* pred = tree.predecessor(node);

    REQUIRE(pred != nil_of(tree));
    REQUIRE(pred->key == 4);
}

TEST_CASE("OrderStatisticTree predecessor works when node has no left subtree") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 7);
    Node* pred = tree.predecessor(node);

    REQUIRE(pred != nil_of(tree));
    REQUIRE(pred->key == 6);
}

TEST_CASE("OrderStatisticTree predecessor of minimum returns nil") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 2);
    Node* pred = tree.predecessor(node);

    REQUIRE(pred == nil_of(tree));
}

TEST_CASE("OrderStatisticTree tree_select returns each order statistic") {
    OrderStatisticTree tree = make_sample_tree();

    const std::vector<int> expected{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    };

    for (int i = 1; i <= static_cast<int>(expected.size()); ++i) {
        Node* selected = tree.tree_select(tree.root(), i);

        REQUIRE(selected != nil_of(tree));
        REQUIRE(selected->key == expected[static_cast<std::size_t>(i - 1)]);
    }

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree tree_select returns nil for invalid ranks") {
    OrderStatisticTree tree = make_sample_tree();

    REQUIRE(tree.tree_select(tree.root(), 0) == nil_of(tree));
    REQUIRE(tree.tree_select(tree.root(), -1) == nil_of(tree));
    REQUIRE(tree.tree_select(tree.root(), 12) == nil_of(tree));
    REQUIRE(tree.tree_select(nil_of(tree), 1) == nil_of(tree));
    REQUIRE(tree.tree_select(nullptr, 1) == nil_of(tree));
}

TEST_CASE("OrderStatisticTree tree_rank returns one-based rank of each node") {
    OrderStatisticTree tree = make_sample_tree();

    const std::vector<int> sorted{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    };

    for (std::size_t i = 0; i < sorted.size(); ++i) {
        Node* node = tree.tree_search(tree.root(), sorted[i]);

        REQUIRE(node != nil_of(tree));
        REQUIRE(tree.tree_rank(node) == static_cast<int>(i + 1));
    }

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree tree_rank returns zero for nullptr or nil") {
    OrderStatisticTree tree = make_sample_tree();

    REQUIRE(tree.tree_rank(nullptr) == 0);
    REQUIRE(tree.tree_rank(nil_of(tree)) == 0);
}

TEST_CASE("OrderStatisticTree insert nullptr throws") {
    OrderStatisticTree tree;

    REQUIRE_THROWS_AS(tree.insert(nullptr), std::invalid_argument);
}

TEST_CASE("OrderStatisticTree supports duplicate keys") {
    OrderStatisticTree tree;

    tree.insert(make_node(10));
    tree.insert(make_node(10));
    tree.insert(make_node(10));

    REQUIRE(tree.size() == 3);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{10, 10, 10});

    Node* first = tree.tree_select(tree.root(), 1);
    Node* second = tree.tree_select(tree.root(), 2);
    Node* third = tree.tree_select(tree.root(), 3);

    REQUIRE(first != nil_of(tree));
    REQUIRE(second != nil_of(tree));
    REQUIRE(third != nil_of(tree));

    REQUIRE(first->key == 10);
    REQUIRE(second->key == 10);
    REQUIRE(third->key == 10);

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete leaf node") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 2);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 2) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete node with one child") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 7);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 7) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete node with two children") {
    OrderStatisticTree tree = make_sample_tree();

    Node* node = tree.tree_search(tree.root(), 6);
    tree.tree_delete(node);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), 6) == nil_of(tree));
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete root node") {
    OrderStatisticTree tree = make_sample_tree();

    Node* old_root = tree.root();
    const int old_root_key = old_root->key;

    tree.tree_delete(old_root);

    REQUIRE(tree.size() == 10);
    REQUIRE(tree.tree_search(tree.root(), old_root_key) == nil_of(tree));

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete only node leaves tree empty") {
    OrderStatisticTree tree;

    tree.insert(make_node(10));

    Node* node = tree.root();
    tree.tree_delete(node);

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.root() != nullptr);
    REQUIRE(is_nil(tree.root()));
    REQUIRE(tree.inorder_tree_walk().empty());

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree delete nullptr does nothing") {
    OrderStatisticTree tree = make_sample_tree();

    tree.tree_delete(nullptr);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree remains valid after deleting many values") {
    OrderStatisticTree tree;

    for (int value = 1; value <= 40; ++value) {
        tree.insert(make_node(value));
    }

    require_valid_order_statistic_tree(tree);

    const std::vector<int> values_to_delete{
        1, 40, 20, 10, 30, 5, 35, 15, 25
    };

    for (int value : values_to_delete) {
        Node* node = tree.tree_search(tree.root(), value);

        REQUIRE(node != nil_of(tree));

        tree.tree_delete(node);

        REQUIRE(tree.tree_search(tree.root(), value) == nil_of(tree));
        require_valid_order_statistic_tree(tree);
    }
}

TEST_CASE("OrderStatisticTree select and rank remain correct after deletions") {
    OrderStatisticTree tree;

    for (int value = 1; value <= 20; ++value) {
        tree.insert(make_node(value));
    }

    const std::vector<int> values_to_delete{1, 4, 7, 10, 13, 16, 19};

    for (int value : values_to_delete) {
        Node* node = tree.tree_search(tree.root(), value);

        REQUIRE(node != nil_of(tree));

        tree.tree_delete(node);
    }

    const std::vector<int> expected{
        2, 3, 5, 6, 8, 9, 11, 12, 14, 15, 17, 18, 20
    };

    REQUIRE(tree.inorder_tree_walk() == expected);

    for (int i = 1; i <= static_cast<int>(expected.size()); ++i) {
        Node* selected = tree.tree_select(tree.root(), i);

        REQUIRE(selected != nil_of(tree));
        REQUIRE(selected->key == expected[static_cast<std::size_t>(i - 1)]);
        REQUIRE(tree.tree_rank(selected) == i);
    }

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree copy constructor performs deep copy") {
    OrderStatisticTree original = make_sample_tree();

    OrderStatisticTree copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());

    REQUIRE(copy.root() != nullptr);
    REQUIRE(original.root() != nullptr);
    REQUIRE(copy.root() != original.root());

    REQUIRE(copy.root()->p == nil_of(copy));

    Node* copied_node = copy.tree_search(copy.root(), 13);
    Node* original_node = original.tree_search(original.root(), 13);

    REQUIRE(copied_node != nil_of(copy));
    REQUIRE(original_node != nil_of(original));
    REQUIRE(copied_node != original_node);

    REQUIRE(copy.tree_rank(copied_node) == original.tree_rank(original_node));

    require_valid_order_statistic_tree(original);
    require_valid_order_statistic_tree(copy);
}

TEST_CASE("OrderStatisticTree copy assignment performs deep copy") {
    OrderStatisticTree original = make_sample_tree();

    OrderStatisticTree copy;
    copy.insert(make_node(100));
    copy.insert(make_node(200));

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk() == original.inorder_tree_walk());
    REQUIRE(copy.root() != original.root());
    REQUIRE(copy.root()->p == nil_of(copy));

    for (int i = 1; i <= static_cast<int>(copy.size()); ++i) {
        Node* selected = copy.tree_select(copy.root(), i);

        REQUIRE(selected != nil_of(copy));
        REQUIRE(copy.tree_rank(selected) == i);
    }

    require_valid_order_statistic_tree(original);
    require_valid_order_statistic_tree(copy);
}

TEST_CASE("OrderStatisticTree copy assignment handles self assignment") {
    OrderStatisticTree tree = make_sample_tree();

    tree = tree;

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}

TEST_CASE("OrderStatisticTree move constructor transfers ownership") {
    OrderStatisticTree original = make_sample_tree();
    Node* original_root = original.root();

    OrderStatisticTree moved(std::move(original));

    REQUIRE(moved.size() == 11);
    REQUIRE(moved.root() == original_root);
    REQUIRE(moved.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    REQUIRE(original.size() == 0);
    REQUIRE(original.root() == nullptr);
    REQUIRE(original.empty());

    require_valid_order_statistic_tree(moved);
}

TEST_CASE("OrderStatisticTree move assignment transfers ownership") {
    OrderStatisticTree original = make_sample_tree();
    Node* original_root = original.root();

    OrderStatisticTree moved;
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

    require_valid_order_statistic_tree(moved);
}

TEST_CASE("OrderStatisticTree move assignment handles self assignment") {
    OrderStatisticTree tree = make_sample_tree();

    tree = std::move(tree);

    REQUIRE(tree.size() == 11);
    REQUIRE(tree.inorder_tree_walk() == std::vector<int>{
        2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20
    });

    require_valid_order_statistic_tree(tree);
}