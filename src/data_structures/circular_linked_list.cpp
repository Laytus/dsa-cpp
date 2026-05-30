#include "data_structures/circular_linked_list.hpp"

namespace dsa::data_structures {

CircularLinkedList::CircularLinkedList()
    : nil_(new Node{0, nullptr, nullptr}),
      size_(0) {
    nil_->prev = nil_;
    nil_->next = nil_;
}

CircularLinkedList::~CircularLinkedList() {
    if (nil_ == nullptr) {
        return;
    }
    
    Node* current = nil_->next;

    while (current != nil_) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    delete nil_;
    size_ = 0;
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList& other)
    : nil_(new Node{0, nullptr, nullptr}),
      size_(0) {
    nil_->prev = nil_;
    nil_->next = nil_;
    Node* current = other.nil_->next;

    while (current != other.nil_) {
        push_back(current->key);
        current = current->next;
    }
}

CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& other) {
    if (this == &other) {
        return *this;
    }

    // copy-and-swap-like
    CircularLinkedList copy(other);

    Node* old_nil = nil_;
    std::size_t old_size = size_;

    nil_ = copy.nil_;
    size_ = copy.size_;

    copy.nil_ = old_nil;
    copy.size_ = old_size;

    return *this;
}

CircularLinkedList::CircularLinkedList(CircularLinkedList&& other) noexcept
    : nil_(other.nil_),
      size_(other.size_) {
    other.nil_ = nullptr;
    other.size_ = 0;
}

CircularLinkedList& CircularLinkedList::operator=(CircularLinkedList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Node* current = nil_->next;

    while (current != nil_) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    nil_ = other.nil_;
    size_ = other.size_;
    
    other.nil_ = nullptr;
    other.size_ = 0;

    return *this;
}

Node* CircularLinkedList::list_search(const int key) {
    Node* x = nil_->next;

    while (x != nil_ && x->key != key) {
        x = x->next;
    }

    return x;
}

void CircularLinkedList::list_insert(Node* x) {
    x->next = nil_->next;
    x->prev = nil_;

    nil_->next->prev = x;
    nil_->next = x;

    ++size_;
}

void CircularLinkedList::list_delete(Node* x) {
    if (x == nullptr) {
        return;
    }

    x->prev->next = x->next;
    x->next->prev = x->prev;

    --size_;
    delete x;
}

bool CircularLinkedList::empty() const {
    return size_ == 0;
}

std::size_t CircularLinkedList::size() const {
    return size_;
}

void CircularLinkedList::push_front(int key) {
    Node* new_node = new Node();
    new_node->key = key;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    list_insert(new_node);
}

void CircularLinkedList::push_back(int key) {
    Node* new_node = new Node();
    new_node->key = key;
    new_node->next = nil_;
    new_node->prev = nil_->prev;

    nil_->prev->next = new_node;
    nil_->prev = new_node;

    ++size_;
}

void CircularLinkedList::remove(int key) {
    Node* x = list_search(key);
    list_delete(x);
}

Node* CircularLinkedList::head() const {
    return nil_->next;
}

Node* CircularLinkedList::tail() const {
    return nil_->prev;
}

}  // namespace dsa::data_structures