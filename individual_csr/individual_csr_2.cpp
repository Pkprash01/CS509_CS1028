#include "individual_csr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

void free_csr_graph(CSRGraph& graph) {
    if (graph.row_ptr != nullptr) { delete[] graph.row_ptr; graph.row_ptr = nullptr; }
    if (graph.col_idx != nullptr) { delete[] graph.col_idx; graph.col_idx = nullptr; }
    if (graph.values  != nullptr) { delete[] graph.values;  graph.values  = nullptr; }
    graph.V = 0;
    graph.E = 0;
}

CSRGraph load_unweighted_csr(const std::string& filepath, int& source_vertex) {
    std::ifstream infile(filepath.c_str());
    if (!infile.is_open()) {
        std::cerr << "[FILE ERROR] Could not open file at: " << filepath << std::endl;
        return {0, 0, nullptr, nullptr, nullptr};
    }

    int V, E;
    if (!(infile >> V >> E)) {
        std::cerr << "[PARSER ERROR] Invalid V E header in " << filepath << std::endl;
        infile.close();
        return {0, 0, nullptr, nullptr, nullptr};
    }

    int* row_ptr = new int[V + 1];
    row_ptr[0] = 0;

    int max_entries = (2 * E > E) ? (2 * E) : E;
    int* col_idx = new int[max_entries];
    
    int edge_count = 0;

    for (int i = 0; i < V; ++i) {
        int u, degree;
        if (!(infile >> u >> degree)) break;

        for (int d = 0; d < degree; ++d) {
            int neighbor;
            infile >> neighbor;
            col_idx[edge_count++] = neighbor;
        }
        row_ptr[u + 1] = edge_count;
    }

    std::string label;
    if (!(infile >> label >> source_vertex)) {
        source_vertex = 0;
    }

    infile.close();

    CSRGraph graph;
    graph.V = V;
    graph.E = E;
    graph.row_ptr = row_ptr;
    graph.col_idx = col_idx;
    graph.values = nullptr;

    return graph;
}

CSRGraph load_weighted_csr(const std::string& filepath, int& source_vertex, bool is_directed) {
    std::ifstream infile(filepath.c_str());
    if (!infile.is_open()) {
        std::cerr << "[FILE ERROR] Could not open file at: " << filepath << std::endl;
        return {0, 0, nullptr, nullptr, nullptr};
    }

    int V, E;
    if (!(infile >> V >> E)) {
        std::cerr << "[PARSER ERROR] Invalid V E header in " << filepath << std::endl;
        infile.close();
        return {0, 0, nullptr, nullptr, nullptr};
    }

    int* row_ptr = new int[V + 1];
    row_ptr[0] = 0;

    int max_entries = (2 * E > E) ? (2 * E) : E;
    int* col_idx = new int[max_entries];
    int* values  = new int[max_entries];
    
    int edge_count = 0;

    for (int i = 0; i < V; ++i) {
        int u, degree;
        if (!(infile >> u >> degree)) break;

        for (int d = 0; d < degree; ++d) {
            int neighbor, weight;
            infile >> neighbor >> weight;

            if (!is_directed && weight < 0) {
                std::cerr << "[VALIDATION ERROR] Negative weight found on undirected edge at vertex " << u << " -> " << neighbor << std::endl;
                infile.close();
                delete[] row_ptr;
                delete[] col_idx;
                delete[] values;
                exit(1);
            }

            col_idx[edge_count] = neighbor;
            values[edge_count]  = weight;
            edge_count++;
        }
        row_ptr[u + 1] = edge_count;
    }

    std::string label;
    if (!(infile >> label >> source_vertex)) {
        source_vertex = 0;
    }

    infile.close();

    CSRGraph graph;
    graph.V = V;
    graph.E = E;
    graph.row_ptr = row_ptr;
    graph.col_idx = col_idx;
    graph.values = values;

    return graph;
}

struct RawEdge {
    int u, v, w;
};

CSRGraph load_csr_from_edge_list(const std::string& filepath) {
    std::ifstream infile(filepath.c_str());
    if (!infile.is_open()) {
        std::cerr << "[FILE ERROR] Could not open file at: " << filepath << std::endl;
        return {0, 0, nullptr, nullptr, nullptr};
    }

    char graph_type;
    if (!(infile >> graph_type)) {
        infile.close();
        return {0, 0, nullptr, nullptr, nullptr};
    }
    bool is_directed = (graph_type == 'D' || graph_type == 'd');

    struct RawEdge { int u, v, w; };
    std::vector<RawEdge> edge_buffer;
    int max_vertex_id = -1;
    int u, v, w;

    // Step 1: Read all edges until EOF and find max vertex ID
    while (infile >> u >> v >> w) {
        edge_buffer.push_back({u, v, w});
        if (u > max_vertex_id) max_vertex_id = u;
        if (v > max_vertex_id) max_vertex_id = v;
    }
    infile.close();

    int V = (max_vertex_id == -1) ? 0 : (max_vertex_id + 1);
    int E = edge_buffer.size();

    // Step 2: Compute degrees for each vertex
    std::vector<int> count_degree(V, 0);
    for (const auto& edge : edge_buffer) {
        count_degree[edge.u]++;
        if (!is_directed && edge.u != edge.v) {
            count_degree[edge.v]++;
        }
    }

    // Step 3: Prefix sum to build row_ptr
    int* row_ptr = new int[V + 1];
    row_ptr[0] = 0;
    for (int i = 0; i < V; ++i) {
        row_ptr[i + 1] = row_ptr[i] + count_degree[i];
    }

    int total_nnz = (V == 0) ? 0 : row_ptr[V];
    int* col_idx = new int[total_nnz];
    int* values  = new int[total_nnz];

    // Step 4: Populate col_idx and values
    std::vector<int> curr_pos(row_ptr, row_ptr + V);
    for (const auto& edge : edge_buffer) {
        int idx = curr_pos[edge.u]++;
        col_idx[idx] = edge.v;
        values[idx]  = edge.w;

        if (!is_directed && edge.u != edge.v) {
            int rev_idx = curr_pos[edge.v]++;
            col_idx[rev_idx] = edge.u;
            values[rev_idx]  = edge.w;
        }
    }

    // Step 5: Sort each vertex's neighbor slice in ascending order of col_idx
    for (int i = 0; i < V; ++i) {
        int start = row_ptr[i];
        int end = row_ptr[i + 1];
        int deg = end - start;
        if (deg > 1) {
            // Simple in-place sort paired with values
            for (int a = start; a < end - 1; ++a) {
                for (int b = a + 1; b < end; ++b) {
                    if (col_idx[a] > col_idx[b]) {
                        std::swap(col_idx[a], col_idx[b]);
                        std::swap(values[a], values[b]);
                    }
                }
            }
        }
    }

    CSRGraph graph;
    graph.V = V;
    graph.E = E;
    graph.row_ptr = row_ptr;
    graph.col_idx = col_idx;
    graph.values = values;

    return graph;
}