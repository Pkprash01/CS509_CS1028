# CS509 Laboratory Repository — Individual Tasks

## Repository Overview

This repository contains the **individual programming assignments for CS509 — M.Tech CSE Laboratory**.

This section documents the **Individual Tasks for Assignment 02**, covering:

1. **Bellman-Ford Algorithm**
   - Single-source shortest path calculation supporting negative edge weights.
   - Detection of negative weight cycles.
2. **Floyd-Warshall Algorithm**
   - All-pairs shortest path calculation using dynamic programming.

## Student Details

| **Field**           | **Details**    |
| ------------------- | -------------- |
| **Student Name**    | Prashant Kumar |
| **Entry Number**    | 2026CSM1028    |
| **Course**          | M.Tech CSE     |
| **Assignment**      | Assignment 02  |
| **Assignment Mode** | Individual     |
| **Language**        | C++17          |

## Language and Environment

| **Component**            | **Configuration**                    |
| ------------------------ | ------------------------------------ |
| **Programming Language** | C++                                  |
| **Standard**             | C++17                                |
| **Compiler**             | g++ / MinGW-w64 / GCC                |
| **Compilation Flags**    | `-O3 -Wall`                          |
| **Operating Systems**    | Windows 11 / Linux                   |
| **Timing Method**        | `std::chrono::high_resolution_clock` |
| **Timing Unit**          | Milliseconds (`ms`)                  |
| **Output Precision**     | Floating-point with fixed precision  |

# Directory Structure

```text
CS509_CS1028/
│
├── README.md
├── individual_wrapper.cpp
├── individual_wrapper.exe
│
└── Assignment_02/
    │
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
    │   ├── bf_1.txt
    │   ├── bf_10.txt
    │   ├── bf_100.txt
    │   ├── bf_10000.txt
    │   ├── bf_50000.txt
    │   ├── fw_1.txt
    │   ├── fw_10.txt
    │   ├── fw_100.txt
    │   ├── fw_500.txt
    │   └── fw_1000.txt
    │
    └── outputs/
        ├── bf_out_1.txt
        ├── bf_out_10.txt
        ├── bf_out_100.txt
        ├── bf_out_10000.txt
        ├── bf_out_50000.txt
        ├── fw_out_1.txt
        ├── fw_out_10.txt
        ├── fw_out_100.txt
        ├── fw_out_500.txt
        └── fw_out_1000.txt
```

# Assignment 02

## 1. Bellman-Ford Algorithm

### Objective

Compute the shortest paths from a single source vertex to all other vertices in a weighted directed graph. Unlike Dijkstra's algorithm, Bellman-Ford correctly handles graphs containing negative-weight edges and can detect negative-weight cycles.

### 1.1 Bellman-Ford Benchmark Results

| **Test File**  | **Vertices (V)** | **Edges (E)** | **Execution Time (ms)** | **Status** |
| -------------- | ---------------- | ------------- | ----------------------- | ---------- |
| `bf_1.txt`     | 1                | 0             | 0.0000                  | **Pass**   |
| `bf_10.txt`    | 10               | 20            | 0.0150                  | **Pass**   |
| `bf_100.txt`   | 100              | 400           | 0.3120                  | **Pass**   |
| `bf_10000.txt` | 10,000           | 20,000        | 42.5800                 | **Pass**   |
| `bf_50000.txt` | 50,000           | 100,000       | 248.9100                | **Pass**   |

## 2. Floyd-Warshall Algorithm

### Objective

Find shortest paths between all pairs of vertices in a weighted graph with positive or negative edge weights, provided that the graph contains no negative-weight cycles, using dynamic programming.

### 2.1 Floyd-Warshall Benchmark Results

| **Test File** | **Vertices (V)** | **Execution Time (ms)** | **Status** |
| ------------- | ---------------- | ----------------------- | ---------- |
| `fw_1.txt`    | 1                | 0.0000                  | **Pass**   |
| `fw_10.txt`   | 10               | 0.0030                  | **Pass**   |
| `fw_100.txt`  | 100              | 2.1450                  | **Pass**   |
| `fw_500.txt`  | 500              | 215.8400                | **Pass**   |
| `fw_1000.txt` | 1,000            | 1840.2100               | **Pass**   |

# 3. Complexity Analysis

| **Task / Algorithm** | **Time Complexity** | **Space Complexity** | **Notes**                                       |
| -------------------- | ------------------- | -------------------- | ----------------------------------------------- |
| **Bellman-Ford**     | `O(V × E)`          | `O(V + E)`           | Single-source; handles negative weights         |
| **Floyd-Warshall**   | `O(V^3)`            | `O(V^2)`             | All-pairs shortest paths via dynamic programming |

# 4. Verification and Status

All test cases for Bellman-Ford and Floyd-Warshall completed successfully and matched the expected outputs.

### Overall Assignment Status

| **Component**  | **Test Cases** | **Result** |
| -------------- | -------------- | ---------- |
| Bellman-Ford   | 5              | **Pass**   |
| Floyd-Warshall | 5              | **Pass**   |

**Overall Status: PASS**

## Author

**Prashant Kumar**

**Entry Number:** 2026CSM1028

**Program:** M.Tech CSE

**Course:** CS509
