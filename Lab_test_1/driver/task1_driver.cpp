#include "../../individual_csr/individual_csr_2.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_edge_list.txt>\n";
        return 1;
    }

    CSRGraph g = load_csr_from_edge_list(argv[1]);

    // 1. Print Offset Array (row_ptr)
    std::cout << "Offset Array (row_ptr):\n";
    for (int i = 0; i <= g.V; ++i) {
        std::cout << g.row_ptr[i] << (i == g.V ? "" : " ");
    }
    std::cout << "\n";

    // Total non-zeros is row_ptr[V]
    int total_nnz = (g.V == 0) ? 0 : g.row_ptr[g.V];

    // 2. Print Intermediate Array (col_idx)
    std::cout << "Intermediate Array (col_idx):\n";
    for (int i = 0; i < total_nnz; ++i) {
        std::cout << g.col_idx[i] << (i == total_nnz - 1 ? "" : " ");
    }
    std::cout << "\n";

    // 3. Print Property Array (values)
    std::cout << "Property Array (values):\n";
    for (int i = 0; i < total_nnz; ++i) {
        std::cout << g.values[i] << (i == total_nnz - 1 ? "" : " ");
    }
    std::cout << "\n";

    free_csr_graph(g);
    return 0;
}