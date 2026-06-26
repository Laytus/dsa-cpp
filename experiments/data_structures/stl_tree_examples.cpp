#include "data_structures/binary_search_tree.hpp"
#include "data_structures/red_black_tree.hpp"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace {

using dsa::data_structures::BinarySearchTree;
using dsa::data_structures::RedBlackTree;
using dsa::data_structures::RBTreeColor;
using dsa::data_structures::BSTNode;
using dsa::data_structures::RBTNode;

BSTNode* make_bst_node(int key) {
    return new BSTNode{key, nullptr, nullptr, nullptr};
}

RBTNode* make_rb_node(int key) {
    return new RBTNode{key, RBTreeColor::black, nullptr, nullptr, nullptr};
}

void print_separator(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

void print_vector(const std::vector<int>& values) {
    for (int value : values) {
        std::cout << value << " ";
    }

    std::cout << "\n";
}

void custom_binary_search_tree_example() {
    print_separator("Custom BinarySearchTree");

    BinarySearchTree tree;

    const std::vector<int> values{
        15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9
    };

    for (int value : values) {
        tree.insert(make_bst_node(value));
    }

    std::cout << "size: " << tree.size() << "\n";

    std::cout << "inorder traversal: ";
    print_vector(tree.inorder_tree_walk());

    BSTNode* found = tree.tree_search(tree.root(), 13);

    if (found != nullptr) {
        std::cout << "search 13: found\n";
    } else {
        std::cout << "search 13: not found\n";
    }

    BSTNode* missing = tree.iterative_tree_search(tree.root(), 100);

    if (missing != nullptr) {
        std::cout << "search 100: found\n";
    } else {
        std::cout << "search 100: not found\n";
    }

    BSTNode* min = tree.minimum(tree.root());
    BSTNode* max = tree.maximum(tree.root());

    std::cout << "minimum: " << min->key << "\n";
    std::cout << "maximum: " << max->key << "\n";

    BSTNode* node_13 = tree.tree_search(tree.root(), 13);
    BSTNode* successor = tree.successor(node_13);

    if (successor != nullptr) {
        std::cout << "successor of 13: " << successor->key << "\n";
    } else {
        std::cout << "successor of 13: none\n";
    }

    BSTNode* node_7 = tree.tree_search(tree.root(), 7);
    BSTNode* predecessor = tree.predecessor(node_7);

    if (predecessor != nullptr) {
        std::cout << "predecessor of 7: " << predecessor->key << "\n";
    } else {
        std::cout << "predecessor of 7: none\n";
    }

    std::cout << "delete leaf node 2\n";
    tree.tree_delete(tree.tree_search(tree.root(), 2));

    std::cout << "after deleting 2: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "delete node with one child 7\n";
    tree.tree_delete(tree.tree_search(tree.root(), 7));

    std::cout << "after deleting 7: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "delete node with two children 6\n";
    tree.tree_delete(tree.tree_search(tree.root(), 6));

    std::cout << "after deleting 6: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "final size: " << tree.size() << "\n";
}

void custom_red_black_tree_example() {
    print_separator("Custom RedBlackTree");

    RedBlackTree tree;

    const std::vector<int> values{
        15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9
    };

    for (int value : values) {
        tree.insert(make_rb_node(value));
    }

    std::cout << "size: " << tree.size() << "\n";

    std::cout << "inorder traversal: ";
    print_vector(tree.inorder_tree_walk());

    RBTNode* found = tree.tree_search(tree.root(), 13);

    if (found != tree.root()->p) {
        std::cout << "search 13: found\n";
    } else {
        std::cout << "search 13: not found\n";
    }

    RBTNode* missing = tree.iterative_tree_search(tree.root(), 100);

    if (missing != tree.root()->p) {
        std::cout << "search 100: found\n";
    } else {
        std::cout << "search 100: not found\n";
    }

    RBTNode* min = tree.minimum(tree.root());
    RBTNode* max = tree.maximum(tree.root());

    std::cout << "minimum: " << min->key << "\n";
    std::cout << "maximum: " << max->key << "\n";

    RBTNode* node_13 = tree.tree_search(tree.root(), 13);
    RBTNode* successor = tree.successor(node_13);

    if (successor != tree.root()->p) {
        std::cout << "successor of 13: " << successor->key << "\n";
    } else {
        std::cout << "successor of 13: none\n";
    }

    RBTNode* node_7 = tree.tree_search(tree.root(), 7);
    RBTNode* predecessor = tree.predecessor(node_7);

    if (predecessor != tree.root()->p) {
        std::cout << "predecessor of 7: " << predecessor->key << "\n";
    } else {
        std::cout << "predecessor of 7: none\n";
    }

    std::cout << "delete leaf node 2\n";
    tree.tree_delete(tree.tree_search(tree.root(), 2));

    std::cout << "after deleting 2: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "delete node with one child 7\n";
    tree.tree_delete(tree.tree_search(tree.root(), 7));

    std::cout << "after deleting 7: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "delete node with two children 6\n";
    tree.tree_delete(tree.tree_search(tree.root(), 6));

    std::cout << "after deleting 6: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "final size: " << tree.size() << "\n";
}

void stl_set_example() {
    print_separator("std::set<int>");

    std::set<int> values;

    values.insert(15);
    values.insert(6);
    values.insert(18);
    values.insert(3);
    values.insert(7);
    values.insert(17);
    values.insert(20);
    values.insert(2);
    values.insert(4);
    values.insert(13);
    values.insert(9);

    std::cout << "size: " << values.size() << "\n";

    std::cout << "ordered traversal: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    if (values.contains(13)) {
        std::cout << "contains 13: true\n";
    } else {
        std::cout << "contains 13: false\n";
    }

    auto found = values.find(100);

    if (found != values.end()) {
        std::cout << "find 100: found\n";
    } else {
        std::cout << "find 100: not found\n";
    }

    std::cout << "minimum: " << *values.begin() << "\n";
    std::cout << "maximum: " << *values.rbegin() << "\n";

    auto successor = values.upper_bound(13);

    if (successor != values.end()) {
        std::cout << "successor of 13 using upper_bound: "
                  << *successor
                  << "\n";
    } else {
        std::cout << "successor of 13: none\n";
    }

    auto node_7 = values.find(7);

    if (node_7 != values.begin() && node_7 != values.end()) {
        auto predecessor = std::prev(node_7);

        std::cout << "predecessor of 7: "
                  << *predecessor
                  << "\n";
    }

    std::cout << "erase 2\n";
    values.erase(2);

    std::cout << "erase 7\n";
    values.erase(7);

    std::cout << "erase 6\n";
    values.erase(6);

    std::cout << "after erases: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "final size: " << values.size() << "\n";
}

void stl_set_duplicate_behavior_example() {
    print_separator("std::set<int> duplicate behavior");

    std::set<int> values;

    auto [it1, inserted1] = values.insert(10);
    auto [it2, inserted2] = values.insert(10);
    auto [it3, inserted3] = values.insert(10);

    std::cout << std::boolalpha;
    std::cout << "first insert 10: " << inserted1 << "\n";
    std::cout << "second insert 10: " << inserted2 << "\n";
    std::cout << "third insert 10: " << inserted3 << "\n";

    std::cout << "set size: " << values.size() << "\n";

    std::cout << "values: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

void stl_multiset_example() {
    print_separator("std::multiset<int>");

    std::multiset<int> values;

    values.insert(10);
    values.insert(10);
    values.insert(10);
    values.insert(5);
    values.insert(20);

    std::cout << "size: " << values.size() << "\n";

    std::cout << "ordered traversal: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "count of 10: " << values.count(10) << "\n";

    auto one_ten = values.find(10);

    if (one_ten != values.end()) {
        values.erase(one_ten);
    }

    std::cout << "after erasing one 10: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    values.erase(10);

    std::cout << "after erasing all 10s: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

void stl_map_example() {
    print_separator("std::map<int, std::string>");

    std::map<int, std::string> values;

    values.emplace(15, "fifteen");
    values.emplace(6, "six");
    values.emplace(18, "eighteen");
    values.emplace(3, "three");
    values.emplace(7, "seven");
    values.emplace(17, "seventeen");
    values.emplace(20, "twenty");
    values.emplace(2, "two");
    values.emplace(4, "four");
    values.emplace(13, "thirteen");
    values.emplace(9, "nine");

    std::cout << "size: " << values.size() << "\n";

    std::cout << "ordered traversal by key:\n";
    for (const auto& [key, value] : values) {
        std::cout << key << " -> " << value << "\n";
    }

    auto found = values.find(13);

    if (found != values.end()) {
        std::cout << "find 13: "
                  << found->first
                  << " -> "
                  << found->second
                  << "\n";
    }

    if (values.contains(100)) {
        std::cout << "contains 100: true\n";
    } else {
        std::cout << "contains 100: false\n";
    }

    std::cout << "values[10] creates or accesses key 10\n";
    values[10] = "ten";

    std::cout << "values.at(10): " << values.at(10) << "\n";

    auto lower = values.lower_bound(13);
    auto upper = values.upper_bound(13);

    if (lower != values.end()) {
        std::cout << "lower_bound(13): "
                  << lower->first
                  << " -> "
                  << lower->second
                  << "\n";
    }

    if (upper != values.end()) {
        std::cout << "upper_bound(13): "
                  << upper->first
                  << " -> "
                  << upper->second
                  << "\n";
    }

    std::cout << "erase key 6\n";
    values.erase(6);

    std::cout << "after erase:\n";
    for (const auto& [key, value] : values) {
        std::cout << key << " -> " << value << "\n";
    }
}

void compare_custom_bst_and_stl_set() {
    print_separator("Comparison: Custom BST vs std::set");

    const std::vector<int> values{
        15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9
    };

    BinarySearchTree tree;
    std::set<int> set;

    for (int value : values) {
        tree.insert(make_bst_node(value));
        set.insert(value);
    }

    std::cout << "Custom BST inorder: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::set traversal: ";
    for (int value : set) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    BSTNode* custom_found = tree.tree_search(tree.root(), 13);
    auto stl_found = set.find(13);

    std::cout << "Custom BST search 13: "
              << (custom_found != nullptr ? "found" : "not found")
              << "\n";

    std::cout << "std::set find 13: "
              << (stl_found != set.end() ? "found" : "not found")
              << "\n";

    tree.tree_delete(tree.tree_search(tree.root(), 6));
    set.erase(6);

    std::cout << "Custom BST after deleting 6: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::set after erasing 6: ";
    for (int value : set) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

void compare_custom_red_black_tree_and_stl_set() {
    print_separator("Comparison: Custom RedBlackTree vs std::set");

    const std::vector<int> values{
        15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9
    };

    RedBlackTree tree;
    std::set<int> set;

    for (int value : values) {
        tree.insert(make_rb_node(value));
        set.insert(value);
    }

    std::cout << "Custom RedBlackTree inorder: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::set traversal: ";
    for (int value : set) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    RBTNode* nil = tree.root()->p;
    RBTNode* custom_found = tree.tree_search(tree.root(), 13);
    auto stl_found = set.find(13);

    std::cout << "Custom RedBlackTree search 13: "
              << (custom_found != nil ? "found" : "not found")
              << "\n";

    std::cout << "std::set find 13: "
              << (stl_found != set.end() ? "found" : "not found")
              << "\n";

    tree.tree_delete(tree.tree_search(tree.root(), 6));
    set.erase(6);

    std::cout << "Custom RedBlackTree after deleting 6: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::set after erasing 6: ";
    for (int value : set) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

void compare_custom_red_black_tree_and_stl_map() {
    print_separator("Comparison: Custom RedBlackTree vs std::map");

    const std::vector<int> values{
        15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9
    };

    RedBlackTree tree;
    std::map<int, std::string> map;

    for (int value : values) {
        tree.insert(make_rb_node(value));
        map.emplace(value, "value " + std::to_string(value));
    }

    std::cout << "Custom RedBlackTree inorder keys: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::map ordered keys:\n";
    for (const auto& [key, value] : map) {
        std::cout << key << " -> " << value << "\n";
    }

    RBTNode* nil = tree.root()->p;
    RBTNode* custom_found = tree.tree_search(tree.root(), 13);
    auto stl_found = map.find(13);

    std::cout << "Custom RedBlackTree search 13: "
              << (custom_found != nil ? "found" : "not found")
              << "\n";

    if (stl_found != map.end()) {
        std::cout << "std::map find 13: "
                  << stl_found->first
                  << " -> "
                  << stl_found->second
                  << "\n";
    }

    tree.tree_delete(tree.tree_search(tree.root(), 6));
    map.erase(6);

    std::cout << "Custom RedBlackTree after deleting 6: ";
    print_vector(tree.inorder_tree_walk());

    std::cout << "std::map after erasing 6:\n";
    for (const auto& [key, value] : map) {
        std::cout << key << " -> " << value << "\n";
    }
}

void conceptual_differences() {
    print_separator("Conceptual differences");

    std::cout
        << "1. Your BinarySearchTree is a plain BST.\n"
        << "2. A plain BST has operation time O(h), where h is the height.\n"
        << "3. In the worst case, h can become n if the tree degenerates into a chain.\n"
        << "4. std::set and std::map are ordered associative containers.\n"
        << "5. std::set stores unique keys.\n"
        << "6. std::multiset stores duplicate keys.\n"
        << "7. std::map stores key-value pairs with unique keys.\n"
        << "8. std::multimap stores key-value pairs with duplicate keys.\n"
        << "9. std::set and std::map usually use a balanced tree internally.\n"
        << "10. Their main operations are logarithmic: search, insert, erase are O(log n).\n"
        << "11. std::map::operator[] inserts a default value if the key does not exist.\n"
        << "12. std::set does not expose tree nodes, parent pointers, rotations, successor, or predecessor directly.\n";
}

}  // namespace

void run_stl_tree_examples() {
    custom_binary_search_tree_example();
    custom_red_black_tree_example();

    stl_set_example();
    stl_set_duplicate_behavior_example();
    stl_multiset_example();
    stl_map_example();

    compare_custom_bst_and_stl_set();
    compare_custom_red_black_tree_and_stl_set();
    compare_custom_red_black_tree_and_stl_map();

    conceptual_differences();
}