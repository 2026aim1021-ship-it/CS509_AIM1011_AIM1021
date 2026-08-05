CS509 LABORATORY REPOSITORY
============================

1. REPOSITORY OVERVIEW
-----------------------
This repo holds our CS509 lab work. Right now it has one assignment -
graph algorithms (BFS, DFS, Dijkstra's SSSP) implemented in C over a
CSR-based graph representation, run through a common menu-driven wrapper.

2. STUDENT / PAIR DETAILS
--------------------------
Mode: Double (Pair)

- Shivank Shubanshi - 2026AIM1021
- Aman Kumar - 2026AIM1011

3. LANGUAGE AND ENVIRONMENT
-----------------------------
- Language: C
- Compiler: gcc, built with -Wall -Wextra
- Shell: bash (Git Bash / WSL / Linux terminal)

4. DIRECTORY STRUCTURE
------------------------
CS509_AIM1011_AIM1021/
  README.md / README.txt
  common_wrapper/
    wrapper.c
  Assignment__01/
    readme.md
    driver/
      main.c
    src/
      csr.c / csr.h
      bfs.c
      dfs.c
      sssp.c / sssp.h
      graph.c / graph.h
    tests/
      bfs.txt, bfs2.txt
      dfs.txt, dfs2.txt
      sssp.txt, sssp2.txt
    outputs/          (created automatically when the wrapper runs)

5. COMMON WRAPPER: BUILD AND USAGE
------------------------------------
    cd common_wrapper
    gcc -o wrapper wrapper.c
    ./wrapper

Menu:
    1. Compile          -> builds Assignment__01/driver/main
    2. Run BFS test      -> runs bfs.txt then bfs2.txt
    3. Run DFS test      -> runs dfs.txt then dfs2.txt
    4. Run SSSP test     -> runs sssp.txt then sssp2.txt
    5. Run all tests
    0. Exit

Every run also gets written to Assignment__01/outputs/<name>.out, in
addition to printing on screen.

============================================================

ASSIGNMENT 01 - GRAPH ALGORITHMS (BFS / DFS / SSSP)
======================================================

ASSIGNMENT MODE
----------------
Double (Pair)

OBJECTIVE
----------
Read a graph from a text file, build it into a CSR (Compressed Sparse
Row) structure, and run BFS, DFS, and Dijkstra's shortest path on it.

ALGORITHM / APPROACH
----------------------
- BFS - standard queue-based traversal from the source over the CSR
  adjacency. Distance to every vertex is tracked; unreached vertices
  are left at -1.
- DFS - traversal over the CSR adjacency using an explicit stack,
  visiting neighbours in col_idx order.
- SSSP (Dijkstra) - array-based Dijkstra: at every step it scans all
  unvisited vertices for the minimum tentative distance, then relaxes
  its out-edges. Unreachable vertices stay at INF.

INPUT FORMAT
-------------
BFS / DFS (unweighted):
    <V> <E>
    <vertex> <degree> <neighbour_1> <neighbour_2> ...   (one line per vertex)
    ...
    source <source_vertex>

SSSP (weighted):
    <V> <E>
    <edge_from> <edge_to>     (E lines)
    <weight>                  (E lines, one per edge above)
    <source_vertex>

HELPER FUNCTIONS / CSR CONVERSION
------------------------------------
- read_unweighted_graph / read_weighted_graph (src/csr.c) parse the
  input file into an adjacency_list.
- adjacency_list_to_csr converts that into a csr_graph (row_ptr,
  col_idx, values) - this conversion happens before BFS/DFS start and
  is not counted in the timed section.
- SSSP keeps its own fixed-size CSR arrays (idx, nei, val), built by
  makeCSR() in src/sssp.c.

FILE STRUCTURE
----------------
- src/csr.c, src/csr.h    - graph loading + CSR conversion
- src/bfs.c               - BFS
- src/dfs.c               - DFS
- src/sssp.c, src/sssp.h  - Dijkstra
- src/graph.c, src/graph.h - result structs, legacy linked-list loader
- driver/main.c           - picks the algorithm based on argv[1] and runs it

COMPILATION
------------
    gcc -Wall -Wextra -o driver/main driver/main.c src/csr.c src/bfs.c src/dfs.c src/sssp.c src/graph.c

EXECUTION
----------
    ./driver/main 1 tests/bfs.txt     (BFS)
    ./driver/main 2 tests/dfs.txt     (DFS)
    ./driver/main 3 tests/sssp.txt    (SSSP)

TEST CASES AND RESULT TABLE
------------------------------

Mode   | Test File | Input Type       | Input Size       | Expected Output
-------|-----------|------------------|-------------------|-----------------------------------------------------------
Double | bfs.txt   | Adjacency list   | V = 5, E = 5      | Traversal 0 1 2 3 4, dist 0 1 1 2 3
Double | bfs2.txt  | Adjacency list   | V = 100, E = 158  | Vertices 0-98 all reached, vertex 99 unreachable (dist -1)
Double | dfs.txt   | Adjacency list   | V = 5, E = 5      | Traversal 0 1 3 4 2
Double | dfs2.txt  | Adjacency list   | V = 100, E = 158  | All 99 reachable vertices visited exactly once, vertex 99 skipped
Double | sssp.txt  | Weighted edges   | V = 5, E = 6      | dist 0 3 1 4 7
Double | sssp2.txt | Weighted edges   | V = 100, E = 100  | Vertices 0-98 have finite distances, vertex 99 = INF

Continued (Actual Output / Algorithm Time):

Test File  | Actual Output                                                        | Algorithm Time
-----------|-----------------------------------------------------------------------|-----------------
bfs.txt    | Traversal 0 1 2 3 4, dist 0 1 1 2 3                                     | 0.001 ms
bfs2.txt   | Vertices 0-98 all reached, vertex 99 dist -1 (matches)                  | 0.003 ms
dfs.txt    | Traversal 0 1 3 4 2                                                     | 0.001 ms
dfs2.txt   | All 99 reachable vertices visited exactly once, vertex 99 skipped      | 0.009 ms
sssp.txt   | dist 0 3 1 4 7                                                          | 0.003 ms
sssp2.txt  | Vertices 0-98 finite (e.g. dist[1]=2, dist[98]=23), vertex 99 = INF     | 0.059 ms

Full traversal/distance listings for the size-100 runs are saved in
Assignment__01/outputs/ after running the wrapper.

Timings above were measured on the dev machine and will vary a little
run to run - they cover only the algorithm call, not file reading or
CSR conversion.

COMPLEXITY
-----------

Algorithm               | Time         | Space
-------------------------|--------------|-------
BFS                      | O(V + E)     | O(V)
DFS                      | O(V + E)     | O(V)
Dijkstra (array-based)   | O(V^2 + E)   | O(V)

The Dijkstra implementation here picks the minimum-distance vertex with
a linear scan each round instead of a heap, so it's O(V^2) rather than
O(E log V).

REFERENCES
-----------
- CLRS (Cormen, Leiserson, Rivest, Stein) - Introduction to Algorithms,
  chapters on graph traversal and single-source shortest paths, used as
  the general reference for BFS/DFS/Dijkstra.
