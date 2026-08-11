# CS509 Laboratory Repository

## Repository Overview

This repo holds our CS509 lab work.

- **Assignment 01** (C) — BFS, DFS, Dijkstra's SSSP over a CSR-based
  graph representation. See `Assignment__01/readme.md`.
- **Assignment 02** (C++) — Betweenness Centrality, Connected
  Components, Triangle Counting. Reuses Assignment 01's CSR code and
  BFS/DFS rather than duplicating it. See `Assignment__02/readme.md`.

Each assignment folder has its own `readme.md` with the algorithm
details, file structure, test cases, and results. Both run through the
single combined wrapper at the repo root, `common_wrapper.cpp`.

## Student / Pair Details

Mode: Double (Pair)

- Shivank Shubanshi — 2026AIM1021
- Aman Kumar — 2026AIM1011

## Language and Environment

- Language: C (Assignment 01), C++17 (Assignment 02)
- Compiler: gcc / g++
- Shell: bash (Git Bash / WSL / Linux terminal)

## Directory Structure

```
CS509_AIM1011_AIM1021/
├── README.md
├── common_wrapper.cpp   combined menu-driven wrapper for both assignments
├── Assignment__01/      BFS / DFS / SSSP — see Assignment__01/readme.md
└── Assignment__02/      Betweenness Centrality / Connected Components / Triangle Counting — see Assignment__02/readme.md
```

## Common Wrapper: Build and Usage

```
g++ -std=c++17 -o common_wrapper common_wrapper.cpp
./common_wrapper
```

```
1. Evaluate Assignment 1
2. Evaluate Assignment 2
3. Exit
```

- **Option 1** asks for an algorithm (BFS / DFS / SSSP) and an input
  file path, compiles `Assignment__01/driver/main`, and runs it.
- **Option 2** compiles Assignment 2's sources against Assignment 1's
  object files, then hands off to Assignment 2's own driver menu
  (Betweenness Centrality / Connected Components / Triangle Counting),
  which repeatedly asks for an input file path until you choose Exit.

See each assignment's `readme.md` for its file layout, algorithm
details, and result tables.
