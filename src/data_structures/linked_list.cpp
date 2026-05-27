#include "data_structures/linked_list.hpp"

namespace dsa::data_structures {

LinkedList::LinkedList()
    : head_(nullptr),
      tail_(nullptr),
      size_(0) {}

LinkedList::~LinkedList() {
    Node* current = head_;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

LinkedList::LinkedList(const LinkedList& other)
    : head_(nullptr),
      tail_(nullptr),
      size_(0) {
    Node* current = other.head_;

    while (current != nullptr) {
        push_back(current->key);
        current = current->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this == &other) {
        return *this;
    }

    // copy-and-swap-like
    LinkedList copy(other);

    Node* old_head = head_;
    Node* old_tail = tail_;
    std::size_t old_size = size_;

    head_ = copy.head_;
    tail_ = copy.tail_;
    size_ = copy.size_;

    copy.head_ = old_head;
    copy.tail_ = old_tail;
    copy.size_ = old_size;

    return *this;
}

LinkedList::LinkedList(LinkedList&& other) noexcept
    : head_(other.head_),
      tail_(other.tail_),
      size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Node* current = head_;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;

    return *this;
}

Node* LinkedList::list_search(const int key) {
    Node* x = head_;

    while (x != nullptr && x->key != key) {
        x = x->next;
    }

    return x;
}

void LinkedList::list_insert(Node* x) {
    x->next = head_;
    x->prev = nullptr;

    if (head_ != nullptr) {
        head_->prev = x;
    } else {
        tail_ = x;
    }

    head_ = x;
    ++size_;
}

void LinkedList::list_delete(Node* x) {
    if (x == nullptr) {
        return;
    }

    if (x->prev != nullptr) {
        x->prev->next = x->next;
    } else {
        head_ = x->next;
    }

    if (x->next != nullptr) {
        x->next->prev = x->prev;
    } else {
        tail_ = x->prev;
    }

    --size_;
    delete x;
}

Node* LinkedList::head() const {
    return head_;
}

Node* LinkedList::tail() const {
    return tail_;
}

bool LinkedList::empty() const {
    return size_ == 0;
}

std::size_t LinkedList::size() const {
    return size_;
}

void LinkedList::push_back(int key) {
    Node* new_node = new Node();
    new_node->key = key;
    new_node->next = nullptr;
    new_node->prev = tail_;

    if (tail_ != nullptr) {
        tail_->next = new_node;
    } else {
        head_ = new_node;
    }

    tail_ = new_node;
    ++size_;
}

void LinkedList::push_front(int key) {
    Node* new_node = new Node();
    new_node->key = key;
    new_node->next = nullptr;
    new_node->prev = tail_;

    list_insert(new_node);
}

}  // namespace dsa::data_structures