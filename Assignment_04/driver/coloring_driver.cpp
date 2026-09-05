#include <iostream>
#include <iomanip>
#include "../../individual_csr/individual_csr.hpp"
#include "../src/vertex_coloring.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graph_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    int dummy_source = 0;

    // Load unweighted undirected graph using your existing shared CSR module
    CSRGraph graph = load_unweighted_csr(filepath, dummy_source);
    if (graph.V == 0) {
        std::cerr << "[ERROR] Failed to load graph file at: " << filepath << "\n";
        return 1;
    }

    // Execute Welsh-Powell Greedy Coloring
    ColoringResult res = run_vertex_coloring(graph);

    // Section 5.3 expected output format
    std::cout << "Algorithm: Greedy Vertex Coloring\n";
    std::cout << "Vertex colors:\n";
    for (int i = 0; i < graph.V; ++i) {
        std::cout << i << " " << res.colors[i] << "\n";
    }
    std::cout << "Colors used: " << res.total_colors << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << res.execution_time_ms << " ms\n";

    // Clean up allocated memory
    free_coloring_result(res);
    free_csr_graph(graph);

    return 0;
}