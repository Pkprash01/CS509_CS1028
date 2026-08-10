# CS509 Laboratory Repository — Individual Tasks

## Repository Overview

This repository contains the **individual programming assignments for CS509 — M.Tech CSE Laboratory**.

This section documents the **Individual Tasks for Assignment 01**, covering:

1. **GEMM (General Matrix Multiplication)**

   * Simple direct nested-loop implementation
   * Cache-blocking / tiled implementation
2. **CSR (Compressed Sparse Row) Graph Representation**

   * Conversion of graph adjacency-list representation into compact CSR arrays

---

## Student Details

| Field               | Details        |
| ------------------- | -------------- |
| **Student Name**    | Prashant Kumar |
| **Entry Number**    | 2026CSM1028    |
| **Course**          | M.Tech CSE     |
| **Assignment**      | Assignment 01  |
| **Assignment Mode** | Individual     |
| **Language**        | C++17          |

---

## Language and Environment

| Component                | Configuration                        |
| ------------------------ | ------------------------------------ |
| **Programming Language** | C++                                  |
| **Standard**             | C++17                                |
| **Compiler**             | g++ / MinGW-w64 / GCC                |
| **Compilation Flags**    | `-O3 -Wall`                          |
| **Operating Systems**    | Windows 11 / Linux                   |
| **Timing Method**        | `std::chrono::high_resolution_clock` |
| **Timing Unit**          | Milliseconds (`ms`)                  |
| **Output Precision**     | Floating-point with fixed precision  |

The implementations are designed to be portable across Windows and Linux environments supporting a C++17-compatible compiler.

---

# Directory Structure

```text
CS509_CS1028/
│
├── README.md
├── individual_wrapper.cpp
├── individual_wrapper.exe
│
└── Assignment_01/
    │
    ├── src/
    │   ├── GEMM_blocking.cpp
    │   ├── GEMM_blocking.hpp
    │   ├── GEMM_simple.cpp
    │   ├── GEMM_simple.hpp
    │   ├── csr_graph.cpp
    │   └── csr_graph.hpp
    │
    ├── driver/
    │   ├── GEMM_driver.cpp
    │   ├── gemm_driver.exe
    │   ├── csr_test_driver.cpp
    │   └── csr_test_driver.exe
    │
    ├── tests/
    │   ├── csr_input_1.txt
    │   ├── csr_input_10.txt
    │   ├── csr_input_100.txt
    │   ├── csr_input_1000.txt
    │   ├── csr_input_10000.txt
    │   ├── gemm_10.txt
    │   ├── gemm_50.txt
    │   ├── gemm_100.txt
    │   ├── gemm_500.txt
    │   ├── gemm_1000.txt
    │   └── input_1.txt
    │
    └── outputs/
        ├── csr_output_1.txt
        ├── csr_output_10.txt
        ├── csr_output_100.txt
        ├── csr_output_1000.txt
        ├── csr_output_10000.txt
        ├── gemm_10_out.txt
        ├── gemm_50_out.txt
        ├── gemm_100_out.txt
        ├── gemm_500_out.txt
        └── gemm_1000_out.txt
```

---

# Assignment 01

## 1. GEMM — General Matrix Multiplication

### Objective

The objective of the GEMM task is to compute the matrix product:

[
C = A \times B
]

using two different implementations:

1. **Simple GEMM** — conventional three-nested-loop matrix multiplication.
2. **Blocking GEMM** — tiled matrix multiplication designed to improve CPU cache locality.

Both implementations produce the same mathematical result. The primary difference is the way matrix elements are accessed during computation.

---

## 1.1 Simple GEMM

The simple implementation uses the conventional three-loop approach:

```text
for i
    for j
        for k
            C[i][j] += A[i][k] * B[k][j]
```

### Characteristics

* Straightforward implementation
* Time complexity: `O(M × N × K)`
* Easy to understand and verify
* Can suffer from poor cache locality for large matrices

---

## 1.2 Blocking GEMM

The blocking implementation divides the matrices into smaller sub-matrices (tiles/blocks).

The computation is performed block-by-block so that frequently accessed matrix elements are more likely to remain in the CPU cache.

### Characteristics

* Same asymptotic computational complexity as simple GEMM
* Improves memory access locality
* Reduces cache misses for sufficiently large matrices
* Uses configurable block sizes
* Observed block sizes: `16 × 16` and `32 × 32`

---

## 1.3 GEMM Benchmark Results

| Test File       |  Input Size | Expected Output    | Actual Output    | Simple Time (ms) | Blocking Time (ms) | Block Size | Status   |
| --------------- | ----------: | ------------------ | ---------------- | ---------------: | -----------------: | ---------: | -------- |
| `input_1.txt`   |   Up to 100 | Matrix Output      | Matches Expected |           0.0000 |             0.0000 |    16 × 16 | **Pass** |
| `gemm_10.txt`   |     10 × 10 | 10 × 10 Matrix     | Matches Expected |           0.0000 |             0.0000 |    16 × 16 | **Pass** |
| `gemm_50.txt`   |     50 × 50 | 50 × 50 Matrix     | Matches Expected |           0.0000 |             0.5060 |    16 × 16 | **Pass** |
| `gemm_100.txt`  |   100 × 100 | 100 × 100 Matrix   | Matches Expected |           6.7990 |             1.4680 |    32 × 32 | **Pass** |
| `gemm_500.txt`  |   500 × 500 | 500 × 500 Matrix   | Matches Expected |         107.4960 |            98.7660 |    32 × 32 | **Pass** |
| `gemm_1000.txt` | 1000 × 1000 | 1000 × 1000 Matrix | Matches Expected |        1360.5470 |           944.9490 |    32 × 32 | **Pass** |

### Performance Observation

For larger matrices, blocking provides a noticeable performance improvement.

For the `1000 × 1000` test:

* **Simple GEMM:** `1360.5470 ms`
* **Blocking GEMM:** `944.9490 ms`

This represents an approximate **30.5% reduction in execution time** for the blocking implementation under the reported test conditions.

For small matrices, the difference is less meaningful because the computation is too small for cache effects to dominate and timer resolution becomes significant.

---

# 2. CSR — Compressed Sparse Row Graph Representation

## Objective

The objective of the CSR task is to convert a graph represented using adjacency lists into a compact **Compressed Sparse Row (CSR)** representation.

CSR stores sparse graph data using contiguous arrays, reducing storage overhead and providing efficient sequential access to graph edges.

---

## 2.1 CSR Data Structures

The implementation uses three primary arrays:

### `row_ptr`

`row_ptr` has size:

```text
V + 1
```

where `V` is the number of vertices.

For vertex `i`, its outgoing neighbors are stored in:

```text
col_idx[row_ptr[i] ... row_ptr[i+1]-1]
```

Thus, `row_ptr` identifies the beginning and ending positions of each vertex's adjacency list.

---

### `col_idx`

`col_idx` has size:

```text
E
```

where `E` is the number of edges.

It stores the destination vertex index for each edge.

---

### `values`

`values` also has size:

```text
E
```

when edge weights are present.

For unweighted graphs, edge values are not required and may be represented as `NULL`/absent.

---

## 2.2 CSR Conversion

The conversion process can be summarized as:

```text
Adjacency List
      │
      ▼
Count edges per vertex
      │
      ▼
Construct row_ptr
      │
      ▼
Store neighbor indices
      │
      ▼
Construct col_idx / values
      │
      ▼
      CSR Representation
```

The adjacency-list-to-CSR conversion is treated as a **preprocessing operation**. Therefore, according to the laboratory timing requirements, preprocessing time is not included in the measured execution time of subsequent CSR operations.

---

# 2.3 CSR Performance and Verification

| Mode   | Test File             | Vertices (V) | Edges (E) | Input Format   | Preprocessing Status | Execution Time | Status   |
| ------ | --------------------- | -----------: | --------: | -------------- | -------------------- | -------------: | -------- |
| Single | `csr_input_1.txt`     |            5 |        10 | Adjacency List | Converted to CSR     |       0.000 ms | **Pass** |
| Single | `csr_input_10.txt`    |           10 |        15 | Adjacency List | Converted to CSR     |       0.000 ms | **Pass** |
| Single | `csr_input_100.txt`   |          100 |       200 | Adjacency List | Converted to CSR     |       0.000 ms | **Pass** |
| Single | `csr_input_1000.txt`  |        1,000 |     2,000 | Adjacency List | Converted to CSR     |       1.749 ms | **Pass** |
| Single | `csr_input_10000.txt` |       10,000 |    20,000 | Adjacency List | Converted to CSR     |       7.408 ms | **Pass** |

All reported test cases successfully completed CSR conversion and output verification.

---

# 3. Complexity Analysis

| Task / Algorithm   | Time Complexity | Space Complexity | Notes                                                             |
| ------------------ | --------------- | ---------------- | ----------------------------------------------------------------- |
| **Simple GEMM**    | `O(M × N × K)`  | `O(M × N)`       | Conventional nested-loop matrix multiplication                    |
| **Blocking GEMM**  | `O(M × N × K)`  | `O(M × N)`       | Same asymptotic complexity, but improved cache locality           |
| **CSR Conversion** | `O(V + E)`      | `O(V + E)`       | Converts adjacency-list representation into contiguous CSR arrays |

### GEMM Complexity

For matrices:

* `A`: `M × K`
* `B`: `K × N`
* `C`: `M × N`

the matrix multiplication requires:

```text
O(M × N × K)
```

arithmetic operations.

Blocking does **not** change the asymptotic complexity. Its advantage comes from improving memory locality and cache utilization.

### CSR Complexity

For a graph containing:

* `V` vertices
* `E` edges

CSR construction requires:

```text
O(V + E)
```

time and:

```text
O(V + E)
```

space for the resulting CSR representation.

---

# 4. Timing Methodology

Execution time is measured using:

```cpp
std::chrono::high_resolution_clock
```

The measured duration is represented using a floating-point millisecond duration:

```cpp
std::chrono::duration<double, std::milli>
```

Output is formatted using fixed-point precision to retain fractional milliseconds.

For example:

```text
0.0000 ms
1.7490 ms
7.4080 ms
```

The intention is to measure the **algorithm execution time** rather than file-generation or output-formatting overhead.

---

# 5. Timing Precision and Execution Behavior

## Small Inputs

For very small inputs, execution can be significantly shorter than one millisecond.

Earlier integer-based timing could therefore produce:

```text
0 ms
```

due to truncation.

The drivers were updated to use floating-point millisecond durations and fixed precision, allowing more accurate reporting of small execution times.

---

## Large Inputs

As the input size increases, execution time becomes more measurable and performance differences between algorithms become clearer.

For GEMM, the blocking implementation shows a noticeable improvement for larger matrices, particularly at:

```text
500 × 500
1000 × 1000
```

This behavior is consistent with the expected benefit of improved cache locality.

---

# 6. CSR Scaling Behavior

The CSR algorithm itself has linear complexity:

```text
O(V + E)
```

As the graph size increases, the conversion work therefore grows approximately linearly with the number of vertices and edges.

For larger test cases, such as:

```text
V = 10,000
E = 20,000
```

additional time may be observed due to output generation and text formatting, especially when large `row_ptr` and `col_idx` arrays are written to files.

It is important to distinguish this I/O overhead from the core CSR conversion algorithm.

---

# 7. Common Wrapper

A common wrapper is provided to automate compilation, execution, and output logging for the individual tasks.

## Compile

From the repository root:

### Windows / MinGW

```powershell
g++ -O3 -Wall individual_wrapper.cpp -o individual_wrapper.exe
```

### Linux

```bash
g++ -O3 -Wall individual_wrapper.cpp -o individual_wrapper
```

---

## Run

### Windows PowerShell

```powershell
.\individual_wrapper.exe
```

### Linux

```bash
./individual_wrapper
```

The wrapper automates the execution of the individual task drivers and records the corresponding outputs.

---

# 8. Individual Drivers

### GEMM Driver

The GEMM driver is located at:

```text
Assignment_01/driver/GEMM_driver.cpp
```

It is responsible for:

* Reading matrix input
* Running Simple GEMM
* Running Blocking GEMM
* Measuring execution time
* Comparing/generated matrix outputs
* Reporting performance results

### CSR Driver

The CSR driver is located at:

```text
Assignment_01/driver/csr_test_driver.cpp
```

It is responsible for:

* Reading adjacency-list graph input
* Performing CSR preprocessing
* Generating `row_ptr`
* Generating `col_idx`
* Handling edge values where applicable
* Measuring execution behavior
* Writing CSR output

---

# 9. Output Files

Generated outputs are stored under:

```text
Assignment_01/outputs/
```

### CSR Outputs

```text
csr_output_1.txt
csr_output_10.txt
csr_output_100.txt
csr_output_1000.txt
csr_output_10000.txt
```

### GEMM Outputs

```text
gemm_10_out.txt
gemm_50_out.txt
gemm_100_out.txt
gemm_500_out.txt
gemm_1000_out.txt
```

These files contain the generated results corresponding to the supplied test inputs.

---

# 10. Verification

All listed GEMM test cases produced outputs matching the expected matrix results.

All listed CSR test cases successfully converted the supplied adjacency-list inputs into CSR representation.

### Overall Assignment Status

| Component      | Test Cases | Result   |
| -------------- | ---------: | -------- |
| Simple GEMM    |          6 | **Pass** |
| Blocking GEMM  |          6 | **Pass** |
| CSR Conversion |          5 | **Pass** |

**Overall Status: PASS**

---

# 11. Key Observations

1. **Simple and Blocking GEMM have the same asymptotic complexity**, `O(M × N × K)`.

2. **Blocking GEMM improves cache locality**, resulting in better performance for sufficiently large matrices.

3. The `1000 × 1000` GEMM test demonstrated a substantial performance difference:

   * Simple GEMM: `1360.5470 ms`
   * Blocking GEMM: `944.9490 ms`

4. **CSR conversion has linear complexity**, `O(V + E)`, making it suitable for preprocessing sparse graph data.

5. High-resolution floating-point timing provides more useful measurements for very small workloads than integer millisecond timing.

6. For large CSR test cases, **file I/O and output formatting can contribute noticeable overhead** and should be distinguished from the core conversion computation.

---

# 12. References

* **CS509 Assignment 01 Specification Document**
* **CS509 M.Tech CSE Laboratory Work Guidelines**
* C++17 Standard Library documentation for `std::chrono`
* Standard algorithms and data-structure concepts for GEMM and CSR representations

---

## Author

**Prashant Kumar**
**Entry Number:** 2026CSM1028
**Program:** M.Tech CSE
**Course:** CS509
