#include "data_structures/interval_tree.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <limits>
#include <vector>

namespace {

using dsa::data_structures::Interval;
using dsa::data_structures::IntervalTree;
using dsa::data_structures::IntervalTreeColor;
using dsa::data_structures::IntervalTreeNode;

IntervalTreeNode* make_node(int low, int high) {
    return new IntervalTreeNode{
        Interval{low, high},
        low,
        high,
        IntervalTreeColor::black,
        nullptr,
        nullptr,
        nullptr
    };
}

IntervalTreeNode* nil_of(const IntervalTree& tree) {
    IntervalTreeNode* root = tree.root();

    if (root == nullptr) {
        return nullptr;
    }

    return root->p;
}

bool is_nil(const IntervalTree& tree, const IntervalTreeNode* node) {
    return node == nil_of(tree);
}

bool overlaps(const Interval& lhs, const Interval& rhs) {
    return lhs.low <= rhs.high && rhs.low <= lhs.high;
}

bool is_sorted_by_low(const std::vector<Interval>& intervals) {
    for (std::size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i - 1].low > intervals[i].low) {
            return false;
        }
    }

    return true;
}

std::size_t count_nodes(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr || is_nil(tree, x)) {
        return 0;
    }

    return 1 + count_nodes(tree, x->left) + count_nodes(tree, x->right);
}

bool all_children_are_valid(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr) {
        return false;
    }

    if (is_nil(tree, x)) {
        return true;
    }

    if (x->left == nullptr || x->right == nullptr || x->p == nullptr) {
        return false;
    }

    return all_children_are_valid(tree, x->left) &&
           all_children_are_valid(tree, x->right);
}

bool keys_match_interval_lows(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr || is_nil(tree, x)) {
        return true;
    }

    if (x->key != x->interval.low) {
        return false;
    }

    return keys_match_interval_lows(tree, x->left) &&
           keys_match_interval_lows(tree, x->right);
}

bool max_fields_are_valid(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr) {
        return false;
    }

    if (is_nil(tree, x)) {
        return x->max == std::numeric_limits<int>::min();
    }

    const int expected_max = std::max({
        x->interval.high,
        x->left->max,
        x->right->max
    });

    if (x->max != expected_max) {
        return false;
    }

    return max_fields_are_valid(tree, x->left) &&
           max_fields_are_valid(tree, x->right);
}

bool no_red_node_has_red_child(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr || is_nil(tree, x)) {
        return true;
    }

    if (x->color == IntervalTreeColor::red) {
        if (x->left->color == IntervalTreeColor::red ||
            x->right->color == IntervalTreeColor::red) {
            return false;
        }
    }

    return no_red_node_has_red_child(tree, x->left) &&
           no_red_node_has_red_child(tree, x->right);
}

int black_height_or_negative_one(const IntervalTree& tree, const IntervalTreeNode* x) {
    if (x == nullptr) {
        return -1;
    }

    if (is_nil(tree, x)) {
        return 1;
    }

    const int left_black_height = black_height_or_negative_one(tree, x->left);
    const int right_black_height = black_height_or_negative_one(tree, x->right);

    if (left_black_height == -1 || right_black_height == -1) {
        return -1;
    }

    if (left_black_height != right_black_height) {
        return -1;
    }

    if (x->color == IntervalTreeColor::black) {
        return left_black_height + 1;
    }

    return left_black_height;
}

bool interval_tree_is_valid(const IntervalTree& tree) {
    IntervalTreeNode* root = tree.root();
    IntervalTreeNode* nil = nil_of(tree);

    if (root == nullptr || nil == nullptr) {
        return false;
    }

    if (nil->color != IntervalTreeColor::black) {
        return false;
    }

    if (nil->max != std::numeric_limits<int>::min()) {
        return false;
    }

    if (nil->left != nil || nil->right != nil) {
        return false;
    }

    if (tree.empty()) {
        return root == nil && tree.size() == 0;
    }

    if (root->p != nil) {
        return false;
    }

    if (root->color != IntervalTreeColor::black) {
        return false;
    }

    if (!all_children_are_valid(tree, root)) {
        return false;
    }

    if (!keys_match_interval_lows(tree, root)) {
        return false;
    }

    if (!max_fields_are_valid(tree, root)) {
        return false;
    }

    if (!no_red_node_has_red_child(tree, root)) {
        return false;
    }

    if (black_height_or_negative_one(tree, root) == -1) {
        return false;
    }

    if (count_nodes(tree, root) != tree.size()) {
        return false;
    }

    return is_sorted_by_low(tree.inorder_tree_walk());
}

void insert_clrs_intervals(IntervalTree& tree) {
    const std::vector<Interval> intervals{
        {16, 21},
        {8, 9},
        {25, 30},
        {5, 8},
        {15, 23},
        {17, 19},
        {26, 26},
        {0, 3},
        {6, 10},
        {19, 20}
    };

    for (const Interval& interval : intervals) {
        tree.insert(make_node(interval.low, interval.high));
    }
}

}  // namespace

TEST_CASE("IntervalTree starts empty") {
    IntervalTree tree;

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(interval_tree_is_valid(tree));

    IntervalTreeNode* result = tree.interval_search(Interval{1, 2});
    REQUIRE(is_nil(tree, result));
}

TEST_CASE("IntervalTree inserts intervals and keeps inorder order") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    REQUIRE(tree.size() == 10);
    REQUIRE_FALSE(tree.empty());
    REQUIRE(interval_tree_is_valid(tree));

    const std::vector<Interval> intervals = tree.inorder_tree_walk();

    REQUIRE(intervals.size() == 10);
    REQUIRE(is_sorted_by_low(intervals));

    REQUIRE(intervals.front().low == 0);
    REQUIRE(intervals.back().low == 26);
}

TEST_CASE("IntervalTree search by low endpoint works") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    IntervalTreeNode* found = tree.tree_search(tree.root(), 15);

    REQUIRE_FALSE(is_nil(tree, found));
    REQUIRE(found->interval.low == 15);
    REQUIRE(found->interval.high == 23);

    IntervalTreeNode* missing = tree.iterative_tree_search(tree.root(), 100);

    REQUIRE(is_nil(tree, missing));
    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree minimum and maximum work") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    IntervalTreeNode* min = tree.minimum(tree.root());
    IntervalTreeNode* max = tree.maximum(tree.root());

    REQUIRE(min->interval.low == 0);
    REQUIRE(min->interval.high == 3);

    REQUIRE(max->interval.low == 26);
    REQUIRE(max->interval.high == 26);

    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree successor and predecessor work") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    IntervalTreeNode* node_15 = tree.tree_search(tree.root(), 15);
    IntervalTreeNode* successor = tree.successor(node_15);

    REQUIRE_FALSE(is_nil(tree, successor));
    REQUIRE(successor->interval.low == 16);

    IntervalTreeNode* node_16 = tree.tree_search(tree.root(), 16);
    IntervalTreeNode* predecessor = tree.predecessor(node_16);

    REQUIRE_FALSE(is_nil(tree, predecessor));
    REQUIRE(predecessor->interval.low == 15);

    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree interval_search finds an overlapping interval") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    const Interval query{22, 25};

    IntervalTreeNode* result = tree.interval_search(query);

    REQUIRE_FALSE(is_nil(tree, result));
    REQUIRE(overlaps(result->interval, query));
    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree interval_search returns nil when no interval overlaps") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    const Interval query{11, 14};

    IntervalTreeNode* result = tree.interval_search(query);

    REQUIRE(is_nil(tree, result));
    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree intervals are closed at the endpoints") {
    IntervalTree tree;

    tree.insert(make_node(10, 20));

    IntervalTreeNode* left_touch = tree.interval_search(Interval{5, 10});
    IntervalTreeNode* right_touch = tree.interval_search(Interval{20, 30});

    REQUIRE_FALSE(is_nil(tree, left_touch));
    REQUIRE_FALSE(is_nil(tree, right_touch));

    REQUIRE(overlaps(left_touch->interval, Interval{5, 10}));
    REQUIRE(overlaps(right_touch->interval, Interval{20, 30}));

    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree rejects invalid intervals") {
    IntervalTree tree;

    IntervalTreeNode* invalid = make_node(10, 5);

    REQUIRE_THROWS_AS(tree.insert(invalid), std::invalid_argument);
    delete invalid;

    REQUIRE_THROWS_AS(tree.interval_search(Interval{7, 3}), std::invalid_argument);

    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree deletes intervals and remains valid") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    tree.tree_delete(tree.tree_search(tree.root(), 0));
    REQUIRE(tree.size() == 9);
    REQUIRE(interval_tree_is_valid(tree));

    tree.tree_delete(tree.tree_search(tree.root(), 25));
    REQUIRE(tree.size() == 8);
    REQUIRE(interval_tree_is_valid(tree));

    tree.tree_delete(tree.tree_search(tree.root(), 16));
    REQUIRE(tree.size() == 7);
    REQUIRE(interval_tree_is_valid(tree));

    REQUIRE(is_nil(tree, tree.tree_search(tree.root(), 0)));
    REQUIRE(is_nil(tree, tree.tree_search(tree.root(), 25)));
    REQUIRE(is_nil(tree, tree.tree_search(tree.root(), 16)));
}

TEST_CASE("IntervalTree delete nullptr and nil are no-ops") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    const std::size_t initial_size = tree.size();

    tree.tree_delete(nullptr);
    tree.tree_delete(nil_of(tree));

    REQUIRE(tree.size() == initial_size);
    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree deletes all intervals") {
    IntervalTree tree;

    insert_clrs_intervals(tree);

    const std::vector<int> lows{
        16, 8, 25, 5, 15, 17, 26, 0, 6, 19
    };

    for (int low : lows) {
        tree.tree_delete(tree.tree_search(tree.root(), low));
        REQUIRE(interval_tree_is_valid(tree));
    }

    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0);
    REQUIRE(interval_tree_is_valid(tree));
}

TEST_CASE("IntervalTree copy constructor creates an independent copy") {
    IntervalTree original;

    insert_clrs_intervals(original);

    IntervalTree copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.inorder_tree_walk().size() == original.inorder_tree_walk().size());

    REQUIRE(interval_tree_is_valid(original));
    REQUIRE(interval_tree_is_valid(copy));

    original.tree_delete(original.tree_search(original.root(), 16));

    REQUIRE(original.size() == 9);
    REQUIRE(copy.size() == 10);

    REQUIRE(is_nil(original, original.tree_search(original.root(), 16)));
    REQUIRE_FALSE(is_nil(copy, copy.tree_search(copy.root(), 16)));

    REQUIRE(interval_tree_is_valid(original));
    REQUIRE(interval_tree_is_valid(copy));
}

TEST_CASE("IntervalTree copy assignment creates an independent copy") {
    IntervalTree original;
    IntervalTree copy;

    insert_clrs_intervals(original);

    copy.insert(make_node(100, 200));
    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(interval_tree_is_valid(original));
    REQUIRE(interval_tree_is_valid(copy));

    original.tree_delete(original.tree_search(original.root(), 8));

    REQUIRE(original.size() == 9);
    REQUIRE(copy.size() == 10);

    REQUIRE(is_nil(original, original.tree_search(original.root(), 8)));
    REQUIRE_FALSE(is_nil(copy, copy.tree_search(copy.root(), 8)));

    REQUIRE(interval_tree_is_valid(original));
    REQUIRE(interval_tree_is_valid(copy));
}

TEST_CASE("IntervalTree move constructor transfers ownership") {
    IntervalTree original;

    insert_clrs_intervals(original);

    IntervalTree moved(std::move(original));

    REQUIRE(moved.size() == 10);
    REQUIRE(interval_tree_is_valid(moved));

    REQUIRE(original.root() == nullptr);
    REQUIRE(original.size() == 0);
}

TEST_CASE("IntervalTree move assignment transfers ownership") {
    IntervalTree original;
    IntervalTree moved;

    insert_clrs_intervals(original);
    moved.insert(make_node(100, 200));

    moved = std::move(original);

    REQUIRE(moved.size() == 10);
    REQUIRE(interval_tree_is_valid(moved));

    REQUIRE(original.root() == nullptr);
    REQUIRE(original.size() == 0);
}