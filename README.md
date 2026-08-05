# CS509 Laboratory Repository

## Repository Overview

This repo holds our CS509 lab work. Right now it has one assignment —
graph algorithms (BFS, DFS, Dijkstra's SSSP) implemented in C over a
CSR-based graph representation, run through a common menu-driven wrapper.
Each assignment folder has its own `readme.md` with the algorithm
details, test cases, and results — see `Assignment__01/readme.md`.

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
│   └── wrapper.c
└── Assignment__01/
    ├── readme.md
    ├── driver/
    │   └── main.c
    ├── src/
    │   ├── csr.c / csr.h
    │   ├── bfs.c
    │   ├── dfs.c
    │   ├── sssp.c / sssp.h
    │   └── graph.c / graph.h
    ├── tests/
    │   ├── bfs.txt, bfs2.txt
    │   ├── dfs.txt, dfs2.txt
    │   └── sssp.txt, sssp2.txt
    └── outputs/          (created automatically when the wrapper runs)
```

## Common Wrapper: Build and Usage

```
cd common_wrapper
gcc -o wrapper wrapper.c
./wrapper
```

Menu:

```
1. Compile            -> builds Assignment__01/driver/main
2. Run BFS test        -> runs bfs.txt then bfs2.txt
3. Run DFS test        -> runs dfs.txt then dfs2.txt
4. Run SSSP test       -> runs sssp.txt then sssp2.txt
5. Run all tests
0. Exit
```

Every run also gets written to `Assignment__01/outputs/<name>.out`, in
addition to printing on screen.
