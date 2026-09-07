# dsa-cpp

[![CI](https://github.com/Laytus/dsa-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/Laytus/dsa-cpp/actions/workflows/ci.yml)

**Data structures and algorithms implemented from scratch in modern C++23, based primarily on CLRS and backed by an extensive automated test suite.**

`dsa-cpp` is a C++ implementation project focused on algorithmic foundations, data-structure internals, correctness, and practical experimentation. The repository includes classic sorting and selection algorithms, custom containers and trees, dynamic programming, graph algorithms, shortest-path methods, and supporting experiments.

## Highlights

- Modern **C++23** implementation
- Core algorithms and data structures implemented from scratch
- **778 automated Catch2 test cases**
- **6,522 assertions**
- Individual test discovery through **CTest**
- Automated **GitHub Actions CI**
- Strict compiler-warning configuration
- Selected benchmarks and comparisons with STL facilities
- Theory and study notes based primarily on **CLRS**

## Implemented algorithms and data structures

### Sorting, searching, and selection

- Insertion sort
- Reverse insertion sort
- Linear search
- Selection sort
- Merge sort
- Heap sort
- Quicksort and randomized quicksort
- Counting sort
- Radix sort
- Bucket sort
- Minimum / maximum selection
- Randomized selection
- Deterministic selection

### Divide and conquer and matrix algorithms

- Maximum subarray
  - divide-and-conquer implementation
  - brute-force implementation
- Square-matrix multiplication
- Recursive matrix multiplication
- Strassen matrix multiplication

### Fundamental data structures

- Stack
- Queue
- Linked list
- Circular linked list
- Direct-access table
- Static chained hash table
- Universal chained hash table
- Open-addressing hash table
- Max-priority queue
- Min-priority queue
- Disjoint-set forest / Union-Find

### Trees

- Binary search tree
- Red-black tree
- Order-statistic tree
- Interval tree

The tree implementations include operations such as insertion, deletion, search, predecessor/successor queries, copy/move behavior, and structure-specific invariants.

### Dynamic programming and greedy algorithms

- Matrix-chain multiplication
- Longest common subsequence
- Optimal binary search tree
- Activity selection
- Huffman coding
- Dynamic alphabetic Huffman coding

### Graph algorithms

- Adjacency-list graph representation
- Weighted adjacency-list graph representation
- Breadth-first search
- Depth-first search
- Topological sort
- Strongly connected components
- Minimum spanning tree
  - Kruskal
  - Prim

### Shortest paths and all-pairs algorithms

- Single-source shortest-path utilities
- Bellman-Ford
- DAG shortest paths
- Dijkstra
- Slow all-pairs shortest paths
- Faster all-pairs shortest paths
- Floyd-Warshall
- Floyd-Warshall with predecessor reconstruction
- Transitive closure
- Johnson's all-pairs shortest paths

## Testing

The repository uses **Catch2** for automated tests and **CTest** for discovery and execution.

The current suite contains:

```text
778 test cases
6,522 assertions
```

Coverage includes:

- normal behavior
- edge cases
- invalid inputs and exceptions
- copy and move semantics
- data-structure invariants
- graph reachability and path reconstruction
- CLRS reference examples
- alternative implementations of the same problem
- agreement between related algorithms where appropriate

CTest discovers each Catch2 test case individually.

Run the complete suite with:

```bash
cmake -S . -B build \
  -DDSA_ENABLE_TESTS=ON \
  -DDSA_ENABLE_WARNINGS=ON \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --parallel

ctest --test-dir build --output-on-failure --no-tests=error
```

List all discovered tests with:

```bash
ctest --test-dir build -N
```

The test executable can also be run directly:

```bash
./build/dsa_tests
```

## Continuous integration

GitHub Actions automatically configures, builds, and tests the project on pushes and pull requests.

The CI workflow currently uses:

```text
macOS
C++23
CMake
Catch2
CTest
```

The project intentionally uses modern C++23 language and standard-library features, so CI targets a current AppleClang/libc++ environment consistent with the primary development setup.

## Build

### Requirements

- CMake 3.25+
- A C++23 compiler and standard library supporting the features used by the project
- Git, so CMake can fetch Catch2 when tests are enabled

### Build without tests

```bash
cmake -S . -B build
cmake --build build --parallel
```

Run the main executable:

```bash
./build/dsa_app
```

### Build with tests

```bash
cmake -S . -B build -DDSA_ENABLE_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure --no-tests=error
```

Useful CMake options:

```text
DSA_ENABLE_TESTS      Build the Catch2 test suite
DSA_ENABLE_WARNINGS   Enable the project's compiler-warning configuration
```

## Compiler warnings

When enabled, the project uses a strict warning configuration.

For Clang/GCC-style compilers:

```text
-Wall
-Wextra
-Wpedantic
-Wconversion
-Wsign-conversion
-Wshadow
```

For MSVC:

```text
/W4
/permissive-
```

These warnings are applied to the core `dsa_cpp` library.

## Repository structure

```text
dsa-cpp/
├── .github/
│   └── workflows/
│       └── ci.yml                 # Automated build and test workflow
│
├── app/
│   ├── main.cpp                   # Main executable entry point
│   └── experiment_runner.cpp      # Experiment runner
│
├── include/
│   ├── algorithms/                # Public algorithm interfaces
│   ├── data_structures/           # Public data-structure interfaces
│   └── utils/                     # Shared utilities
│
├── src/
│   ├── algorithms/                # Algorithm implementations
│   └── data_structures/           # Data-structure implementations
│
├── tests/
│   ├── algorithms/                # Catch2 algorithm tests
│   └── data_structures/           # Catch2 data-structure tests
│
├── experiments/
│   ├── algorithms/                # Algorithm benchmarks and comparisons
│   └── data_structures/           # STL and custom-structure experiments
│
├── theory/                        # Supporting theory notes
├── notes/
│   └── general/
│       └── dsa-study-plan.md      # Original study-plan reference
│
├── CMakeLists.txt
└── README.md
```

## Experiments

The `experiments/` directory complements the correctness-oriented test suite with exploratory code.

Examples include:

- maximum-subarray benchmarking
- custom hash-table comparisons with STL hash containers
- custom priority-queue comparisons with STL facilities
- tree-related STL examples
- activity-selection comparisons
- Huffman-coding comparisons

Build the repository and run:

```bash
./build/dsa_experiments
```

The experiments are intentionally separate from automated correctness tests.

## Implementation approach

The repository follows a few consistent principles:

1. **Implement fundamentals explicitly.**
   Core algorithms and data structures are implemented directly rather than replaced by STL equivalents.

2. **Stay close to the underlying algorithms.**
   CLRS pseudocode and invariants are preserved where useful, while adapting implementations to modern C++.

3. **Test behavior extensively.**
   Automated tests cover both expected behavior and important edge cases.

4. **Separate reusable code from experiments.**
   Core implementations live under `include/` and `src/`; exploratory comparisons and benchmarks live under `experiments/`.

5. **Prioritize correctness and clarity.**
   The project is designed as an algorithmic implementation and learning/reference repository rather than as a production container library.

## Theory and references

The implementation work is based primarily on:

- *Introduction to Algorithms* (CLRS), 4th edition
- MIT 6.006 material
- selected supplementary algorithm references

The `theory/` and `notes/` directories preserve supporting notes from the original study process. They are supplementary to the C++ implementation and automated test suite.

## Scope

This repository is intended to demonstrate and reinforce:

- algorithmic reasoning
- data-structure implementation
- modern C++
- memory and ownership behavior
- complexity-aware design
- graph and dynamic-programming fundamentals
- automated correctness testing

It is **not** intended to replace the C++ Standard Library or provide production-ready general-purpose containers.

## Status

The core implementation and automated-test suite are stable.

Current repository-quality infrastructure includes:

- CMake-based builds
- C++23 configuration
- strict compiler warnings
- Catch2
- CTest test discovery
- 778 automated tests
- GitHub Actions CI

Future changes are expected to focus on maintenance, corrections, or selective additions rather than broad expansion of the repository's scope.
