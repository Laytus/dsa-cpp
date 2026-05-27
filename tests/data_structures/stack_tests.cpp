#include <catch2/catch_test_macros.hpp>

#include "data_structures/stack.hpp"

#include <stdexcept>
#include <utility>

TEST_CASE("Stack constructor creates an empty stack") {
    dsa::data_structures::Stack stack(3);

    REQUIRE(stack.empty());
    REQUIRE_FALSE(stack.full());
    REQUIRE(stack.size() == 0);
    REQUIRE(stack.capacity() == 3);
}

TEST_CASE("Stack constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(dsa::data_structures::Stack(0), std::underflow_error);
}

TEST_CASE("Stack push adds one element") {
    dsa::data_structures::Stack stack(3);

    stack.push(10);

    REQUIRE_FALSE(stack.empty());
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == 10);
}

TEST_CASE("Stack push adds several elements") {
    dsa::data_structures::Stack stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    REQUIRE(stack.size() == 3);
    REQUIRE(stack.full());
    REQUIRE(stack.top() == 30);
}

TEST_CASE("Stack pop returns the last pushed element") {
    dsa::data_structures::Stack stack(3);

    stack.push(10);
    stack.push(20);

    REQUIRE(stack.pop() == 20);
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == 10);
}

TEST_CASE("Stack follows LIFO order") {
    dsa::data_structures::Stack stack(5);

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    REQUIRE(stack.pop() == 4);
    REQUIRE(stack.pop() == 3);
    REQUIRE(stack.pop() == 2);
    REQUIRE(stack.pop() == 1);
    REQUIRE(stack.empty());
}

TEST_CASE("Stack top returns the last pushed element without removing it") {
    dsa::data_structures::Stack stack(3);

    stack.push(42);

    REQUIRE(stack.top() == 42);
    REQUIRE(stack.size() == 1);

    REQUIRE(stack.top() == 42);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Stack pop throws underflow when stack is empty") {
    dsa::data_structures::Stack stack(3);

    REQUIRE_THROWS_AS(stack.pop(), std::underflow_error);
}

TEST_CASE("Stack top throws underflow when stack is empty") {
    dsa::data_structures::Stack stack(3);

    REQUIRE_THROWS_AS(stack.top(), std::underflow_error);
}

TEST_CASE("Stack push throws overflow when stack is full") {
    dsa::data_structures::Stack stack(2);

    stack.push(10);
    stack.push(20);

    REQUIRE(stack.full());
    REQUIRE_THROWS_AS(stack.push(30), std::overflow_error);
}

TEST_CASE("Stack size updates correctly after push and pop") {
    dsa::data_structures::Stack stack(4);

    REQUIRE(stack.size() == 0);

    stack.push(10);
    REQUIRE(stack.size() == 1);

    stack.push(20);
    REQUIRE(stack.size() == 2);

    stack.pop();
    REQUIRE(stack.size() == 1);

    stack.pop();
    REQUIRE(stack.size() == 0);
    REQUIRE(stack.empty());
}

TEST_CASE("Stack copy constructor creates an independent copy") {
    dsa::data_structures::Stack original(3);
    original.push(10);
    original.push(20);

    dsa::data_structures::Stack copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.top() == 20);

    copy.push(30);

    REQUIRE(copy.top() == 30);
    REQUIRE(copy.size() == 3);

    REQUIRE(original.top() == 20);
    REQUIRE(original.size() == 2);
}

TEST_CASE("Stack copy assignment creates an independent copy") {
    dsa::data_structures::Stack original(3);
    original.push(10);
    original.push(20);

    dsa::data_structures::Stack copy(5);
    copy.push(99);

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.top() == 20);

    copy.push(30);

    REQUIRE(copy.top() == 30);
    REQUIRE(copy.size() == 3);

    REQUIRE(original.top() == 20);
    REQUIRE(original.size() == 2);
}

TEST_CASE("Stack copy assignment handles self-assignment") {
    dsa::data_structures::Stack stack(3);

    stack.push(10);
    stack.push(20);

    stack = stack;

    REQUIRE(stack.size() == 2);
    REQUIRE(stack.capacity() == 3);
    REQUIRE(stack.top() == 20);
}

TEST_CASE("Stack move constructor transfers ownership") {
    dsa::data_structures::Stack original(3);
    original.push(10);
    original.push(20);

    dsa::data_structures::Stack moved(std::move(original));

    REQUIRE(moved.size() == 2);
    REQUIRE(moved.capacity() == 3);
    REQUIRE(moved.top() == 20);
}

TEST_CASE("Stack move assignment transfers ownership") {
    dsa::data_structures::Stack original(3);
    original.push(10);
    original.push(20);

    dsa::data_structures::Stack moved(5);
    moved.push(99);

    moved = std::move(original);

    REQUIRE(moved.size() == 2);
    REQUIRE(moved.capacity() == 3);
    REQUIRE(moved.top() == 20);
}

TEST_CASE("Stack move assignment handles self-move-assignment") {
    dsa::data_structures::Stack stack(3);

    stack.push(10);
    stack.push(20);

    stack = std::move(stack);

    REQUIRE(stack.size() == 2);
    REQUIRE(stack.capacity() == 3);
    REQUIRE(stack.top() == 20);
}