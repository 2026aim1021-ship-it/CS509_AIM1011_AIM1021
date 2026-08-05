# Assignment 01 - Graph Algorithms (BFS / DFS / SSSP)

### Assignment Mode

Double (Pair)

### Objective

Read a graph from a text file, build it into a CSR (Compressed Sparse
Row) structure, and run BFS, DFS, and Dijkstra's shortest path on it.

### Algorithm / Approach

- **BFS** — standard queue-based traversal from the source over the CSR
  adjacency. Distance to every vertex is tracked; unreached vertices are
  left at `-1`.
- **DFS** — traversal over the CSR adjacency using an explicit stack,
  visiting neighbours in `col_idx` order.
- **SSSP (Dijkstra)** — array-based Dijkstra: at every step it scans all
  unvisited vertices for the minimum tentative distance, then relaxes
  its out-edges. Unreachable vertices stay at `INF`.

### Input Format

**BFS / DFS (unweighted)**

```
<V> <E>
<vertex> <degree> <neighbour_1> <neighbour_2> ...   (one line per vertex)
...
source <source_vertex>
```

**SSSP (weighted)**

```
<V> <E>
<edge_from> <edge_to>     (E lines)
<weight>                  (E lines, one per edge above)
<source_vertex>
```

### Helper Functions / CSR Conversion

- `read_unweighted_graph` / `read_weighted_graph` (`src/csr.c`) parse the
  input file into an `adjacency_list`.
- `adjacency_list_to_csr` converts that into a `csr_graph` (`row_ptr`,
  `col_idx`, `values`) — this conversion happens before BFS/DFS start and
  is not counted in the timed section.
- SSSP keeps its own fixed-size CSR arrays (`idx`, `nei`, `val`), built by
  `makeCSR()` in `src/sssp.c`.

### File Structure

- `src/csr.c`, `src/csr.h` — graph loading + CSR conversion
- `src/bfs.c` — BFS
- `src/dfs.c` — DFS
- `src/sssp.c`, `src/sssp.h` — Dijkstra
- `src/graph.c`, `src/graph.h` — result structs, legacy linked-list loader
- `driver/main.c` — picks the algorithm based on `argv[1]` and runs it

### Compilation

```
gcc -Wall -Wextra -o driver/main driver/main.c src/csr.c src/bfs.c src/dfs.c src/sssp.c src/graph.c
```

Or use the shared wrapper (`common_wrapper/wrapper.c` — option 1 compiles,
options 2-5 run the tests). See the root `README.md` for the full menu.

### Execution

```
./driver/main 1 tests/bfs.txt     # BFS
./driver/main 2 tests/dfs.txt     # DFS
./driver/main 3 tests/sssp.txt    # SSSP
```

### Test Cases and Result Table

| Mode   | Test File   | Input Type            | Input Size      | Expected Output                                              | Actual Output                                                | Algorithm Time |
|--------|-------------|------------------------|------------------|----------------------------------------------------------------|-----------------------------------------------------------------|-----------------|
| Double | bfs.txt     | Adjacency list          | V = 5, E = 5     | Traversal 0 1 2 3 4, dist 0 1 1 2 3                              | Traversal 0 1 2 3 4, dist 0 1 1 2 3                              | 0.001 ms        |
| Double | bfs2.txt    | Adjacency list          | V = 100, E = 158 | Vertices 0-98 all reached, vertex 99 unreachable (dist -1)      | Vertices 0-98 all reached, vertex 99 dist -1 (matches)           | 0.003 ms        |
| Double | dfs.txt     | Adjacency list          | V = 5, E = 5     | Traversal 0 1 3 4 2                                              | Traversal 0 1 3 4 2                                              | 0.001 ms        |
| Double | dfs2.txt    | Adjacency list          | V = 100, E = 158 | All 99 reachable vertices visited exactly once, vertex 99 skipped | All 99 reachable vertices visited exactly once, vertex 99 skipped | 0.009 ms        |
| Double | sssp.txt    | Weighted edge list      | V = 5, E = 6     | dist 0 3 1 4 7                                                   | dist 0 3 1 4 7                                                   | 0.003 ms        |
| Double | sssp2.txt   | Weighted edge list      | V = 100, E = 100 | Vertices 0-98 have finite distances, vertex 99 = INF             | Vertices 0-98 finite (e.g. dist[1]=2, dist[98]=23), vertex 99 = INF | 0.059 ms        |

Full traversal/distance listings for the size-100 runs are saved in
`outputs/` after running the wrapper.

Timings above were measured on the dev machine and will vary a little
run to run — they cover only the algorithm call, not file reading or
CSR conversion.

### Complexity

| Algorithm | Time         | Space |
|-----------|--------------|-------|
| BFS       | O(V + E)     | O(V)  |
| DFS       | O(V + E)     | O(V)  |
| Dijkstra (array-based) | O(V^2 + E) | O(V) |

The Dijkstra implementation here picks the minimum-distance vertex with
a linear scan each round instead of a heap, so it's O(V²) rather than
O(E log V).

### References

- CLRS (Cormen, Leiserson, Rivest, Stein) — *Introduction to
  Algorithms*, chapters on graph traversal and single-source shortest
  paths, used as the general reference for BFS/DFS/Dijkstra.
