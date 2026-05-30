#pragma once

#include <cstddef>

namespace dsa::data_structures {

struct Node {
    std::size_t key;
    int data;
};

class DirectAccessTable {
public:
    explicit DirectAccessTable(std::size_t capacity);

    ~DirectAccessTable();

    DirectAccessTable(const DirectAccessTable& other);
    DirectAccessTable& operator=(const DirectAccessTable& other);
    
    DirectAccessTable(DirectAccessTable&& other) noexcept;
    DirectAccessTable& operator=(DirectAccessTable&& other) noexcept;

    Node* direct_access_search(const std::size_t k) const;
    void direct_access_insert(Node* x);
    void direct_access_delete(Node* x);

private:
    Node** table_;
    std::size_t capacity_;
};

}  // namespace dsa::data_structures