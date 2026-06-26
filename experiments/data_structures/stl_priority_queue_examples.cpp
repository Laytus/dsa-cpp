#include "data_structures/max_priority_queue.hpp"
#include "data_structures/min_priority_queue.hpp"

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace {

using dsa::data_structures::MaxPriorityQueue;
using dsa::data_structures::MinPriorityQueue;
using dsa::data_structures::Node;

void print_separator(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

template <typename PriorityQueue>
void print_and_drain(PriorityQueue queue) {
    while (!queue.empty()) {
        std::cout << queue.top() << " ";
        queue.pop();
    }

    std::cout << "\n";
}

void stl_max_priority_queue_example() {
    print_separator("std::priority_queue<int> as max-priority queue");

    std::priority_queue<int> queue;

    queue.push(10);
    queue.push(40);
    queue.push(20);
    queue.push(5);
    queue.push(30);

    std::cout << "size: " << queue.size() << "\n";
    std::cout << "top / maximum: " << queue.top() << "\n";

    std::cout << "extract order: ";
    print_and_drain(queue);

    std::cout << "original queue size after print_and_drain: "
              << queue.size()
              << "\n";
}

void stl_min_priority_queue_example() {
    print_separator("std::priority_queue<int, vector<int>, greater<int>> as min-priority queue");

    std::priority_queue<
        int,
        std::vector<int>,
        std::greater<int>
    > queue;

    queue.push(10);
    queue.push(40);
    queue.push(20);
    queue.push(5);
    queue.push(30);

    std::cout << "size: " << queue.size() << "\n";
    std::cout << "top / minimum: " << queue.top() << "\n";

    std::cout << "extract order: ";
    print_and_drain(queue);
}

struct Task {
    std::size_t priority;
    std::string name;
};

struct MaxTaskPriority {
    bool operator()(const Task& lhs, const Task& rhs) const {
        return lhs.priority < rhs.priority;
    }
};

struct MinTaskPriority {
    bool operator()(const Task& lhs, const Task& rhs) const {
        return lhs.priority > rhs.priority;
    }
};

void stl_custom_type_max_priority_queue_example() {
    print_separator("std::priority_queue<Task> with custom max-priority comparator");

    std::priority_queue<
        Task,
        std::vector<Task>,
        MaxTaskPriority
    > queue;

    queue.push(Task{3, "low priority task"});
    queue.push(Task{10, "critical task"});
    queue.push(Task{5, "medium priority task"});
    queue.emplace(Task{1, "background task"});

    while (!queue.empty()) {
        const Task& task = queue.top();

        std::cout << "priority: " << task.priority
                  << ", name: " << task.name
                  << "\n";

        queue.pop();
    }
}

void stl_custom_type_min_priority_queue_example() {
    print_separator("std::priority_queue<Task> with custom min-priority comparator");

    std::priority_queue<
        Task,
        std::vector<Task>,
        MinTaskPriority
    > queue;

    queue.push(Task{3, "task with deadline 3"});
    queue.push(Task{10, "task with deadline 10"});
    queue.push(Task{5, "task with deadline 5"});
    queue.emplace(Task{1, "task with deadline 1"});

    while (!queue.empty()) {
        const Task& task = queue.top();

        std::cout << "priority: " << task.priority
                  << ", name: " << task.name
                  << "\n";

        queue.pop();
    }
}

void custom_max_priority_queue_example() {
    print_separator("Custom MaxPriorityQueue");

    std::vector<Node> nodes{
        Node{10, 100},
        Node{40, 400},
        Node{20, 200},
        Node{5, 50},
        Node{30, 300}
    };

    MaxPriorityQueue queue(nodes.size());

    for (Node& node : nodes) {
        queue.insert(&node);
    }

    std::cout << "capacity: " << queue.capacity() << "\n";
    std::cout << "heap_size: " << queue.heap_size() << "\n";

    Node* max = queue.maximum();

    std::cout << "maximum key: " << max->key
              << ", data: " << max->data
              << "\n";

    std::cout << "extract order:\n";

    while (queue.heap_size() > 0) {
        Node* node = queue.extract_max();

        std::cout << "key: " << node->key
                  << ", data: " << node->data
                  << "\n";
    }
}

void custom_min_priority_queue_example() {
    print_separator("Custom MinPriorityQueue");

    std::vector<Node> nodes{
        Node{10, 100},
        Node{40, 400},
        Node{20, 200},
        Node{5, 50},
        Node{30, 300}
    };

    MinPriorityQueue queue(nodes.size());

    for (Node& node : nodes) {
        queue.insert(&node);
    }

    std::cout << "capacity: " << queue.capacity() << "\n";
    std::cout << "heap_size: " << queue.heap_size() << "\n";

    Node* min = queue.minimum();

    std::cout << "minimum key: " << min->key
              << ", data: " << min->data
              << "\n";

    std::cout << "extract order:\n";

    while (queue.heap_size() > 0) {
        Node* node = queue.extract_min();

        std::cout << "key: " << node->key
                  << ", data: " << node->data
                  << "\n";
    }
}

void compare_stl_and_custom_max_priority_queue() {
    print_separator("Comparison: STL max-priority queue vs custom MaxPriorityQueue");

    const std::vector<int> values{10, 40, 20, 5, 30};

    std::priority_queue<int> stl_queue;

    for (int value : values) {
        stl_queue.push(value);
    }

    std::vector<Node> nodes{
        Node{10, 10},
        Node{40, 40},
        Node{20, 20},
        Node{5, 5},
        Node{30, 30}
    };

    MaxPriorityQueue custom_queue(nodes.size());

    for (Node& node : nodes) {
        custom_queue.insert(&node);
    }

    std::cout << "STL extract order:    ";

    while (!stl_queue.empty()) {
        std::cout << stl_queue.top() << " ";
        stl_queue.pop();
    }

    std::cout << "\n";

    std::cout << "Custom extract order: ";

    while (custom_queue.heap_size() > 0) {
        std::cout << custom_queue.extract_max()->key << " ";
    }

    std::cout << "\n";
}

void compare_stl_and_custom_min_priority_queue() {
    print_separator("Comparison: STL min-priority queue vs custom MinPriorityQueue");

    const std::vector<int> values{10, 40, 20, 5, 30};

    std::priority_queue<
        int,
        std::vector<int>,
        std::greater<int>
    > stl_queue;

    for (int value : values) {
        stl_queue.push(value);
    }

    std::vector<Node> nodes{
        Node{10, 10},
        Node{40, 40},
        Node{20, 20},
        Node{5, 5},
        Node{30, 30}
    };

    MinPriorityQueue custom_queue(nodes.size());

    for (Node& node : nodes) {
        custom_queue.insert(&node);
    }

    std::cout << "STL extract order:    ";

    while (!stl_queue.empty()) {
        std::cout << stl_queue.top() << " ";
        stl_queue.pop();
    }

    std::cout << "\n";

    std::cout << "Custom extract order: ";

    while (custom_queue.heap_size() > 0) {
        std::cout << custom_queue.extract_min()->key << " ";
    }

    std::cout << "\n";
}

void stl_priority_queue_api_notes() {
    print_separator("std::priority_queue API notes");

    std::priority_queue<int> queue;

    std::cout << "queue.empty(): " << std::boolalpha << queue.empty() << "\n";

    queue.push(10);
    queue.push(30);
    queue.emplace(20);

    std::cout << "After push/emplace:\n";
    std::cout << "queue.empty(): " << queue.empty() << "\n";
    std::cout << "queue.size(): " << queue.size() << "\n";
    std::cout << "queue.top(): " << queue.top() << "\n";

    std::cout << "Calling pop() removes top but does not return it.\n";

    const int top = queue.top();
    queue.pop();

    std::cout << "saved top before pop: " << top << "\n";
    std::cout << "new top: " << queue.top() << "\n";

    std::priority_queue<int> other;
    other.push(100);
    other.push(200);

    queue.swap(other);

    std::cout << "After swap, queue.top(): " << queue.top() << "\n";
}

void conceptual_differences() {
    print_separator("Conceptual differences");

    std::cout
        << "1. std::priority_queue is an adapter, not a full heap class.\n"
        << "2. By default, std::priority_queue<T> is a max-priority queue.\n"
        << "3. For a min-priority queue, use std::greater<T> as comparator.\n"
        << "4. top() returns the highest-priority element.\n"
        << "5. pop() removes the top element but does not return it.\n"
        << "6. std::priority_queue does not expose increase_key or decrease_key.\n"
        << "7. std::priority_queue does not support searching arbitrary elements.\n"
        << "8. Custom implementation exposes CLRS-style operations like extract_max, increase_key, extract_min, decrease_key.\n";
}

}  // namespace

void run_stl_priority_queue_examples() {
    stl_max_priority_queue_example();
    stl_min_priority_queue_example();

    stl_custom_type_max_priority_queue_example();
    stl_custom_type_min_priority_queue_example();

    custom_max_priority_queue_example();
    custom_min_priority_queue_example();

    compare_stl_and_custom_max_priority_queue();
    compare_stl_and_custom_min_priority_queue();

    stl_priority_queue_api_notes();
    conceptual_differences();
}