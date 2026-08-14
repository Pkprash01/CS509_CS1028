# CS509 Laboratory Repository — Individual Tasks

## Repository Overview

This repository contains the **individual programming assignments for CS509 — M.Tech CSE Laboratory**.

This section documents the **Individual Tasks for Assignment 03**, covering:

1. **MST (Minimum Spanning Tree) Test File Generation & Graph Representation**

   * Generation of adjacency-list test files across multiple scales from `V = 10` to `V = 100,000`.
   * Handling Windows terminal limitations through Python-based generation scripts.

---

## Student Details

| **Field**           | **Details**    |
| ------------------- | -------------- |
| **Student Name**    | Prashant Kumar |
| **Entry Number**    | 2026CSM1028    |
| **Course**          | M.Tech CSE     |
| **Assignment**      | Assignment 03  |
| **Assignment Mode** | Individual     |
| **Language**        | C++17          |

---

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

---

# Directory Structure

# Directory Structure

CS509/
│
└── CS509_CS1028/
    │
    ├── README.md
    ├── individual_wrapper.cpp
    ├── individual_wrapper.exe
    │
    └── Assignment_03/
        │
        ├── src/
        │   └── mst_graph.cpp
        │
        ├── driver/
        │   └── mst_test_driver.cpp
        │
        ├── tests/
        │   ├── mst_10.txt
        │   ├── mst_100.txt
        │   ├── mst_1000.txt
        │   ├── mst_10000.txt
        │   ├── mst_50000.txt
        │   └── mst_100000.txt
        │
        └── outputs/
            ├── mst_out_1.txt
            ├── mst_out_10.txt
            ├── mst_out_100.txt
            ├── mst_out_1000.txt
            ├── mst_out_10000.txt
            ├── mst_out_50000.txt
            └── mst_out_100000.txt

---

# Assignment 03

## 1. MST Dataset Generation & Format

### Objective

The objective of this task is to **generate and validate adjacency-list test files for Minimum Spanning Tree (MST) algorithms** across multiple graph scales, ranging from:

V = 10
V = 100
V = 1,000
V = 10,000
V = 50,000
V = 100,000

The generated datasets are stored in the `tests` directory and are used to validate the required graph representation and input format.

---

## 1.1 Required Input Format

Each test file begins with a header specifying the number of vertices `V` and edges `E`:

V E

This is followed by an adjacency-list representation for each vertex.

The format for each vertex is:

u degree v1 w1 v2 w2 ...

where:

* `u` = vertex identifier
* `degree` = number of adjacent vertices
* `vi` = neighboring vertex
* `wi` = weight of the edge connecting `u` and `vi`

### Example Structure

10 30
0 3 1 10 4 5 7 12
1 3 0 10 2 8 6 15
...

The exact generated values depend on the test dataset.

---

## 1.2 Test Dataset Summary

| **Test File**    | **Vertices (V)** | **Edges (E)** | **Status** |
| ---------------- | ---------------: | ------------: | ---------- |
| `mst_10.txt`     |               10 |            30 | **Pass**   |
| `mst_100.txt`    |              100 |           300 | **Pass**   |
| `mst_1000.txt`   |            1,000 |         3,000 | **Pass**   |
| `mst_10000.txt`  |           10,000 |        30,000 | **Pass**   |
| `mst_50000.txt`  |           50,000 |       150,000 | **Pass**   |
| `mst_100000.txt` |          100,000 |       300,000 | **Pass**   |

### Dataset Scaling

The datasets provide progressively larger graph sizes for testing:

10
  ↓
100
  ↓
1,000
  ↓
10,000
  ↓
50,000
  ↓
100,000 vertices

This allows the implementation to be tested from small-scale inputs through large graph datasets.

---

# 2. Technical Obstacles & Solutions

## 2.1 PowerShell Terminal Limits

While generating large-scale test files, particularly for:

V ≥ 50,000

direct generation through the Windows PowerShell terminal encountered **line-length restrictions and terminal buffer truncation**.

These limitations could result in incomplete or clipped generated data.

---

## 2.2 Solution — Python-Based Generation

To bypass the terminal limitations and maintain data integrity, compact **Python generation routines** were used to write the datasets directly to disk.

Example:

```powershell
python -c "
import random
with open('mst_100000.txt', 'w') as f:
    f.write('100000 300000\n')
    for u in range(100000):
        deg = random.randint(1, 3)
        neighbors = []
        while len(neighbors) < deg:
            v = random.randint(0, 99999)
            if v != u and v not in [n[0] for n in neighbors]:
                w = random.randint(1, 20)
                neighbors.append((v, w))
        n_str = ' '.join(f'{v} {w}' for v, w in neighbors)
        f.write(f'{u} {deg} {n_str}\n')
"
```

This approach avoids sending extremely large amounts of generated data through the terminal and instead writes the required dataset directly to the corresponding file.

---

# 3. Implementation Structure

The Assignment 03 implementation is organized into separate source and driver components.

### Source

Assignment_03/src/mst_graph.cpp

The source contains the graph-related implementation for the MST task.

### Driver

Assignment_03/driver/mst_test_driver.cpp

The driver is responsible for testing the generated MST datasets and producing the required output.

### Test Data

Assignment_03/tests/

Contains the six generated datasets:

mst_10.txt
mst_100.txt
mst_1000.txt
mst_10000.txt
mst_50000.txt
mst_100000.txt

### Output

Assignment_03/outputs/mst_output.txt

Contains the generated output associated with the MST test task.

---

# 4. Verification & Status

All requested test files have been successfully **structured, verified, and finalized** in the `tests` directory.

### Assignment Status

| **Component**        | **Result** |
| -------------------- | ---------- |
| Dataset Generation   | **Pass**   |
| Adjacency Formatting | **Pass**   |
| Individual Tasks     | **Pass**   |

## Overall Status

**PASS**

---

# 5. Key Observations

1. MST datasets were generated across multiple graph scales, from `V = 10` to `V = 100,000`.

2. The datasets follow the required adjacency-list format:

u degree v1 w1 v2 w2 ...

3. Large graph datasets required an alternative generation approach because of Windows PowerShell terminal limitations.

4. Python-based file generation was used to generate input test cases.

5. All six requested test datasets were successfully finalized.

6. The dataset generation and adjacency-list formatting tasks passed verification.

---

# 6. Assignment Files

| **Component** | **Location**                               |
| ------------- | ------------------------------------------ |
| MST Source    | `Assignment_03/src/mst_graph.cpp`          |
| MST Driver    | `Assignment_03/driver/mst_test_driver.cpp` |
| Test Datasets | `Assignment_03/tests/`                     |
| Output        | `Assignment_03/outputs/mst_output.txt`     |

---

## Author

**Prashant Kumar**

**Entry Number:** 2026CSM1028

**Program:** M.Tech CSE

**Course:** CS509

---

> **CS509 Laboratory — Assignment 03**
