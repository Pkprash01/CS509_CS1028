#include "csr_graph.hpp"
#include <iostream>
#include <fstream>
#include <cstddef>

void free_csr_graph(CSRGraph& graph) {
    if (graph.row_ptr != NULL) { delete[] graph.row_ptr; graph.row_ptr = NULL; }
    if (graph.col_idx != NULL) { delete[] graph.col_idx; graph.col_idx = NULL; }
    if (graph.values  != NULL) { delete[] graph.values;  graph.values  = NULL; }
    graph.V = 0;
    graph.E = 0;
}

//Unweighted CSR Conversion Helper
CSRGraph load_unweighted_csr(const std::string& filepath, int& source_vertex) {
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file at " << filepath << std::endl;
        return {0, 0, NULL, NULL, NULL};
    }

    int V, E;
    infile >> V >> E;

    int* row_ptr = new int[V + 1];
    int* col_idx = new int[E];
    
    row_ptr[0] = 0;
    int edge_count = 0;

    for (int i = 0; i < V; ++i) {
        int u, degree;
        infile >> u >> degree;

        for (int d = 0; d < degree; ++d) {
            int neighbor;
            infile >> neighbor;
            col_idx[edge_count++] = neighbor;
        }
        row_ptr[u + 1] = edge_count;
    }

    std::string label;
    if (infile >> label >> source_vertex) {
        //Source successfully parsed
    }

    infile.close();

    CSRGraph graph;
    graph.V = V;
    graph.E = E;
    graph.row_ptr = row_ptr;
    graph.col_idx = col_idx;
    graph.values = NULL; //Unweighted

    return graph;
}

//Weighted CSR Conversion Helper
CSRGraph load_weighted_csr(const std::string& filepath, int& source_vertex) {
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file at " << filepath << std::endl;
        return {0, 0, NULL, NULL, NULL};
    }

    int V, E;
    infile >> V >> E;

    int* row_ptr = new int[V + 1];
    int* col_idx = new int[E];
    int* values  = new int[E];
    
    row_ptr[0] = 0;
    int edge_count = 0;

    for (int i = 0; i < V; ++i) {
        int u, degree;
        infile >> u >> degree;

        for (int d = 0; d < degree; ++d) {
            int neighbor, weight;
            infile >> neighbor >> weight;
            col_idx[edge_count] = neighbor;
            values[edge_count]  = weight;
            edge_count++;
        }
        row_ptr[u + 1] = edge_count;
    }

    std::string label;
    if (infile >> label >> source_vertex) {
        //Source successfully parsed
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