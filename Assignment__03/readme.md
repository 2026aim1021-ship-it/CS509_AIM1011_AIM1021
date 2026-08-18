# Assignment 03 - Buddy Task (Gradient Descent / Maxflow-Mincut)

### Assignment Mode

Double (Pair) — Buddy task

### Status

- **Maxflow-Mincut** — implemented and verified below.
- **Gradient Descent** — pending; being implemented by the other half of
  the pair. `driver/main.cpp` already reserves menu option `1` for it
  (see the `NOTE` comment at the top of that file) so wiring it in later
  is a small addition, not a restructure.

### Objective (Maxflow-Mincut)

Read a directed, capacitated graph from a text file as an adjacency
list, convert it to CSR with Assignment 1's `adjacency_list_to_csr()`,
then compute the maximum flow and minimum cut between a given source and
sink with Dinic's algorithm.

### Algorithm / Approach

**Maxflow-Mincut** — Dinic's algorithm. `maxflow_mincut()` builds a
fresh residual network (paired forward/reverse edges, `id ^ 1` gives the
matching reverse edge) from the CSR's `row_ptr`/`col_idx`/`values`, then
repeats BFS level-graph construction + blocking-flow DFS (with a
current-arc pointer per vertex, so exhausted edges are never re-scanned
within a phase) until the sink is unreachable. After the flow is
maximal, a BFS from the source over edges with remaining capacity > 0
finds the source-side vertex set; the complement is the sink side. Cut
edges are the original CSR edges crossing from the source side to the
sink side — their capacities sum to the minimum cut, which always
equals the maximum flow value (verified below).

**Reference:** MIT OCW 6.046J, "Incremental Improvement: Max Flow, Min
Cut" —
https://ocw.mit.edu/courses/6-046j-design-and-analysis-of-algorithms-spring-2015/resources/lecture-13-incremental-improvement-max-flow-min-cut/

### Input Format (Section 7.1)

Directed capacity adjacency list:

```
V E
u0 degree neighbor1 capacity1 neighbor2 capacity2 ...
...
u(V-1) degree neighbor1 capacity1 ...
SOURCE s
SINK t
```

### Helper Functions / CSR Conversion

`read_maxflow_input()` (`src/maxflowMincut.cpp`) parses the file above
into an `adjacency_list` (the same struct Assignment 1's `csr.h`
defines); the driver then calls Assignment 1's
`adjacency_list_to_csr()` directly — that conversion is **not**
re-implemented here, per the assignment instructions. CSR conversion is
excluded from the timed section. `maxflow_mincut()`'s internal Dinic
residual-network build from the CSR *is* included in the timed call
(Section 8 — "initialization of the residual network from the
already-prepared CSR is part of the max-flow algorithm call").

### File Structure

- `src/maxflowMincut.hpp`, `src/maxflowMincut.cpp` — Maxflow-Mincut (Dinic's algorithm)
- `driver/main.cpp` — interactive menu (option 2 runs Maxflow-Mincut;
  option 1 is reserved for Gradient Descent, pending)
- `tools/generate_maxflow_graph.cpp` — random sparse directed
  capacitated-graph generator used to build the `maxflow_100.txt` /
  `maxflow_1000.txt` / `maxflow_10000.txt` / `maxflow_50000.txt` test
  files (guarantees a source(0)->sink(V-1) path). `maxflow_100000.txt`
  (optional per Section 4.2) was not generated — see note below.
- `tests/` — `maxflow_10.txt` (hand-built) plus `maxflow_100.txt`,
  `maxflow_1000.txt`, `maxflow_10000.txt`, `maxflow_50000.txt`
  (generated with the tool above, seed 42, E ≈ 3V) — all 5 required
  sizes from Section 4.2.
- `outputs/` — saved run results, `<name>.out` per test file, for all 5
  required sizes.

### Compilation

```
gcc -I Assignment__01/src -c Assignment__01/src/csr.c -o /tmp/a1_csr.o

g++ -std=c++17 -O2 \
    Assignment__03/driver/main.cpp \
    Assignment__03/src/maxflowMincut.cpp \
    /tmp/a1_csr.o \
    -o Assignment__03/driver/main
```

Once Gradient Descent's `src/gradientDescent.hpp`/`.cpp` are added, add
them to this command (and to `driver/main.cpp`'s option 1) the same way
Assignment 2 lists its algorithm `.cpp` files.

### Execution

```
./Assignment__03/driver/main
```

Pick `2` (Maxflow-Mincut), enter an input file path (e.g.
`Assignment__03/tests/maxflow_10.txt`), and read the result. Choose `3`
to exit. Option `1` (Gradient Descent) currently prints a "not wired in
yet" message.

### Test Cases and Result Table

All 5 required sizes (Section 4.2) generated and run; on every one,
Maximum Flow equals Minimum Cut Capacity, which is Dinic's correctness
guarantee — a mismatch would mean a bug:

| File                | V     | E      | Source | Sink  | Max Flow | Cut Capacity | Time        | Status |
|---------------------|-------|--------|--------|-------|----------|--------------|-------------|--------|
| maxflow_10.txt      | 10    | 17     | 0      | 9     | 15       | 15           | 0.010 ms    | Pass   |
| maxflow_100.txt     | 100   | 300    | 0      | 99    | 1510     | 1510         | 0.105 ms    | Pass   |
| maxflow_1000.txt    | 1000  | 3000   | 0      | 999   | 1136     | 1136         | 5.502 ms    | Pass   |
| maxflow_10000.txt   | 10000 | 30000  | 0      | 9999  | 579      | 579          | 189.198 ms  | Pass   |
| maxflow_50000.txt   | 50000 | 150000 | 0      | 49999 | 394      | 394          | 1804.012 ms | Pass   |

`maxflow_100.txt`/`_1000.txt`/`_10000.txt`/`_50000.txt` were generated
with `tools/generate_maxflow_graph.cpp` (seed 42, E ≈ 3V, keeping E
within the "approximately 2V to 4V" sparsity guidance from Section 4.2).
Timings above were measured on the dev machine (single run each,
CLOCKS_PER_SEC-based `clock()` timing per Section 8) and will vary on
your machine — re-run if you want your own numbers for the report; note
in the report if you average repeated runs, per Section 8's guidance
for very fast inputs.

`maxflow_100000.txt` (optional per Section 4.2) was not generated —
mention in the report if you skip it, per Section 4.2's "document E" /
"record the observed behavior" guidance for optional/large cases.

Input validation was also spot-checked: malformed adjacency lines
(including a vertex id outside `[0, V)`, which would otherwise corrupt
memory rather than fail cleanly), negative capacities, and
`SOURCE == SINK` are all rejected with a clear error message instead of
crashing.

### Complexity

| Algorithm                          | Time      | Space    |
|-------------------------------------|-----------|----------|
| Maxflow-Mincut (Dinic's algorithm)  | O(V² · E) | O(V + E) |

Dinic's O(V² · E) bound is the standard general-graph guarantee; on
sparse test graphs (few BFS phases, short augmenting paths) observed
runtime is well below that worst case.

### References

- MIT OpenCourseWare 6.046J — Design and Analysis of Algorithms,
  "Incremental Improvement: Max Flow, Min Cut."
