#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <string>

//Raw C-style dynamic CSR structure
struct CSRGraph {
    int V;          // Total vertices
    int E;          // Total edges
    int* row_ptr;   // Size: V + 1
    int* col_idx;   // Size: E
    int* values;    // Size: E (Edge weights; NULL for unweighted graphs)
};

//Converts unweighted adjacency-list file (BFS/DFS) to CSR
CSRGraph load_unweighted_csr(const std::string& filepath, int& source_vertex);

//Converts weighted adjacency-list file (SSSP) to CSR
CSRGraph load_weighted_csr(const std::string& filepath, int& source_vertex);

//Memory cleanup helper
void free_csr_graph(CSRGraph& graph);

#endif // CSR_GRAPH_HPP