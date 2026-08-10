# CS509 Laboratory Repository

## Repository Overview

This repo holds our CS509 lab work.

- **Assignment 01** (C) — BFS, DFS, Dijkstra's SSSP over a CSR-based
  graph representation. See `Assignment__01/readme.md`.
- **Assignment 02** (C++) — Bellman-Ford, Floyd-Warshall, Triangle
  Counting, Betweenness Centrality, Connected Components. Reuses
  Assignment 01's CSR code rather than duplicating it. See
  `Assignment__02/readme.md`.

Each assignment folder has its own `readme.md` with the algorithm
details, test cases, and results. Both run through the common
menu-driven wrappers in `common_wrapper/`.

## Student / Pair Details

Mode: Double (Pair)

- Shivank Shubanshi — 2026AIM1021
- Aman Kumar — 2026AIM1011

## Language and Environment

- Language: C
- Compiler: gcc, built with `-Wall -Wextra`
- Shell: bash (Git Bash / WSL / Linux terminal)

## Directory Structure

```
CS509_AIM1011_AIM1021/
├── README.md
├── common_wrapper/
│   ├── wrapper.c            Assignment 01 menu
│   └── wrapper2.cpp         Assignment 02 menu
├── Assignment__01/
│   ├── readme.md
│   ├── driver/
│   │   └── main.c
│   ├── src/
│   │   ├── csr.c / csr.h
│   │   ├── bfs.c
│   │   ├── dfs.c
│   │   ├── sssp.c / sssp.h
│   │   └── graph.c / graph.h
│   ├── tests/
│   │   ├── bfs.txt, bfs2.txt
│   │   ├── dfs.txt, dfs2.txt
│   │   └── sssp.txt, sssp2.txt
│   └── outputs/             (created automatically when the wrapper runs)
└── Assignment__02/
    ├── readme.md
    ├── driver/
    │   └── main.cpp
    ├── src/
    │   ├── csr_bridge.h      extern "C" bridge into Assignment 01's csr.c/csr.h
    │   ├── bellman_ford.h / .cpp
    │   ├── floyd_warshall.h / .cpp
    │   ├── triangle_counting.h / .cpp
    │   ├── betweenness_centrality.h / .cpp
    │   └── connected_components.h / .cpp
    ├── tools/
    │   ├── graph_generator.cpp   random test-file generator
    │   └── cross_check.cpp       Bellman-Ford vs Floyd-Warshall verifier
    ├── tests/
    │   ├── bf_*.txt, fw_*.txt
    │   └── tc_*.txt, bc_*.txt, cc_*.txt
    └── outputs/             (created automatically when the wrapper runs)
```

## Common Wrapper: Build and Usage

**Assignment 01**

```
cd common_wrapper
gcc -o wrapper wrapper.c
./wrapper
```

```
1. Compile            -> builds Assignment__01/driver/main
2. Run BFS test        -> runs bfs.txt then bfs2.txt
3. Run DFS test        -> runs dfs.txt then dfs2.txt
4. Run SSSP test       -> runs sssp.txt then sssp2.txt
5. Run all tests
0. Exit
```

**Assignment 02**

```
cd common_wrapper
g++ -std=c++17 -o wrapper2 wrapper2.cpp
./wrapper2
```

```
1. Compile                        -> builds Assignment__02/driver/main
2. Run Bellman-Ford tests          -> all 5 required sizes
3. Run Floyd-Warshall tests        -> all 5 required sizes
4. Run Triangle Counting tests     -> all 5 required sizes
5. Run Betweenness Centrality tests -> all 5 required sizes
6. Run Connected Components tests  -> all 5 required sizes
7. Run all tests
0. Exit
```

Every run also gets written to `Assignment__0N/outputs/<name>.out`, in
addition to printing on screen.
