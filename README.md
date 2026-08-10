# CS509 — M.Tech CSE Laboratory

> **Individual Programming Assignments | C++17 | Performance & Graph Algorithms**

This repository contains the **individual programming assignments for CS509 — M.Tech CSE Laboratory** by **Prashant Kumar (2026CSM1028)**.

The repository currently includes implementations, drivers, test cases, benchmark results, and generated outputs for **Assignment 01** and **Assignment 02**.

---

## 👨‍🎓 Student Details

| Field | Details |
|---|---|
| **Student Name** | Prashant Kumar |
| **Entry Number** | 2026CSM1028 |
| **Program** | M.Tech CSE |
| **Course** | CS509 |
| **Assignment Mode** | Individual |
| **Language** | C++17 |

---

## 📚 Assignments

### Assignment 01 — Matrix Multiplication & Sparse Graph Representation

Assignment 01 focuses on performance-oriented matrix multiplication and sparse graph data representation.

| Task | Description |
|---|---|
| **GEMM — Simple** | Conventional three-nested-loop matrix multiplication |
| **GEMM — Blocking** | Cache-blocked/tiled matrix multiplication for improved locality |
| **CSR** | Conversion of adjacency-list graphs into Compressed Sparse Row representation |

#### GEMM Performance

The blocking implementation maintains the same asymptotic complexity as simple GEMM while improving cache locality.

For the reported `1000 × 1000` benchmark:

- **Simple GEMM:** `1360.5470 ms`
- **Blocking GEMM:** `944.9490 ms`
- **Approximate improvement:** `30.5%`

#### CSR

CSR preprocessing converts adjacency-list graph data into compact arrays:

- `row_ptr`
- `col_idx`
- `values` where applicable

The reported CSR conversion complexity is **O(V + E)**.

[**→ Open Assignment 01**](./Assignment_01/README.md)

---

### Assignment 02 — Shortest Path Algorithms

Assignment 02 focuses on shortest-path algorithms for weighted graphs.

| Task | Description |
|---|---|
| **Bellman-Ford** | Single-source shortest paths with support for negative edge weights and negative-cycle detection |
| **Floyd-Warshall** | All-pairs shortest paths using dynamic programming |

#### Bellman-Ford

Reported benchmark coverage includes graphs up to:

- **50,000 vertices**
- **100,000 edges**
- Execution time: **248.9100 ms**

Complexity:

- **Time:** `O(V × E)`
- **Space:** `O(V + E)`

#### Floyd-Warshall

Reported benchmark coverage includes graphs up to:

- **1,000 vertices**
- Execution time: **1840.2100 ms**

Complexity:

- **Time:** `O(V³)`
- **Space:** `O(V²)`

[**→ Open Assignment 02**](./Assignment_02/README.md)

---

## 🗂️ Repository Structure

```text
CS509_CS1028/
│
├── README.md
├── individual_wrapper.cpp
├── individual_wrapper.exe
│
├── Assignment_01/
│   ├── README.md
│   ├── src/
│   │   ├── GEMM_blocking.cpp
│   │   ├── GEMM_blocking.hpp
│   │   ├── GEMM_simple.cpp
│   │   ├── GEMM_simple.hpp
│   │   ├── csr_graph.cpp
│   │   └── csr_graph.hpp
│   │
│   ├── driver/
│   │   ├── GEMM_driver.cpp
│   │   ├── gemm_driver.exe
│   │   ├── csr_test_driver.cpp
│   │   └── csr_test_driver.exe
│   │
│   ├── tests/
│   │   └── Assignment 01 test inputs
│   │
│   └── outputs/
│       └── Assignment 01 generated outputs
│
└── Assignment_02/
    ├── README.md
    ├── src/
    │   ├── bellmanford.cpp
    │   ├── bellmanford.hpp
    │   ├── floydwarshall.cpp
    │   └── floydwarshall.hpp
    │
    ├── driver/
    │   ├── bellmanford_driver.cpp
    │   ├── bellmanford_driver.exe
    │   ├── floydwarshall_driver.cpp
    │   └── floydwarshall_driver.exe
    │
    ├── tests/
    │   └── Assignment 02 test inputs
    │
    └── outputs/
        └── Assignment 02 generated outputs
```

---

## 🛠️ Language & Environment

| Component | Configuration |
|---|---|
| **Language** | C++ |
| **Standard** | C++17 |
| **Compiler** | g++ / GCC / MinGW-w64 |
| **Optimization** | `-O3` |
| **Warnings** | `-Wall` |
| **Supported OS** | Windows 11 / Linux |
| **Timing** | `std::chrono::high_resolution_clock` |
| **Timing Unit** | Milliseconds (`ms`) |

The implementations are designed to be portable across Windows and Linux environments with a C++17-compatible compiler.

---

## ⚙️ Building

### Compile the Common Wrapper

#### Windows / MinGW

```powershell
g++ -O3 -Wall individual_wrapper.cpp -o individual_wrapper.exe
```

#### Linux

```bash
g++ -O3 -Wall individual_wrapper.cpp -o individual_wrapper
```

### Run the Wrapper

#### Windows PowerShell

```powershell
.\individual_wrapper.exe
```

#### Linux

```bash
./individual_wrapper
```

The common wrapper automates execution of the individual task drivers and records the corresponding outputs.

---

## 📊 Complexity Summary

| Algorithm / Task | Time Complexity | Space Complexity |
|---|---:|---:|
| **Simple GEMM** | `O(M × N × K)` | `O(M × N)` |
| **Blocking GEMM** | `O(M × N × K)` | `O(M × N)` |
| **CSR Conversion** | `O(V + E)` | `O(V + E)` |
| **Bellman-Ford** | `O(V × E)` | `O(V + E)` |
| **Floyd-Warshall** | `O(V³)` | `O(V²)` |

---

## ⏱️ Performance & Timing

Execution time is measured using:

```cpp
std::chrono::high_resolution_clock
```

with floating-point millisecond duration:

```cpp
std::chrono::duration<double, std::milli>
```

Fixed-point output is used to preserve fractional milliseconds for small workloads.

For large workloads, the benchmark results demonstrate the expected algorithmic and implementation-level behavior:

- Blocking GEMM benefits from improved cache locality.
- CSR conversion scales approximately linearly with the number of vertices and edges.
- Bellman-Ford scales with `V × E`.
- Floyd-Warshall scales cubically with the number of vertices.

---

## ✅ Verification Status

All reported test cases in both assignments completed successfully.

| Assignment | Component | Test Cases | Status |
|---|---|---:|---|
| **01** | Simple GEMM | 6 | **PASS** |
| **01** | Blocking GEMM | 6 | **PASS** |
| **01** | CSR Conversion | 5 | **PASS** |
| **02** | Bellman-Ford | 5 | **PASS** |
| **02** | Floyd-Warshall | 5 | **PASS** |

### Overall Repository Status

**PASS — All reported Assignment 01 and Assignment 02 test cases completed successfully.**

---

## 📖 Assignment Documentation

Detailed implementation information, test cases, benchmark tables, complexity analysis, timing methodology, and verification results are available in the individual assignment README files:

- [📘 Assignment 01 — GEMM & CSR](./Assignment_01/README.md)
- [📗 Assignment 02 — Bellman-Ford & Floyd-Warshall](./Assignment_02/README.md)

---

## 🔑 Key Topics Covered

- Matrix multiplication
- Cache blocking / tiling
- CPU cache locality
- Sparse graph representation
- Compressed Sparse Row (CSR)
- Single-source shortest paths
- All-pairs shortest paths
- Negative edge weights
- Negative-cycle detection
- Dynamic programming
- Algorithmic complexity
- Benchmarking and performance analysis
- High-resolution execution timing
- C++17 programming

---

## 👤 Author

**Prashant Kumar**  
**Entry Number:** 2026CSM1028  
**Program:** M.Tech CSE  
**Course:** CS509

---

> **CS509 Laboratory — Individual Programming Assignments**
>
> *C++17 • Algorithms • Data Structures • Performance Analysis*
