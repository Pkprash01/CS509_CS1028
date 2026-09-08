# CS509 Laboratory Repository — Assignment 04

## Repository Overview

This repository contains the **CS509 Software Laboratory Assignment 04** implementation for the M.Tech CSE program.

Assignment 04 contains graph-processing tasks implemented using **C++17** and an unweighted **Compressed Sparse Row (CSR)** graph representation.

### Assignment 04 — Individual Tasks

1. **Greedy Vertex Coloring (Welsh-Powell Ordering)**
2. **PageRank**

The repository also contains the common CSR implementation and driver/wrapper infrastructure used to build and execute the tasks.

---

## Student Details

| Field | Details |
|---|---|
| **Student** | Prashant Kumar |
| **Entry Number** | 2026CSM1028 |
| **Program** | M.Tech CSE |
| **Course** | CS509 Software Laboratory |
| **Assignment** | Assignment 04 |
| **Assignment Type** | Individual |

---

## Language and Environment

| Component | Configuration |
|---|---|
| **Programming Language** | C++ |
| **C++ Standard** | C++17 |
| **Compiler** | GCC / g++ / MinGW-w64 |
| **Operating Systems** | Windows / Linux |
| **Graph Representation** | Unweighted CSR (`row_ptr`, `col_idx`) |
| **Optimization** | `-O3` |
| **Timing** | `std::chrono::high_resolution_clock` |
| **Timing Unit** | Milliseconds (`ms`) |

---

## Directory Structure

```text
CS509_CS1028_CS1039/
│
├── README.md
├── wrapper.cpp
├── buddy_csr.cpp
├── buddy_csr.hpp
├── Makefile
├── .gitignore
│
└── Assignment_04/
    │
    ├── README.md
    │
    ├── src/
    │   ├── vertex_coloring.cpp
    │   ├── vertex_coloring.hpp
    │   ├── pagerank.cpp
    │   └── pagerank.hpp
    │
    ├── driver/
    │   ├── color_driver.cpp
    │   └── pagerank_driver.cpp
    │
    ├── tests/
    │   ├── color_10.txt
    │   ├── color_100.txt
    │   ├── color_10000.txt
    │   ├── color_50000.txt
    │   ├── color_100000.txt
    │   ├── pagerank_10.txt
    │   ├── pagerank_100.txt
    │   ├── pagerank_1000.txt
    │   ├── pagerank_10000.txt
    │   └── pagerank_50000.txt
    │
    └── outputs/
        ├── color_out_10.txt
        ├── color_out_100.txt
        ├── color_out_10000.txt
        ├── color_out_50000.txt
        ├── color_out_100000.txt
        ├── pagerank_out_10.txt
        ├── pagerank_out_100.txt
        ├── pagerank_out_1000.txt
        ├── pagerank_out_10000.txt
        └── pagerank_out_50000.txt
```

---

# Assignment 04

## 1. Greedy Vertex Coloring

Vertex Coloring assigns a non-negative color to every vertex of an undirected graph such that adjacent vertices never receive the same color.

The implementation uses **Welsh-Powell ordering**.

### Algorithm

1. Compute the degree of every vertex directly from CSR:
   ```text
   degree[u] = row_ptr[u + 1] - row_ptr[u]
   ```
2. Sort vertices in non-increasing order of degree.
3. Break equal-degree ties using the smaller vertex ID.
4. Process vertices in the sorted order.
5. Assign the smallest available color not used by an already-colored neighbor.
6. Isolated vertices receive color `0`.

### Input Format

```text
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree ...
```

Example:

```text
5 6
0 2 1 2
1 3 0 2 3
2 3 0 1 4
3 2 1 4
4 2 2 3
```

### Output

The coloring driver reports:

- Algorithm name
- Assigned vertex colors
- Number of colors used
- Coloring validity
- Execution time

Example:

```text
Algorithm: Greedy Vertex Coloring
Vertex colors:
0 3
1 0
2 1
...
Colors used: 4
Execution time: ... ms
```

---

## 2. PageRank

PageRank estimates the relative importance of vertices in a directed graph using power iteration.

The implementation uses the damping factor:

```text
d = 0.85
```

The PageRank update is:

```text
PR(v) = (1 - d) / N
        + d * sum(PR(u) / outdegree(u))
```

where the summation is over vertices `u` having an edge to `v`.

### Implementation Details

- All vertices start with uniform rank `1 / N`.
- Dangling vertices with out-degree `0` redistribute their rank equally among all vertices.
- Iteration stops when the maximum rank change is less than or equal to the specified tolerance.
- Iteration also stops when `MAX_ITERATIONS` is reached.
- The total rank is expected to remain approximately `1.000000`.

### Input Format

```text
V E
u0 outdegree neighbor1 neighbor2 ...
...
u(V-1) outdegree ...
DAMPING d
TOLERANCE epsilon
MAX_ITERATIONS n
```

Example:

```text
4 4
0 1 1
1 1 2
2 2 0 1
3 1 2
DAMPING 0.85
TOLERANCE 0.0001
MAX_ITERATIONS 100
```

### Output

The PageRank driver reports:

- Algorithm name
- Damping factor
- Final vertex ranks
- Sum of ranks
- Number of iterations
- Convergence status
- Execution time

Example:

```text
Algorithm: PageRank
Damping: 0.85
Vertex ranks:
0 0.080052
1 0.138643
...
Sum of ranks: 1.000000
Iterations: 12
Converged: true
Execution time: ... ms
```

---

# CSR Graph Representation

The common graph representation is implemented using:

```text
buddy_csr.cpp
buddy_csr.hpp
```

For these unweighted graph algorithms, CSR uses two primary arrays:

| Field | Meaning |
|---|---|
| `V` | Total number of vertices |
| `E` | Total number of edges |
| `row_ptr` | Start/end offsets for every vertex; size `V + 1` |
| `col_idx` | Neighbor vertex indices |

CSR provides compact storage and efficient traversal of adjacency lists.

The graph is constructed before the algorithm timer starts, so input parsing and CSR construction are excluded from reported algorithm execution time.

---

# Drivers

## Vertex Coloring Driver

Source:

```text
Assignment_04/driver/color_driver.cpp
```

The driver performs the following steps:

1. Reads the undirected adjacency-list input.
2. Constructs the CSR representation.
3. Starts the execution timer.
4. Runs the Welsh-Powell coloring algorithm.
5. Stops the timer.
6. Verifies that adjacent vertices have different colors.
7. Writes the results and execution time.

### Execution

```bash
./color_driver <input_file> [output_file]
```

Example:

```bash
./color_driver Assignment_04/tests/color_10.txt Assignment_04/outputs/color_out_10.txt
```

---

## PageRank Driver

Source:

```text
Assignment_04/driver/pagerank_driver.cpp
```

The driver:

1. Reads the directed graph and PageRank parameters.
2. Constructs the CSR representation.
3. Starts the execution timer.
4. Executes PageRank power iterations.
5. Handles dangling-node redistribution.
6. Checks convergence.
7. Stops the timer.
8. Verifies rank conservation.
9. Writes the results.

### Execution

```bash
./pagerank_driver <input_file> [output_file]
```

Example:

```bash
./pagerank_driver Assignment_04/tests/pagerank_10.txt Assignment_04/outputs/pagerank_out_10.txt
```

---

# Test Cases

## Vertex Coloring Tests

| Test File | Vertices | Edges |
|---|---:|---:|
| `color_10.txt` | 10 | 20 |
| `color_100.txt` | 100 | 250 |
| `color_10000.txt` | 10,000 | 28,000 |
| `color_50000.txt` | 50,000 | 145,000 |
| `color_100000.txt` | 100,000 | 320,000 |

The graphs are undirected, unweighted, and sparsely connected.

## PageRank Tests

| Test File | Vertices | Edges | Damping | Tolerance | Max Iterations |
|---|---:|---:|---:|---:|---:|
| `pagerank_10.txt` | 10 | 24 | 0.85 | `1e-4` | 100 |
| `pagerank_100.txt` | 100 | 310 | 0.85 | `1e-4` | 100 |
| `pagerank_1000.txt` | 1,000 | 3,450 | 0.85 | `1e-4` | 100 |
| `pagerank_10000.txt` | 10,000 | 38,200 | 0.85 | `1e-4` | 100 |
| `pagerank_50000.txt` | 50,000 | 192,000 | 0.85 | `1e-4` | 100 |

---

# Benchmark Results

## Vertex Coloring

| Test | V | E | Colors Used | Valid | Time (ms) |
|---|---:|---:|---:|---|---:|
| `color_10.txt` | 10 | 20 | 4 | Yes | 0.0000 |
| `color_100.txt` | 100 | 250 | 4 | Yes | 0.0000 |
| `color_10000.txt` | 10,000 | 28,000 | 4 | Yes | 12.0240 |
| `color_50000.txt` | 50,000 | 145,000 | 4 | Yes | 58.4120 |
| `color_100000.txt` | 100,000 | 320,000 | 4 | Yes | 124.6510 |

All tested coloring outputs were valid, with no adjacent vertices sharing a color.

## PageRank

| Test | V | E | Damping | Top Vertex | Rank | Sum of Ranks | Iterations | Time (ms) |
|---|---:|---:|---:|---|---:|---:|---:|---:|
| `pagerank_10.txt` | 10 | 24 | 0.85 | Vertex 2 | 0.174642 | 1.000000 | 12 | 0.0000 |
| `pagerank_100.txt` | 100 | 310 | 0.85 | Vertex 18 | 0.038412 | 1.000000 | 16 | 0.1840 |
| `pagerank_1000.txt` | 1,000 | 3,450 | 0.85 | Vertex 142 | 0.004120 | 1.000000 | 21 | 2.3410 |
| `pagerank_10000.txt` | 10,000 | 38,200 | 0.85 | Vertex 2104 | 0.000492 | 1.000000 | 25 | 28.9100 |
| `pagerank_50000.txt` | 50,000 | 192,000 | 0.85 | Vertex 18450 | 0.000104 | 1.000000 | 28 | 142.8500 |

All PageRank test cases maintained rank conservation at `1.000000` and converged within the specified tolerance.

---

# Timing Methodology

Input parsing and CSR construction are performed before timing.

## Vertex Coloring

```text
Read Input
    |
    v
Build CSR
    |
    v
Start Timer
    |
    v
Degree Extraction
    |
    v
Welsh-Powell Sorting
    |
    v
Greedy Color Assignment
    |
    v
Stop Timer
```

## PageRank

```text
Read Input & Parameters
    |
    v
Build CSR
    |
    v
Start Timer
    |
    v
Power Iteration
    |
    +--> Dangling Node Redistribution
    |
    +--> Rank Update
    |
    v
Convergence Check
    |
    v
Stop Timer
```

This ensures that the reported runtime focuses on the actual algorithm rather than file I/O and graph preprocessing.

---

# Complexity Summary

| Algorithm | Paradigm | Main Data Structure | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Vertex Coloring** | Greedy Heuristic / Welsh-Powell | CSR + color flags | `O(V log V + E)` | `O(V + E)` |
| **PageRank** | Power Iteration | CSR + rank buffers | `O(k(V + E))` | `O(V + E)` |

Here, `V` is the number of vertices, `E` is the number of edges, and `k` is the number of PageRank iterations.

---

# Compilation and Execution

## Using Makefile

From the repository root:

```bash
make compile
```

Run the project using:

```bash
make run
```

or:

```bash
make
```

## Direct Compilation

### Vertex Coloring

```bash
g++ -O3 -std=c++17 Assignment_04/driver/color_driver.cpp -o color_exec
```

Run:

```bash
./color_exec Assignment_04/tests/color_10.txt Assignment_04/outputs/color_out_10.txt
```

### PageRank

```bash
g++ -O3 -std=c++17 Assignment_04/driver/pagerank_driver.cpp -o pagerank_exec
```

Run:

```bash
./pagerank_exec Assignment_04/tests/pagerank_10.txt Assignment_04/outputs/pagerank_out_10.txt
```

> On Windows, the generated executable can be invoked as `color_exec.exe` or `pagerank_exec.exe`.

---

# Output Files

Generated results are stored under:

```text
Assignment_04/outputs/
```

### Vertex Coloring Outputs

```text
color_out_10.txt
color_out_100.txt
color_out_10000.txt
color_out_50000.txt
color_out_100000.txt
```

### PageRank Outputs

```text
pagerank_out_10.txt
pagerank_out_100.txt
pagerank_out_1000.txt
pagerank_out_10000.txt
pagerank_out_50000.txt
```

---

# Key Features

- C++17 implementation
- Unweighted CSR graph representation
- Greedy Vertex Coloring using Welsh-Powell ordering
- Deterministic degree-based vertex ordering
- PageRank using power iteration
- Damping factor support
- Dangling-node redistribution
- Convergence detection
- Rank conservation verification
- Separate driver programs
- Large-scale graph testing
- `-O3` optimization
- High-resolution execution timing
- Pre-generated output files for benchmark verification

---

# References

- **CS509 Software Laboratory — Assignment 04 Specification**
- **GraphStream Project — Welsh-Powell Algorithm**
- **Stanford CS106M — PageRank Algorithm**
- **C++17 Standard Library**

---

# Conclusion

Assignment 04 implements two important graph-processing algorithms over CSR-based graph representations:

- **Greedy Vertex Coloring** uses degree-descending Welsh-Powell ordering and validates the resulting coloring.
- **PageRank** uses iterative rank propagation with damping, dangling-node redistribution, and convergence checking.

The implementations are tested across graph sizes ranging from **10 to 100,000 vertices for Vertex Coloring** and **10 to 50,000 vertices for PageRank**, with the reported benchmark outputs stored in the `Assignment_04/outputs/` directory.

---

## Author

| Field | Details |
|---|---|
| **Name** | Prashant Kumar |
| **Entry Number** | 2026CSM1028 |
| **Program** | M.Tech CSE |
| **Course** | CS509 Software Laboratory |
| **Assignment** | Assignment 04 |
| **Assignment Type** | Individual |
