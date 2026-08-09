#include "individual_csr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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