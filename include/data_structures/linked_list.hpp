#pragma once

#include <cstddef>

namespace dsa::data_structures {

struct Node {
    int key;
    Node* prev;
    Node* next;
};

class LinkedList {
public:
    LinkedList();

    ~LinkedList();

    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;

    Node* list_search(const int key);
    void push_front(int key);
    void push_back(int key);

    void list_delete(Node* x);

    Node* head() const;
    Node* tail() const;
    
    bool empty() const;

    std::size_t size() const;

private:
    void list_insert(Node* x);
    
    Node* head_;
    Node* tail_;
    std::size_t size_;
};

}  // namespace dsa::data_structures