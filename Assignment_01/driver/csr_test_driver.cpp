#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "../src/csr_graph.hpp"

int main(int argc, char* argv[]) {
    std::string test_path = "../tests/csr_input.txt";
    std::string output_path = "../outputs/csr_output.txt";

    if (argc >= 2) {
        test_path = argv[1];
    }
    if (argc >= 3) {
        output_path = argv[2];
    }

    int source = -1;
    
    // Timing rule: Measure only the conversion/algorithm execution time using high-precision double
    auto start_time = std::chrono::high_resolution_clock::now();
    CSRGraph g = load_unweighted_csr(test_path, source);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    if (g.row_ptr == nullptr) {
        std::cerr << "Error: Could not open or parse file at " << test_path << std::endl;
        return 1;
    }

    std::ofstream outfile(output_path);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open output file at " << output_path << std::endl;
        free_csr_graph(g);
        return 1;
    }

    outfile << "Algorithm: CSR Graph Conversion\n";
    outfile << "Vertices (V): " << g.V << " | Edges (E): " << g.E << " | Source: " << source << "\n";
    
    outfile << "row_ptr: ";
    for (int i = 0; i <= g.V; ++i) {
        outfile << g.row_ptr[i] << " ";
    }
    outfile << "\n";

    outfile << "col_idx: ";
    for (int i = 0; i < g.E; ++i) {
        outfile << g.col_idx[i] << " ";
    }
    outfile << "\n";
    
    outfile << "Execution time: " << std::fixed << std::setprecision(3) << duration.count() << " ms\n";

    std::cout << "Successfully processed " << test_path << " -> Output written to " << output_path 
              << " (" << std::fixed << std::setprecision(3) << duration.count() << " ms)\n";

    free_csr_graph(g);
    return 0;
}