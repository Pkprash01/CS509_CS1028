#ifndef INDIVIDUAL_CSR_HPP
#define INDIVIDUAL_CSR_HPP

#include <string>

struct CSRGraph {
    int V;
    int E;
    int* row_ptr;
    int* col_idx;
    int* values;
};

CSRGraph load_unweighted_csr(const std::string& filepath, int& source_vertex);
CSRGraph load_weighted_csr(const std::string& filepath, int& source_vertex, bool is_directed = true);
void free_csr_graph(CSRGraph& graph);

#endif