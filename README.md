# dsa-cpp

**Data Structures & Algorithms in C++**  
*A structured self-study repository by Heber Arteaga*

---

## Overview

This repository documents my systematic study of Data Structures and Algorithms in C++, with focus on implementing core CLRS algorithms and data structures from scratch in modern C++ and applying them to interview-style problems.

The goal is to combine rigorous theory with practical implementation: each concept studied is implemented, tested, and later applied to NeetCode-style problems and experiments.

---

## Study Plan

The plan is organized in 4 phases, each building on the previous:

| Phase | Topics | Duration |
|-------|--------|----------|
| 1 | Complexity analysis, arrays, hash tables, linked lists, stacks, binary search, two pointers, sliding window, prefix sum | Weeks 1–4 |
| 2 | Trees, heaps, graphs (BFS/DFS), BSTs, Union-Find, amortized analysis | Weeks 5–7 |
| 3 | Sorting, dynamic programming, greedy algorithms, shortest paths, backtracking | Weeks 8–12 |
| 4 | Interview preparation, mock interviews, problem review | Weeks 13–15 |

Full plan with chapters, exercises, and support materials: [`dsa-study-plan.md`](notes/general/dsa-study-plan.md)

---

## Resources

**Primary theory:** [Introduction to Algorithms — CLRS (4th ed.)](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)  
**Primary practice:** [Neetcode 150](https://neetcode.io/practice)  
**Video support:** [MIT 6.006](https://www.youtube.com/playlist?list=PLUl4u3cNGP63EdVPNLG3ToM6LaEUuStEY) · [NeetCode YouTube](https://www.youtube.com/@NeetCode) · [Aditya Verma — DP](https://www.youtube.com/playlist?list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)  
**Reference:** [The Algorithm Design Manual — Skiena](https://www.algorist.com)

---

## Repository Structure

```text
dsa-cpp/
├── app/
│   ├── main.cpp                 # General entry point
│   ├── exercise_runner.cpp      # Sandbox for quick problem-solving experiments
│   ├── experiment_runner.cpp    # Runs custom algorithm/data structure experiments
│   └── problem_runner.cpp       # Runs selected NeetCode-style solutions
│
├── include/
│   ├── algorithms/              # Algorithm headers
│   ├── data_structures/         # Data structure headers
│   └── utils/                   # Shared utilities
│
├── src/
│   ├── algorithms/              # Algorithm implementations
│   └── data_structures/         # Data structure implementations
│
├── tests/
│   ├── algorithms/              # Unit tests for algorithms
│   └── data_structures/         # Unit tests for data structures
│
├── experiments/                 # Exploratory programs, STL comparisons, and benchmarks
├── problems/                    # NeetCode / interview-style problems and notes
├── theory/                      # Topic notes and patterns
├── notes/
│   └── general/
│       └── dsa-study-plan.md    # Main study plan
│
├── CMakeLists.txt
└── README.md
```

---

## Project Components

- `include/` and `src/` contain the core CLRS-style implementations.
- `tests/` contains unit tests for correctness.
- `experiments/` contains exploratory programs used to compare custom implementations with STL containers or benchmark behavior.
- `problems/` contains NeetCode-style solutions and notes.
- `theory/` contains topic notes and reusable problem-solving patterns.
- `app/` contains runner files used to execute experiments, problems, or sandbox code.

---

## Build and Test

```bash
cmake -S . -B build -DDSA_ENABLE_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

---

## Runners

- `main.cpp`: general executable entry point.
- `exercise_runner.cpp`: sandbox for quickly testing ideas and problem-solving snippets.
- `experiment_runner.cpp`: runs experiment files from `experiments/`.
- `problem_runner.cpp`: runs selected NeetCode-style solutions from `problems/`.

---

## Implementation Philosophy

- Implement core algorithms and data structures from scratch before relying on STL equivalents.
- Keep implementations close to CLRS pseudocode when useful, while writing idiomatic modern C++.
- Write tests for each implementation.
- Use experiments to compare custom implementations with STL behavior or to benchmark performance.
- Prioritize correctness and clarity before optimization.

---

## Problem Notes Format

Each problem in `problems/` can include a `.cpp` solution and a `.md` file documenting the approach, time complexity, space complexity, and pattern used.

```markdown
## Problem Name

**Approach:** brief description of the strategy used  
**Time complexity:** O(...)  
**Space complexity:** O(...)  
**Pattern:** e.g. Two Pointers / Sliding Window / BFS / DP  
**Difficulty:** Easy / Medium / Hard
```

---

## Background

This repository is part of my preparation for software engineering and quant developer roles, with an emphasis on rigorous algorithmic foundations, modern C++, and interview problem solving.