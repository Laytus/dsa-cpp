# DSA Study Plan in C++

Complete guide to build solid foundations in Data Structures & Algorithms, oriented toward software interviews and quant dev.

**Estimated duration:** 13–15 weeks of intensive study  
**Language:** C++  
**Main theory guide:** Introduction to Algorithms (CLRS, 4th ed.)  
**Main practice guide:** Neetcode 150 (LeetCode)

---

## Legend

| Symbol | Meaning |
|---------|---------|
| `[impl]` | Study and implement in C++ |
| `[theory]` | Reading only, no implementation |
| `[pattern]` | Technique or pattern not covered in CLRS |
| `[LC]` | LeetCode / Neetcode 150 exercises |
| `[support]` | Supporting material (use when CLRS feels dense) |
| `⚠️` | Critical topic — requires extra time and attention |

---

## Workflow per topic

1. Study the chapter/concept (CLRS or indicated source)
2. Implement the data structure or algorithm from scratch in C++
3. Add the implementation to the repo in `include/` and `src/`
4. Add chapter notes in `theory/`
5. Solve the indicated LeetCode exercises
6. Add notes for each problem in `problems/` (approach + complexity)

> Steps 2–4 are skipped for items marked as `[theory]`.

---

## Phase 1 — Foundations and complexity
**Weeks 1–4**

### CLRS `[impl]`

- [x] **Ch. 1** — The Role of Algorithms in Computing  
  Quick reading. Establishes the vocabulary of the book.

- [x] **Ch. 2** — Getting Started  
  Insertion sort, merge sort, loop invariants. First real implementation in C++.

- [x] **Ch. 3** — Characterizing Running Times  
  Big O, Θ, Ω. Foundation of all complexity analysis.

- [x] **Ch. 4** — Divide-and-Conquer *(sections 4.1–4.5 only)*  
  Recurrences and recursion tree.

- [ ] **Ch. 10** — Elementary Data Structures  
  Arrays, linked lists, stacks, queues. Implement each one from scratch in C++.

- [ ] **Ch. 11** — Hash Tables  
  Hashing, chaining, open addressing. Also use STL: `unordered_map`, `unordered_set`.

### Patterns / techniques not in CLRS `[pattern]`

Source for all: [Neetcode.io](https://neetcode.io) + NeetCode YouTube channel.

- **Binary Search** — Classic implementation + variants (lower bound, upper bound)
- **Two Pointers** — Fundamental pattern for arrays and strings
- **Sliding Window** — Fixed window and variable window
- **Prefix Sum** — Technique for range queries in O(1)
- **Stack Patterns** — Monotonic stack, next greater element

### LeetCode exercises `[LC]`

**Arrays & Hashing** — Neetcode 150 (9 problems)
- Contains Duplicate
- Valid Anagram
- Two Sum
- Group Anagrams
- Top K Frequent Elements
- Encode and Decode Strings
- Product of Array Except Self
- Valid Sudoku
- Longest Consecutive Sequence

**Two Pointers** — Neetcode 150 (5 problems)
- Valid Palindrome
- Two Sum II
- 3Sum
- Container With Most Water
- Trapping Rain Water

**Sliding Window** — Neetcode 150 (6 problems)
- Best Time to Buy and Sell Stock
- Longest Substring Without Repeating Characters
- Longest Repeating Character Replacement
- Permutation in String
- Minimum Window Substring
- Sliding Window Maximum

**Binary Search** — Neetcode 150 (7 problems)
- Binary Search
- Search a 2D Matrix
- Koko Eating Bananas
- Find Minimum in Rotated Sorted Array
- Search in Rotated Sorted Array
- Time-Based Key-Value Store
- Median of Two Sorted Arrays

**Stack** — Neetcode 150 (7 problems)
- Valid Parentheses
- Min Stack
- Evaluate Reverse Polish Notation
- Generate Parentheses
- Daily Temperatures
- Car Fleet
- Largest Rectangle in Histogram

### Supporting material `[support]`

- **MIT 6.006 — Lectures 1–5** (YouTube)  
  To consolidate Big O and computation models when CLRS chapters 1–3 become abstract.

---

## Phase 2 — Nonlinear data structures and graphs
**Weeks 5–7**

### CLRS `[impl]`

- **Ch. 6** — Heapsort  
  Heap as a data structure (min-heap, max-heap). Implement heap from scratch and use STL `priority_queue`.

- **Ch. 12** — Binary Search Trees  
  Insertion, search, deletion. Implement a complete BST in C++. STL: `map`, `set`.

- **Ch. 17** — Amortized Analysis  
  Aggregate, accounting, and potential methods. Explains why `vector::push_back` is amortized O(1).

- **Ch. 21** — Data Structures for Disjoint Sets  
  Union-Find with union by rank and path compression. Implement from scratch — foundation of Kruskal.

- **Ch. 22** — Elementary Graph Algorithms  
  BFS, DFS, topological sorting, strongly connected components. Implement using adjacency lists.

### CLRS `[theory]`

- **Ch. 13** — Red-Black Trees  
  Understand the properties and balancing guarantees. Do not implement. Know that STL `map`/`set` use them internally.

- **Ch. 23** — Minimum Spanning Trees  
  Kruskal and Prim conceptually. Understand the proof of correctness. Do not implement from scratch.

### LeetCode exercises `[LC]`

**Linked List** — Neetcode 150 (11 problems)
- Reverse Linked List
- Merge Two Sorted Lists
- Reorder List
- Remove Nth Node From End of List
- Copy List with Random Pointer
- Add Two Numbers
- Linked List Cycle
- Find the Duplicate Number
- LRU Cache
- Merge K Sorted Lists
- Reverse Nodes in K-Group

**Trees** — Neetcode 150 (15 problems)
- Invert Binary Tree
- Maximum Depth of Binary Tree
- Diameter of Binary Tree
- Balanced Binary Tree
- Same Tree
- Subtree of Another Tree
- Lowest Common Ancestor of a BST
- Binary Tree Level Order Traversal
- Binary Tree Right Side View
- Count Good Nodes in Binary Tree
- Validate Binary Search Tree
- Kth Smallest Element in a BST
- Construct Binary Tree from Preorder and Inorder Traversal
- Binary Tree Maximum Path Sum
- Serialize and Deserialize Binary Tree

**Heap / Priority Queue** — Neetcode 150 (7 problems)
- Kth Largest Element in a Stream
- Last Stone Weight
- K Closest Points to Origin
- Kth Largest Element in an Array
- Task Scheduler
- Design Twitter
- Find Median from Data Stream

**Graphs — BFS/DFS** — Neetcode 150 (13 problems)
- Number of Islands
- Max Area of Island
- Clone Graph
- Walls and Gates
- Rotting Oranges
- Pacific Atlantic Water Flow
- Surrounded Regions
- Course Schedule
- Course Schedule II
- Graph Valid Tree
- Number of Connected Components in an Undirected Graph
- Redundant Connection
- Word Ladder

**Tries** — Neetcode 150 (3 problems)
- Implement Trie (Prefix Tree)
- Design Add and Search Words Data Structure
- Word Search II

### Supporting material `[support]`

- **Skiena — Ch. 4–6** (The Algorithm Design Manual)  
  For graphs: more intuitive than CLRS. Use when chapters 22–23 feel abstract.

- **MIT 6.006 — Lectures 6–14** (YouTube)  
  BSTs, hashing, graphs. Covers exactly the topics of this phase.

---

## Phase 3 — Classical algorithms and paradigms
**Weeks 8–12**

### CLRS `[impl]`

- **Ch. 7** — Quicksort  
  Implement with Lomuto and Hoare partitioning. Analyze worst/average case.

- **Ch. 8** — Sorting in Linear Time  
  Counting sort, radix sort, bucket sort. Understand when each one beats O(n log n).

- **Ch. 9** — Medians and Order Statistics  
  Quickselect for the k-th element. Implement and analyze.

- **Ch. 14** — Augmenting Data Structures *(sec. 14.1)*  
  Order-statistic trees. Only the first section as conceptual foundation.

- **Ch. 15** — Dynamic Programming ⚠️  
  Rod cutting, LCS, matrix chain. The most important chapter of the book.  
  Complement it mandatorily with audiovisual material (see support section).

- **Ch. 16** — Greedy Algorithms  
  Activity selection, Huffman coding. Implement and compare with DP equivalents.

- **Ch. 24** — Single-Source Shortest Paths  
  Dijkstra and Bellman-Ford. Implement Dijkstra with `priority_queue` in C++.

### CLRS `[theory]`

- **Ch. 25** — All-Pairs Shortest Paths *(secs. 25.1–25.2)*  
  Floyd-Warshall and Johnson. Understand the logic and complexity. Do not implement.

### LeetCode exercises `[LC]`

**Sorting** — Extra LeetCode
- Sort Colors (LC 75)
- Merge Intervals (LC 56)
- Insert Interval (LC 57)
- Largest Number (LC 179)

**Intervals** — Neetcode 150 (5 problems)
- Insert Interval
- Merge Intervals
- Non-overlapping Intervals
- Meeting Rooms I
- Meeting Rooms II
- Minimum Interval to Include Each Query

**Greedy** — Extra LeetCode
- Jump Game (LC 55)
- Jump Game II (LC 45)
- Gas Station (LC 134)
- Hand of Straights (LC 846)

**1-D Dynamic Programming** ⚠️ — Neetcode 150 (12 problems)
- Climbing Stairs
- Min Cost Climbing Stairs
- House Robber
- House Robber II
- Longest Palindromic Substring
- Palindromic Substrings
- Decode Ways
- Coin Change
- Maximum Product Subarray
- Word Break
- Longest Increasing Subsequence
- Partition Equal Subset Sum

**2-D Dynamic Programming** ⚠️ — Neetcode 150 (11 problems)
- Unique Paths
- Longest Common Subsequence
- Best Time to Buy and Sell Stock with Cooldown
- Coin Change II
- Target Sum
- Interleaving String
- Longest Increasing Path in a Matrix
- Distinct Subsequences
- Edit Distance
- Burst Balloons
- Regular Expression Matching

**Advanced Graphs — Dijkstra** — Neetcode 150 (6 problems)
- Reconstruct Itinerary
- Min Cost to Connect All Points
- Network Delay Time
- Swim in Rising Water
- Alien Dictionary
- Cheapest Flights Within K Stops

**Backtracking** — Neetcode 150 (9 problems)
- Subsets
- Subsets II
- Combination Sum
- Combination Sum II
- Permutations
- Word Search
- Palindrome Partitioning
- Letter Combinations of a Phone Number
- N-Queens

**AtCoder Educational DP Contest** ⚠️ — 26 problems (A–Z)  
The best resource for systematic DP practice ordered by pattern.  
URL: https://atcoder.jp/contests/dp

### Supporting material — DP mandatory for this phase `[support]`

- **Aditya Verma — DP Playlist** (YouTube)  
  The most complete audiovisual source for DP. Covers all patterns: knapsack, LCS, LIS, MCM, etc.  
  Watch in parallel with CLRS Ch. 15.

- **NeetCode — DP Playlist** (YouTube)  
  Watch after Aditya Verma. Focused on the exact interview patterns, ordered by difficulty.

- **MIT 6.006 — Lectures 15–22** (YouTube)  
  Formal DP and shortest paths. To consolidate the theory before Aditya Verma.

- **Skiena — Ch. 8** (The Algorithm Design Manual)  
  Very intuitive explanation with real examples. Use when CLRS Ch. 15 feels too abstract.

---

## Phase 4 — Interview preparation
**Weeks 13–15**

There are no new CLRS chapters. The focus is consolidation through mock interviews,
reviewing gaps, and completing pending Neetcode 150 problems.

### CLRS `[theory]`

- **Ch. 5** — Probabilistic Analysis and Randomized Algorithms  
  Review reading. Useful to understand randomized quicksort and probabilistic hash tables.

### LeetCode exercises `[LC]`

**Bit Manipulation** — Neetcode 150 (7 problems)
- Single Number
- Number of 1 Bits
- Counting Bits
- Reverse Bits
- Missing Number
- Sum of Two Integers
- Reverse Integer

**Math & Geometry** — Neetcode 150 (8 problems)
- Rotate Image
- Spiral Matrix
- Set Matrix Zeroes
- Happy Number
- Plus One
- Pow(x, n)
- Multiply Strings
- Detect Squares

**Pending problems from previous phases**  
Review which problems were not solved or not fully understood. Prioritize those marked as Hard.

### Mock interviews `[support]`

- **Pramp** — https://www.pramp.com  
  Free mock interviews with other candidates. 2–3 sessions per week.

- **Interviewing.io** — https://interviewing.io  
  Mock interviews with engineers from top companies. More demanding than Pramp.

> Goal: verbalize your reasoning out loud while solving.
> Quant firms especially value the thought process, not only the solution.

---

## Repository structure

```text
dsa-cpp/
├── README.md
├── theory/
│   ├── 01-complexity/
│   │   └── notes.md
│   ├── 02-arrays/
│   │   └── notes.md
│   └── ...
├── app/
│   ├── main.cpp
│   └── test_runner.cpp
├── include/
│   ├── linked_list.hpp
│   ├── binary_tree.hpp
│   ├── hash_table.hpp
│   └── ...
├── src/
│   ├── linked_list.cpp
│   ├── binary_tree.cpp
│   ├── hash_table.cpp
│   └── ...
└── problems/
    ├── arrays/
    │   ├── two-sum.cpp
    │   └── two-sum.md      ← approach + complexity in 3–5 lines
    ├── trees/
    └── ...
```

### `.md` file format per problem

```markdown
## Two Sum

**Approach:** Hash map to store seen complements. Single pass.  
**Time:** O(n)  
**Space:** O(n)  
**Difficulty:** Easy  
**Pattern:** Arrays & Hashing
```

---

## Consolidated resources

| Resource | Type | When to use it |
|----------|------|----------------|
| CLRS (4th ed.) | Book | Main theory guide — all phases |
| Neetcode 150 | LeetCode | Main practice — all phases |
| The Algorithm Design Manual (Skiena) | Book | Support when CLRS is too dense |
| MIT 6.006 (YouTube) | Video | Visual support for theory — phases 1–3 |
| NeetCode (YouTube) | Video | Interview patterns and DP — phases 1–3 |
| Aditya Verma DP Playlist (YouTube) | Video | DP — phase 3 (mandatory) |
| AtCoder Educational DP Contest | Practice | Extra DP — phase 3 (mandatory) |
| Pramp / Interviewing.io | Mock interviews | Phase 4 |
