# dsa-cpp

**Data Structures & Algorithms in C++**  
*A structured self-study repository by Heber Arteaga*

---

## Overview

This repository documents my systematic study of Data Structures and Algorithms in C++, built around a structured 4-phase plan designed to reach a level suitable for software engineering and quant dev interviews.

The study plan is grounded in rigorous theory and intensive practice from day one — not sequential, but parallel: every concept studied is immediately implemented and applied to real problems.

---

## Study Plan

The plan is organized in 4 phases, each building on the previous:

| Phase | Topics | Duration |
|-------|--------|----------|
| 1 | Complexity analysis, arrays, hash tables, linked lists, stacks, binary search, two pointers, sliding window, prefix sum | Weeks 1–4 |
| 2 | Trees, heaps, graphs (BFS/DFS), BSTs, Union-Find, amortized analysis | Weeks 5–7 |
| 3 | Sorting, dynamic programming, greedy algorithms, shortest paths, backtracking | Weeks 8–12 |
| 4 | Interview preparation, mock interviews, problem review | Weeks 13–15 |

Full plan with chapters, exercises, and support materials: [`study-plan.md`](study-plan.md)

---

## Resources

**Primary theory:** [Introduction to Algorithms — CLRS (4th ed.)](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)  
**Primary practice:** [Neetcode 150](https://neetcode.io/practice)  
**Video support:** [MIT 6.006](https://www.youtube.com/playlist?list=PLUl4u3cNGP63EdVPNLG3ToM6LaEUuStEY) · [NeetCode YouTube](https://www.youtube.com/@NeetCode) · [Aditya Verma — DP](https://www.youtube.com/playlist?list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)  
**Reference:** [The Algorithm Design Manual — Skiena](https://www.algorist.com)

---

## Repository Structure

```
dsa-cpp/
├── README.md
├── study-plan.md           ← full phase-by-phase plan with chapters and exercises
├── theory/                 ← notes per topic, following CLRS chapter order
│   ├── 01-complexity/
│   ├── 02-arrays-strings/
│   └── ...
├── include/                ← header files for data structure implementations
│   ├── linked_list.hpp
│   └── ...
├── src/                    ← C++ implementations from scratch
│   ├── linked_list.cpp
│   └── ...
├── app/
│   ├── main.cpp
│   └── test_runner.cpp
└── problems/               ← LeetCode solutions, organized by topic
    ├── arrays/
    │   ├── two-sum.cpp
    │   └── two-sum.md      ← approach + complexity notes
    ├── trees/
    ├── graphs/
    ├── dynamic-programming/
    └── ...
```

Each problem in `problems/` has two files: the `.cpp` solution and a `.md` file documenting the approach, time complexity, space complexity, and pattern used.

---

## Problem Notes Format

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

I hold a degree in Mechanical Civil Engineering with a minor in Mechatronics from Pontificia Universidad Católica de Chile, and a Diplôme d'Ingénieur Généraliste from École Centrale de Lyon. I completed a 6-month internship at Capital Fund Management (Paris), where I worked on internal tooling and market data infrastructure.

This repository is part of a broader preparation plan for software engineering and quant dev roles, which also includes applied mathematics and quantitative finance study.