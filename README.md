# CS509 Laboratory Repository

## Repository Overview

This repository contains the CS509 laboratory Buddy Assignments.

- **Assignment 01** (C) — BFS, DFS, and Dijkstra's SSSP using a CSR-based graph representation.
- **Assignment 02** (C++) — Betweenness Centrality, Connected Components, and Triangle Counting. Assignment 01's CSR, BFS, and DFS functionality is reused.
- **Assignment 03** (C++) — **Gradient Descent** and **Maxflow-Mincut**. 

## Buddy / Pair Details


- **Shivank Shubanshi** — 2026AIM1021
- **Aman Kumar** — 2026AIM1011

---

## Language and Environment

- Assignment 01: C
- Assignment 02: C++17
- Assignment 03: C++17
- Compiler: `gcc` / `g++`
- Shell: Bash / Git Bash / WSL / Linux terminal


---

## Directory Structure

```text
CS509_AIM1011_AIM1021/
├── README.md
├── common_wrapper.cpp
│
├── Assignment__01/
│   ├── driver/
│   ├── src/
│   ├── tests/
│   ├── outputs/
│   └── readme.md
│
├── Assignment__02/
│   ├── driver/
│   ├── src/
│   ├── tests/
│   ├── outputs/
│   └── readme.md
│
└── Assignment__03/
    ├── driver/
    ├── src/
    ├── tests/
    ├── outputs/
    ├── tools/
    └── readme.md
```

---

# Assignment 01

Assignment 01 contains:

- BFS
- DFS
- Dijkstra's Single-Source Shortest Path

The graph representation uses CSR.

---

# Assignment 02

Assignment 02 contains:

- Betweenness Centrality
- Connected Components
- Triangle Counting

The implementation reuses the CSR and traversal functionality developed in Assignment 01.


---

# Assignment 03 

Assignment 03 contains:

1. **Gradient Descent**
2. **Maxflow-Mincut**

The assignment specification states that Gradient Descent does not use CSR, while Maxflow-Mincut does.

---

# Common Wrapper

The repository contains `common_wrapper.cpp` as the common entry point.

The menu is intended to expose:

```text
1. Evaluate Assignment 1
2. Evaluate Assignment 2
3. Evaluate Assignment 3
4. Exit
```

The Assignment 3 driver accepts an input-file path and then runs the selected buddy-task algorithm, as required by the Assignment 3 driver behaviour. fileciteturn1file0L425-L436

### Direct Any Assignment compilation

From the repository root:

```bash
gcc -I Assignment__01/src -c Assignment__01/src/graph.c -o /tmp/a3_graph.o
gcc -I Assignment__01/src -c Assignment__01/src/csr.c -o /tmp/a3_csr.o

g++ -std=c++17 -O2 -I Assignment__01/src \
    Assignment__03/driver/main.cpp \
    Assignment__03/src/gradientdescent.cpp \
    Assignment__03/src/maxflowMincut.cpp \
    /tmp/a3_graph.o \
    /tmp/a3_csr.o \
    -o Assignment__03/driver/main
```

Then:

```bash
./Assignment__03/driver/main
```

The source file present in this repository is named:

```text
Assignment__03/src/gradientdescent.cpp
```