#pragma once

#include <cstddef>

namespace dsa::data_structures {

struct Node {
    int key;
    Node* prev;
    Node* next;
};

class CircularLinkedList {
public:
    CircularLinkedList();

    ~CircularLinkedList();

    CircularLinkedList(const CircularLinkedList& other);
    CircularLinkedList& operator=(const CircularLinkedList& other);

    CircularLinkedList(CircularLinkedList&& other) noexcept;
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept;

    Node* list_search(const int key);
    void push_front(int key);
    void push_back(int key);
    void remove(int key);

    Node* head() const;
    Node* tail() const;
    
    bool empty() const;

    std::size_t size() const;

private:
    void list_insert(Node* x);
    void list_delete(Node* x);
    
    // Node* head_;
    // Node* tail_;
    Node* nil_;
    std::size_t size_;
};

}  // namespace dsa::data_structures