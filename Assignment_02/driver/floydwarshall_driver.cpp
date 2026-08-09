#include <iostream>
#include <fstream>
#include <iomanip>
#include "../src/floydwarshall.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_matrix_file>\n";
        return 1;
    }

    std::string filepath = argv[1];

    // 1. Load dense adjacency matrix (Setup work - excluded from timer)[cite: 2]
    FWGraph graph = load_fw_graph(filepath);
    if (graph.V == 0) {
        std::cerr << "[ERROR] Failed to load Floyd-Warshall graph file.\n";
        return 1;
    }

    // 2. Run Floyd-Warshall algorithm
    FWResult fw_result = run_floyd_warshall(graph);

    // 3. Print output format strictly matching Section 6.3[cite: 2]
    std::cout << "Algorithm: Floyd-Warshall\n";
    std::cout << "Distance matrix:\n";

    if (fw_result.has_negative_cycle) {
        std::cout << "Negative cycle: true\n";
    } else {
        for (int i = 0; i < graph.V; ++i) {
            for (int j = 0; j < graph.V; ++j) {
                if (fw_result.dist[i][j] >= INF_VAL / 2) {
                    std::cout << "INF";
                } else {
                    std::cout << fw_result.dist[i][j];
                }
                if (j < graph.V - 1) std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Negative cycle: none\n";
    }
    
    // Print execution time with 4 decimal places of accuracy
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << fw_result.execution_time_ms << " ms\n";

    // Clean up allocated memory cleanly
    free_fw_result(fw_result, graph.V);
    free_fw_graph(graph);

    return 0;
}