# Assignment 03

## Assignment Mode

**Double (Pair) — Buddy Task**

- Shivank Shubanshi — 2026AIM1021
- Aman Kumar — 2026AIM1011

---

## 1. Scope of This Assignment

This repository implements **only the two Assignment 3 buddy tasks**:

1. **Gradient Descent**
2. **Maxflow-Mincut**

The Assignment 3 specification separately identifies MST (Kruskal and Prim) as an **individual task**, while Gradient Descent and Maxflow-Mincut are explicitly the **buddy tasks for a pair of two students**. Therefore, MST is intentionally not documented or included as part of this Assignment 03 buddy-task implementation. fileciteturn1file0L8-L21

The required language may be C or C++, with C++ preferred. fileciteturn1file0L16-L21

---

# 2. Gradient Descent

## Objective

Gradient Descent is an iterative optimization algorithm that updates the current value of `x` in the direction that decreases the objective function.

For this assignment, the objective is a generic one-variable polynomial:

```text
f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d
```

Its derivative is:

```text
f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ... + d*cd*x^(d-1)
```

The update rule is:

```text
x_new = x - learning_rate * f'(x)
```

These are the exact mathematical requirements given in the Assignment 3 specification. fileciteturn1file0L62-L72

## Implementation

`src/gradientdescent.cpp` provides a generic implementation that:

- Reads the degree and coefficient vector from the input file.
- Supports all required polynomial degrees using the same implementation.
- Evaluates the polynomial.
- Evaluates its derivative.
- Performs the Gradient Descent update.
- Stops according to the required derivative tolerance or maximum iteration count.
- Reports the final optimization values through the driver.

The implementation does **not** hard-code five different objective functions. fileciteturn1file0L70-L80

The implementation evaluates the polynomial and derivative using Horner-style evaluation, avoiding repeated explicit power calculations.

---

# 3. Gradient Descent Input Format

Each test case is a separate `.txt` file.

```text
DEGREE d
COEFFICIENTS c0 c1 c2 ... cd
INITIAL_X x0
LEARNING_RATE alpha
TOLERANCE epsilon
MAX_ITERATIONS n
```

The coefficient list must contain exactly `d + 1` values in ascending power order:

```text
c0, c1, c2, ..., cd
```

The specification explicitly states that the constant coefficient comes first and the coefficient of `x^d` comes last. fileciteturn1file0L253-L270

### Example

```text
DEGREE 6
COEFFICIENTS 0 0 1 0 0.5 0 0.1
INITIAL_X 2
LEARNING_RATE 0.02
TOLERANCE 0.000001
MAX_ITERATIONS 20000
```

This represents:

```text
f(x) = x^2 + 0.5x^4 + 0.1x^6
```

which is the example specified in the assignment document. fileciteturn1file0L272-L278

---

# 4. Gradient Descent Stopping Rule

At each iteration:

```text
calculate f'(x)
```

If:

```text
|f'(x)| <= tolerance
```

the algorithm has converged.

Otherwise:

```text
x = x - learning_rate * f'(x)
```

and the iteration continues until `MAX_ITERATIONS` is reached.

The specification requires this exact stopping rule. fileciteturn1file0L264-L270

---

# 5. Gradient Descent Output

The driver reports:

```text
Algorithm: Gradient Descent
Degree: <degree>
Final x: <value>
Final f(x): <value>
Iterations: <value>
Converged: true/false
Execution time: <value> ms
```

These are the required output fields in Section 6.3 of the assignment. fileciteturn1file0L281-L291

If convergence is not achieved before `MAX_ITERATIONS`, the driver must still print the final values and:

```text
Converged: false
```

---

# 6. Required Gradient Descent Test Cases

The assignment requires five tests with polynomial degrees 2, 4, 6, 8, and 10. fileciteturn1file0L167-L203

| File | Degree | Objective Function | Initial x | Rate | Tolerance | Max Iterations | Expected x* |
|---|---:|---|---:|---:|---:|---:|---:|
| `gd_01.txt` | 2 | `x² - 6x + 9` | 0 | 0.10 | `1e-6` | 5,000 | 3 |
| `gd_02.txt` | 4 | `x⁴ + 2x²` | 2 | 0.02 | `1e-6` | 10,000 | 0 |
| `gd_03.txt` | 6 | `0.1x⁶ + 0.5x⁴ + x²` | 2 | 0.02 | `1e-6` | 20,000 | 0 |
| `gd_04.txt` | 8 | `0.01x⁸ + 0.05x⁶ + 0.2x⁴ + x²` | 2 | 0.01 | `1e-8` | 50,000 | 0 |
| `gd_05.txt` | 10 | `0.002x¹⁰ + 0.01x⁸ + 0.05x⁶ + 0.2x⁴ + x²` | 2 | 0.005 | `1e-10` | 100,000 | 0 |

Coefficients not explicitly present in these functions are zero. All five required objective functions are convex with a single global minimum. fileciteturn1file0L183-L200

---

# 7. Gradient Descent Verification

The current implementation was compiled and run against all five required files.

| File | Degree | Final x | Final f(x) | Iterations | Converged | Execution Time* |
|---|---:|---:|---:|---:|---|---:|
| `gd_01.txt` | 2 | 2.9999995063 | 0.0000000000 | 70 | true | 0.008 ms |
| `gd_02.txt` | 4 | 0.0000002379 | 0.0000000000 | 180 | true | 0.024 ms |
| `gd_03.txt` | 6 | 0.0000004835 | 0.0000000000 | 349 | true | 0.039 ms |
| `gd_04.txt` | 8 | 0.0000000050 | 0.0000000000 | 948 | true | 0.129 ms |
| `gd_05.txt` | 10 | 0.0000000000 | 0.0000000000 | 2,364 | true | 0.351 ms |


All five tests converge toward their specified expected minima.

---

# 8. Gradient Descent Validation

The implementation rejects invalid input including:

- Invalid degree.
- A coefficient count different from `d + 1`.
- Non-positive learning rate.
- Non-positive tolerance.
- Non-positive `MAX_ITERATIONS`.

These are minimum validation requirements stated in the assignment. fileciteturn1file0L425-L439

---

# 9. Maxflow-Mincut

## Objective

The Maxflow problem finds the maximum amount of flow that can be sent from source `s` to sink `t` without exceeding edge capacities.

The corresponding minimum cut partitions the vertices into source and sink sides, with minimum total capacity crossing from the source side to the sink side. fileciteturn1file0L91-L100

The implementation uses **Dinic's algorithm**, which the assignment recommends because the required graph sizes can make slower algorithms impractical. fileciteturn1file0L101-L103

---

# 10. Maxflow-Mincut Algorithm / Approach

The implementation performs the following steps:

1. Read the directed adjacency-list graph.
2. Validate source, sink, vertices, and capacities.
3. Convert the adjacency list to CSR using Assignment 01's helper.
4. Build the residual network internally.
5. Run BFS to create a level graph.
6. Run blocking-flow DFS using a current-arc pointer.
7. Repeat until the sink is no longer reachable in the residual graph.
8. Run a final residual BFS from the source.
9. Treat reachable vertices as the source side of the minimum cut.
10. Treat the remaining vertices as the sink side.
11. Collect original edges crossing the cut and calculate their total capacity.

Reverse residual edges are created internally by the Maxflow implementation; they are not placed in the input files. This matches the assignment requirement. fileciteturn1file0L130-L145

---

# 11. Maxflow-Mincut Input Format

```text
V E
u0 degree neighbor1 capacity1 neighbor2 capacity2 ...
u1 degree neighbor1 capacity1 neighbor2 capacity2 ...
...
u(V-1) degree ...
SOURCE s
SINK t
```

The input contains only original outgoing capacity edges.

Required tests use positive integer capacities. Source and sink must be different valid vertices, and there must be a source-to-sink path. fileciteturn1file0L130-L134

---

# 12. Maxflow-Mincut Required Test Sizes

The required graph sizes are:

```text
10
100
1,000
10,000
50,000
```

A 100,000-vertex test is optional. Large graphs should remain sparse, with approximately `E = 2V` to `4V` where practical. fileciteturn1file0L146-L166

The repository contains the five required files:

```text
tests/maxflow_10.txt
tests/maxflow_100.txt
tests/maxflow_1000.txt
tests/maxflow_10000.txt
tests/maxflow_50000.txt
```

---

# 13. Maxflow-Mincut Verification Results

The existing recorded test results are:

| File | V | E | Source | Sink | Maximum Flow | Cut Capacity | Time | Status |
|---|---:|---:|---:|---:|---:|---:|---:|---|
| `maxflow_10.txt` | 10 | 17 | 0 | 9 | 15 | 15 | 0.010 ms | Pass |
| `maxflow_100.txt` | 100 | 300 | 0 | 99 | 1510 | 1510 | 0.105 ms | Pass |
| `maxflow_1000.txt` | 1,000 | 3,000 | 0 | 999 | 1136 | 1136 | 5.502 ms | Pass |
| `maxflow_10000.txt` | 10,000 | 30,000 | 0 | 9999 | 579 | 579 | 189.198 ms | Pass |
| `maxflow_50000.txt` | 50,000 | 150,000 | 0 | 49999 | 394 | 394 | 1804.012 ms | Pass |

For every recorded test:

```text
Maximum Flow = Minimum Cut Capacity
```

which satisfies the required correctness condition. fileciteturn1file0L96-L100

The optional `maxflow_100000.txt` test is not included.

---

# 14. CSR Reuse

CSR is used for **Maxflow-Mincut**, but not for Gradient Descent.

The required flow is:

```text
Maxflow input file
        ↓
Adjacency list
        ↓
Assignment 01 adjacency_list_to_csr()
        ↓
CSR
        ↓
Maxflow-Mincut
```

The assignment explicitly requires reuse of the previous Assignment's CSR conversion rather than copying the conversion implementation into Assignment 3. fileciteturn1file0L118-L125

Gradient Descent directly reads its scalar parameters and coefficient vector and therefore bypasses CSR. fileciteturn1file0L135-L145

---

# 15. Timing Methodology

The Assignment 3 timing rule is strict:

```text
Start timer
    ↓
Call algorithm
    ↓
Stop timer
```

File reading, input parsing, CSR conversion, setup allocation, output printing, and file writing are excluded. fileciteturn1file0L338-L349

### Gradient Descent

```text
Read + validate input       ← NOT TIMED
        ↓
Start timer
        ↓
Gradient Descent            ← TIMED
        ↓
Stop timer
        ↓
Print result                ← NOT TIMED
```

### Maxflow-Mincut

```text
Read + validate input       ← NOT TIMED
        ↓
Adjacency list → CSR        ← NOT TIMED
        ↓
Start timer
        ↓
Maxflow + residual/cut work ← TIMED
        ↓
Stop timer
        ↓
Print result                ← NOT TIMED
```

For Maxflow-Mincut, residual-network initialization from the prepared CSR and minimum-cut extraction are explicitly part of the measured algorithm section. fileciteturn1file0L350-L356

---

# 16. Driver Behaviour

The Assignment 3 driver provides:

```text
==============================
   ASSIGNMENT 3 - BUDDY TASK
==============================
1. Gradient Descent
2. Maxflow-Mincut
3. Exit
```

For either algorithm, the driver asks for the input-file path, validates the input, calls the algorithm, and prints the required result and execution time.

This matches the minimum expected driver behaviour specified for Assignment 3. fileciteturn1file0L425-L436

---

# 17. File Structure

```text
Assignment__03/
├── driver/
│   ├── main.cpp
│   └── main
│
├── src/
│   ├── gradientdescent.cpp
│   ├── maxflowMincut.cpp
│   └── maxflowMincut.hpp
│
├── tests/
│   ├── gd_01.txt
│   ├── gd_02.txt
│   ├── gd_03.txt
│   ├── gd_04.txt
│   ├── gd_05.txt
│   ├── maxflow_10.txt
│   ├── maxflow_100.txt
│   ├── maxflow_1000.txt
│   ├── maxflow_10000.txt
│   └── maxflow_50000.txt
│
├── outputs/
│   ├── maxflow_10.out
│   ├── maxflow_100.out
│   ├── maxflow_1000.out
│   ├── maxflow_10000.out
│   └── maxflow_50000.out
│
├── tools/
│   └── generate_maxflow_graph.cpp
│
└── readme.md
```

---

# 18. Compilation

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

Run:

```bash
./Assignment__03/driver/main
```

Then choose:

```text
1 → Gradient Descent
2 → Maxflow-Mincut
3 → Exit
```

---

# 19. Complexity

| Buddy Task | Algorithm | Time Complexity | Space Complexity |
|---|---|---|---|
| Gradient Descent | Generic polynomial Gradient Descent | `O(d × I)` | `O(d)` |
| Maxflow-Mincut | Dinic's algorithm | `O(V²E)` general bound | `O(V + E)` |

Here:

- `d` = polynomial degree.
- `I` = number of Gradient Descent iterations.
- `V` = number of vertices.
- `E` = number of directed edges.

The complexity table is included for algorithm analysis; actual execution time depends on the input and machine.

---



The Assignment 3 specification is the primary reference for the required input format, test cases, output fields, validation, and timing rules.
