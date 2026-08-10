CS509 Laboratory Repository — Individual Tasks
Repository Overview
This repository contains individual programming assignments for CS509.

This section documents the Individual Tasks for Assignment 01:

GEMM (General Matrix Multiplication): Simple direct nested-loop implementation and Cache-blocking implementation.

CSR (Compressed Sparse Row) Graph Representation: Preprocessing module converting graph adjacency lists into compact CSR arrays (row_ptr, col_idx, values)

Student Details:
Student Name: Prashant Kumar
Entry Number: 2026CSM1028
Course: M.Tech CSE

Assignment Mode: Individual

Language and Environment
Programming Language: C++ (C++17 standard)

Compiler: g++ (MinGW-w64 / GCC)
Compilation Flags: -O3 -Wall

Platform/OS: Windows 11 (PowerShell) / Linux

Timing Method: std::chrono::high_resolution_clock (Measuring pure algorithm execution time in milliseconds with precision formatting)

Directory Structure:
CS509_CS1028/
├── README.md                           <-- Repository documentation
├── individual_wrapper.cpp              <-- C++ Test Harness Driver for Individual Tasks
├── individual_wrapper.exe              <-- Compiled wrapper executable
└── Assignment_01/
    ├── src/
    │   ├── GEMM_blocking.cpp           <-- Blocked GEMM matrix implementation
    │   ├── GEMM_blocking.hpp           <-- Blocked GEMM header
    │   ├── GEMM_simple.cpp             <-- Simple GEMM matrix implementation
    │   ├── GEMM_simple.hpp             <-- Simple GEMM header
    │   ├── csr_graph.cpp               <-- Safe CSR conversion logic implementation
    │   └── csr_graph.hpp               <-- CSR structure headers
    ├── driver/
    │   ├── GEMM_driver.cpp             <-- Driver for matrix multiplication
    │   ├── gemm_driver.exe             <-- Compiled GEMM driver executable
    │   ├── csr_test_driver.cpp         <-- Driver for CSR conversion & high-precision timing
    │   └── csr_test_driver.exe         <-- Compiled CSR driver executable
    ├── tests/
    │   ├── csr_input_1.txt             <-- Basic CSR adjacency list input
    │   ├── csr_input_10.txt            <-- CSR input (10 vertices)
    │   ├── csr_input_100.txt           <-- CSR input (100 vertices)
    │   ├── csr_input_1000.txt          <-- CSR input (1,000 vertices)
    │   ├── csr_input_10000.txt         <-- CSR input (10,000 vertices)
    │   ├── gemm_10.txt                 <-- Matrix size 10x10
    │   ├── gemm_50.txt                 <-- Matrix size 50x50
    │   ├── gemm_100.txt                <-- Matrix size 100x100
    │   ├── gemm_500.txt                <-- Matrix size 500x500
    │   ├── gemm_1000.txt               <-- Matrix size 1000x1000
    │   └── input_1.txt                 <-- Sample test matrix input
    └── outputs/
        ├── csr_output_1.txt            <-- Generated CSR output arrays
        ├── csr_output_10.txt           <-- CSR output (10 vertices)
        ├── csr_output_100.txt          <-- CSR output (100 vertices)
        ├── csr_output_1000.txt         <-- CSR output (1,000 vertices)
        ├── csr_output_10000.txt        <-- CSR output (10,000 vertices)
        ├── gemm_10_out.txt             <-- Matrix output (10x10)
        ├── gemm_50_out.txt             <-- Matrix output (50x50)
        ├── gemm_100_out.txt            <-- Matrix output (100x100)
        ├── gemm_500_out.txt            <-- Matrix output (500x500)
        └── gemm_1000_out.txt           <-- Matrix output (1000x1000)

Common Wrapper: Build and Usage
The individual common wrapper automates compilation, execution, and output logging across all individual tasks.

Compiling the Wrapper
From the root directory (CS509_CS1028), execute:
g++ -O3 individual_wrapper.cpp -o individual_wrapper.exe

Running the Wrapper
.\individual_wrapper.exe

Assignment 01: Individual Tasks1. GEMM (General Matrix Multiplication)ObjectiveCompute the matrix product C = A * B using two implementations:
Simple GEMM: Direct 3-nested loop matrix multiplication.
Blocking GEMM: Tiled iteration designed to maximize CPU L1/L2 cache locality.

GEMM Benchmark Results Table
Test File,Input Size,Expected Output,Actual Output,Simple Time (ms),Blocking Time (ms),Block Size,Status
input_1.txt,Up to 100,Matrix Output,Matches Expected,0.0000 ms,0.0000 ms,16x16,Pass
gemm_10.txt,10x10,10x10 Matrix,Matches Expected,0.0000 ms,0.0000 ms,16x16,Pass
gemm_50.txt,50x50,50x50 Matrix,Matches Expected,0.0000 ms,0.5060 ms,16x16,Pass
gemm_100.txt,100x100,100x100 Matrix,Matches Expected,6.7990 ms,1.4680 ms,32x32,Pass
gemm_500.txt,500x500,500x500 Matrix,Matches Expected,107.4960 ms,98.7660 ms,32x32,Pass
gemm_1000.txt,1000x1000,1000x1000 Matrix,Matches Expected,1360.5470 ms,944.9490 ms,32x32,Pass

CSR Graph Representation
ObjectiveConvert graph adjacency list inputs into Compressed Sparse Row (CSR) array representations.  

CSR Data Arraysrow_ptr: 
row_ptr: Size V+1, marks starting/ending offsets for neighbor lists.
col_idx: Size E, stores target neighbor vertex indices.
values: Size E, stores edge weights (NULL for unweighted graphs).

Preprocessing Rule
Adjacency-list-to-CSR conversion is executed as preprocessing setup. Its runtime is omitted from algorithm execution timing as per lab guidelines.

Graph CSR Performance and Output Verification Table

| Mode | Test File | Vertices (V) | Edges (E) | Input Format | Preprocessing Status | Execution Time | Status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Single | `csr_input_1.txt` | 5 | 10 | Adjacency List | Converted to CSR | 0.000 ms

 | Pass |
| Single | `csr_input_10.txt` | 10 | 15 | Adjacency List | Converted to CSR | 0.000 ms

 | Pass |
| Single | `csr_input_100.txt` | 100 | 200 | Adjacency List | Converted to CSR | 0.000 ms

 | Pass |
| Single | `csr_input_1000.txt` | 1,000 | 2,000 | Adjacency List | Converted to CSR | 1.749 ms

 | Pass |
| Single | `csr_input_10000.txt` | 10,000 | 20,000 | Adjacency List | Converted to CSR | 7.408 ms

 | Pass |

Complexity Analysis
Task / Algorithm,Time Complexity,Space Complexity,Notes
Simple GEMM,O(M x N x K),O(M x N),Subject to cache thrashing on large matrices
Blocking GEMM,O(M x N x K),O(M x N),Enhances L1/L2 cache hit ratio via sub-matrix blocking
CSR Conversion,O(V + E),O(V + E),Preprocessing step converting sparse data to contiguous vectors

Observations & Execution Behavior Notes
Timing Precision Changes: For very small inputs (such as V = 10 or small matrices), unoptimized timers initially recorded standard 0 ms due to integer truncation. This was resolved by upgrading the drivers to high-resolution floating-point precision (std::chrono::duration<double, std::milli>) combined with fixed-point output streams (std::setprecision), allowing accurate fractional milliseconds reporting (e.g., 0.0000 ms).

Scale Scaling Behavior: As the vertex and edge count scales up to 10,000, file generation and text stream writes take up noticeably more time due to massive output array string formatting (row_ptr and col_idx array size rendering), while internal conversion logic executes efficiently in linear time complexity.

References
CS509 Assignment 1 Specification Document.
CS509 M.Tech Lab Work Guidelines.
