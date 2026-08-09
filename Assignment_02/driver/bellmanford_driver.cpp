#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../individual_csr/individual_csr.hpp"
#include "../src/bellmanford.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graph_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    int source_vertex = 0;

    // Load weighted graph using CSR loader (Setup work - excluded from timer as per rules)
    CSRGraph graph = load_weighted_csr(filepath, source_vertex, true);
    if (graph.V == 0) {
        std::cerr << "[ERROR] Failed to load graph.\n";
        return 1;
    }

    // Run Bellman-Ford algorithm
    BellmanFordResult bf_result = run_bellman_ford(graph, source_vertex);

    // Print exact required format from assignment guidelines
    std::cout << "Algorithm: Bellman-Ford\n";
    std::cout << "Source: " << source_vertex << "\n";
    std::cout << "Vertex Distance\n";

    if (bf_result.has_negative_cycle) {
        std::cout << "Negative cycle: true\n";
    } else {
        for (int i = 0; i < graph.V; ++i) {
            std::cout << i << "\t" << bf_result.distances[i] << "\n";
        }
        std::cout << "Negative cycle: none\n";
    }
    
    // Print execution time with 4 decimal places of accuracy
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << bf_result.execution_time_ms << " ms\n";

    // Clean up allocated memory
    free_bellman_ford_result(bf_result);
    free_csr_graph(graph);

    return 0;
}