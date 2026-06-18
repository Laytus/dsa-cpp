#pragma once

#include <cstddef>

namespace dsa::data_structures {

struct DSFNode {
    int key;
    DSFNode* p;
    std::size_t rank;
    DSFNode* next;
}; 

class DisjointSetForest {
public:
    DisjointSetForest();

    ~DisjointSetForest();

    DisjointSetForest(const DisjointSetForest& other);
    DisjointSetForest& operator=(const DisjointSetForest& other);

    DisjointSetForest(DisjointSetForest&& other) noexcept;
    DisjointSetForest& operator=(DisjointSetForest&& other) noexcept;

    DSFNode* make_set(int key);
    DSFNode* find_set(DSFNode* x);
    void union_sets(DSFNode* x, DSFNode* y);
    bool connected(DSFNode* x, DSFNode* y);

    std::size_t size() const;
    
private:
    void link(DSFNode* x, DSFNode* y);
    void clear();

    DSFNode* head_;
    std::size_t size_;
};

}  // namespace dsa::data_structures