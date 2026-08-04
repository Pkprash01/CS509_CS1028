#include <iostream>
#include <fstream>
#include "../src/csr_graph.hpp"

int main() {
    std::string test_path = "../tests/csr_input.txt";
    int source = -1;
    
    CSRGraph g = load_unweighted_csr(test_path, source);

    if (g.row_ptr == NULL) {
        std::cout << "Error: Could not open file at " << test_path << std::endl;
        return 1;
    }

    std::cout << "CSR parsing test success!" << std::endl;
    std::cout << "V: " << g.V << " | E: " << g.E << " | Source: " << source << std::endl;

    std::cout << "row_ptr: ";
    for (int i = 0; i <= g.V; ++i) {
        std::cout << g.row_ptr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "col_idx: ";
    for (int i = 0; i < g.E; ++i) {
        std::cout << g.col_idx[i] << " ";
    }
    std::cout << std::endl;

    free_csr_graph(g);
    return 0;
}