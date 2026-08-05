# Assignment 01 — Graph Algorithms (BFS / DFS / SSSP)

## Layout

- `src/csr.h`, `src/csr.c` — adjacency-list graph loading (`read_unweighted_graph`,
  `read_weighted_graph`) and conversion to CSR (`adjacency_list_to_csr`).
- `src/bfs.c`, `src/dfs.c` — BFS/DFS over a `csr_graph`, each returning a result
  struct (`bfs_result` / `dfs_result`, declared in `src/graph.h`).
- `src/sssp.c`, `src/sssp.h` — Dijkstra's algorithm on its own fixed-size CSR
  arrays. Has an optional standalone `main()` guarded by `SSSP_STANDALONE_MAIN`.
- `src/graph.c`, `src/graph.h` — legacy linked-list graph loader
  (`read_graph`, `read_graph_weighted`, `free_graph`); not used by the driver,
  kept buildable.
- `driver/main.c` — unified entry point: `driver_prog <choice> <inputfile>`.
- `tests/` — sample input files (`bfs.txt`, `dfs.txt`, `sssp.txt`).

## Build & run

Use the shared `common_wrapper/wrapper.c` menu (option 2 = Graph Algorithms
Assignment):

```
cd ../common_wrapper
gcc -o wrapper wrapper.c
./wrapper
# 2  -> Graph Algorithms Assignment
# 1  -> Compile
# 2/3/4 -> Run BFS / DFS / SSSP
# 5  -> Run all three
# 0  -> Exit
```

Or build and run manually:

```
gcc -Wall -Wextra -o driver/main driver/main.c src/csr.c src/bfs.c src/dfs.c src/sssp.c src/graph.c
./driver/main 1 tests/bfs.txt    # BFS
./driver/main 2 tests/dfs.txt    # DFS
./driver/main 3 tests/sssp.txt   # SSSP (Dijkstra)
```

Each mode prints the algorithm name, source vertex, traversal/distances, and
execution time in milliseconds.

## Input format

**Unweighted (BFS/DFS)** — `tests/bfs.txt`, `tests/dfs.txt`:

```
<V> <E>
<vertex> <degree> <neighbour_1> <neighbour_2> ...   (one line per vertex, 0..V-1)
...
source <source_vertex>
```

`E` and the sum of all `<degree>` values must match — `adjacency_list_to_csr`
sizes its buffers off the actual degree sum, but a mismatched `E` in the
header still indicates a malformed file.

**SSSP** — `tests/sssp.txt` (consumed by `src/sssp.c`):

```
<V> <E>
<edge_from> <edge_to>     (E lines)
<weight>                  (E lines, one per edge above)
<source_vertex>
```
