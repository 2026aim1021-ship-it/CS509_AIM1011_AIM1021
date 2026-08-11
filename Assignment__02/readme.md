# Assignment 02 - Graph Algorithms (Betweenness Centrality / Connected Components / Triangle Counting)

### Assignment Mode

Double (Pair)

### Objective

Read an unweighted, undirected graph from a text file, build it into a
CSR (Compressed Sparse Row) structure using Assignment 1's loader, and
compute Betweenness Centrality, Connected Components, and Triangle
Counting on it. BFS and DFS from Assignment 1 are reused internally
rather than re-implemented.

### Algorithm / Approach

- **Betweenness Centrality** — Brandes' algorithm. For every vertex as
  source, Assignment 1's `bfs()` gives discovery order and distances.
  Predecessors are then reconstructed from those distances (`u` is a
  predecessor of `v` when `dist[v] == dist[u] + 1`), shortest-path
  counts (`sigma`) are accumulated during that same pass, and
  dependency scores are accumulated back-to-front over the BFS order.
  Because the graph is undirected, every unordered pair is counted
  twice (once from each endpoint as source), so the final centrality
  values are divided by 2. Values are left unnormalized, as required.
- **Connected Components** — for every undiscovered vertex, Assignment
  1's `dfs()` is run once; every vertex it reaches is stamped with the
  current component id. This repeats until all vertices are labelled.
- **Triangle Counting** — each vertex's adjacency list (`col_idx`
  slice) is sorted, then for every pair of neighbours `(v, w)` of a
  vertex `u`, a binary search checks whether the edge `v-w` also
  exists. Each triangle is found 3 times (once from each of its
  vertices), so the raw count is divided by 3. When the graph has
  ≤ 100 vertices, the actual triangle vertex-triples are also
  collected (deduplicated via a `set`) and printed.

### Input Format

Same unweighted adjacency format as Assignment 1's BFS/DFS (no
trailing `source` line, since these algorithms run over all
vertices rather than a single source):

```
<V> <E>
<vertex> <degree> <neighbour_1> <neighbour_2> ...   (one line per vertex)
...
```

### Helper Functions / CSR Conversion

- `read_unweighted_graph` and `adjacency_list_to_csr` (Assignment 1's
  `src/csr.c`) parse the input file and build the CSR graph — this
  happens before the algorithm runs and is not counted in the timed
  section.
- `bfs()` / `dfs()` (Assignment 1's `src/bfs.c` / `src/dfs.c`) are
  called internally by Betweenness Centrality and Connected
  Components respectively, via an `extern "C"` bridge in each
  header.

### File Structure

- `src/betweenness.cpp`, `src/betweenness.hpp` — Betweenness Centrality
- `src/connectedComponents.cpp`, `src/connectedComponents.hpp` — Connected Components
- `src/triangleCounting.cpp`, `src/triangleCounting.hpp` — Triangle Counting
- `driver/main.cpp` — interactive menu: pick an algorithm, enter an
  input file path, see the result and execution time
- `tests/` — `bc_*.txt`, `cc_*.txt`, `tc_*.txt` input graphs at sizes
  10/100/1000/5000/10000 (plus `tc_50000.txt`, `tc_100000.txt`,
  `tc_sample.txt`)
- `outputs/` — saved run results, `<name>.out` per test file

### Compilation

```
gcc -I Assignment__01/src -c Assignment__01/src/graph.c -o /tmp/a1_graph.o
gcc -I Assignment__01/src -c Assignment__01/src/csr.c   -o /tmp/a1_csr.o
gcc -I Assignment__01/src -c Assignment__01/src/bfs.c   -o /tmp/a1_bfs.o
gcc -I Assignment__01/src -c Assignment__01/src/dfs.c   -o /tmp/a1_dfs.o

g++ -std=c++17 -I Assignment__01/src \
    Assignment__02/driver/main.cpp \
    Assignment__02/src/betweenness.cpp \
    Assignment__02/src/connectedComponents.cpp \
    Assignment__02/src/triangleCounting.cpp \
    /tmp/a1_graph.o /tmp/a1_csr.o /tmp/a1_bfs.o /tmp/a1_dfs.o \
    -o Assignment__02/driver/main
```

Or use the shared wrapper — `common_wrapper.cpp` at the repo root
(option 2, "Evaluate Assignment 2") runs exactly these steps and then
launches the driver. See the root `README.md`.

### Execution

```
./Assignment__02/driver/main
```

Then, per run: pick `1` (Betweenness Centrality), `2` (Connected
Components), or `3` (Triangle Counting), and enter an input file path,
e.g. `Assignment__02/tests/bc_1000.txt`. Choose `4` to exit.

### Test Cases and Result Table

| Algorithm              | Test File       | V     | E      | Result                                   | Execution Time |
|-------------------------|------------------|-------|--------|-------------------------------------------|-----------------|
| Betweenness Centrality  | bc_10.txt        | 10    | 9      | All centrality values 0.00 (three disjoint triangles + 1 isolated vertex) | 0.028 ms        |
| Betweenness Centrality  | bc_100.txt       | 100   | 250    | Full per-vertex centrality listing        | 1.658 ms        |
| Betweenness Centrality  | bc_1000.txt      | 1000  | 2500   | Full per-vertex centrality listing        | 152.468 ms      |
| Betweenness Centrality  | bc_5000.txt      | 5000  | 12500  | Full per-vertex centrality listing        | 3516.382 ms     |
| Betweenness Centrality  | bc_10000.txt     | 10000 | 25000  | Full per-vertex centrality listing        | 20169.267 ms    |
| Connected Components    | cc_10.txt        | 10    | 9      | 4 components (matches 3 triangles + 1 isolated vertex) | 0.005 ms |
| Connected Components    | cc_100.txt       | 100   | 200    | Component id per vertex                   | 0.010 ms        |
| Connected Components    | cc_1000.txt      | 1000  | 2000   | Component id per vertex                   | 0.055 ms        |
| Connected Components    | cc_5000.txt      | 5000  | 10000  | Component id per vertex                   | 0.270 ms        |
| Connected Components    | cc_10000.txt     | 10000 | 20000  | Component id per vertex                   | 0.516 ms        |
| Triangle Counting       | tc_sample.txt    | 6     | 8      | 3 triangles: (0,1,2), (1,2,3), (3,4,5)    | 0.008 ms        |
| Triangle Counting       | tc_100.txt       | 100   | 300    | Total triangle count                      | 0.074 ms        |
| Triangle Counting       | tc_10000.txt     | 10000 | 40000  | Total triangle count                      | 6.547 ms        |
| Triangle Counting       | tc_50000.txt     | 50000 | 200000 | Total triangle count                      | 47.814 ms       |
| Triangle Counting       | tc_100000.txt    | 100000| 400000 | Total triangle count                      | 105.203 ms      |

Full per-vertex/per-component listings and triangle lists are saved
in `outputs/` (`bc_*.out`, `cc_*.out`, `tc_*.out`) after running the
driver.

Betweenness Centrality was spot-checked against `bc_10.txt`: the graph
is three disjoint triangles plus one isolated vertex, so every pair is
directly adjacent and no vertex sits on a shortest path between two
others — centrality 0.00 everywhere is the correct result. Connected
Components was spot-checked against `cc_10.txt`: it correctly reports
4 components matching the graph's structure.

Timings above were measured on the dev machine and will vary run to
run — they cover only the algorithm call, not file reading or CSR
conversion.

### Complexity

| Algorithm               | Time                | Space   |
|---------------------------|--------------------|---------|
| Betweenness Centrality (Brandes) | O(V · (V + E))     | O(V + E) |
| Connected Components (DFS-based) | O(V + E)           | O(V)     |
| Triangle Counting (sort + binary search) | O(E · Δ · log Δ) (Δ = max degree) | O(V + E) |

Betweenness Centrality's O(V · (V + E)) cost is visible in the result
table above: it dominates runtime at every size, since it runs a full
BFS from every vertex plus O(V) predecessor/dependency bookkeeping per
BFS — for `bc_10000.txt` (V = 10000) this means 10000 separate BFS
passes over a 25000-edge graph.

### References

- CLRS (Cormen, Leiserson, Rivest, Stein) — *Introduction to
  Algorithms*, chapters on graph traversal, used as the general
  reference for BFS/DFS reuse.
- U. Brandes, "A Faster Algorithm for Betweenness Centrality,"
  *Journal of Mathematical Sociology*, 2001 — the algorithm used for
  Betweenness Centrality.
