#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <string>

struct CSRGraph {
    int V;
    int E;
    int* row_ptr;
    int* col_idx;
    int* values; // NULL if unweighted
};

// Function declarations
void free_csr_graph(CSRGraph& graph);
CSRGraph load_unweighted_csr(const std::string& filepath, int& source_vertex);
CSRGraph load_weighted_csr(const std::string& filepath, int& source_vertex);

#endif