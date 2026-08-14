#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../individual_csr/individual_csr.hpp"
#include "../src/mst.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graph_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    int dummy_source = 0;

    // Load weighted undirected graph using CSR loader (Setup work - excluded from timer)
    CSRGraph graph = load_weighted_csr(filepath, dummy_source, false);
    if (graph.V == 0) {
        std::cerr << "[ERROR] Failed to load weighted MST graph.\n";
        return 1;
    }

    // Run Kruskal's Algorithm
    MSTResult kruskal_res = run_kruskal(graph);

    // Run Prim's Algorithm
    MSTResult prim_res = run_prim(graph);

    // Print Kruskal's output format matching Section 5.3
    std::cout << "Algorithm: Kruskal's MST\n";
    std::cout << "MST edges:\n";
    for (int i = 0; i < graph.V - 1; ++i) {
        std::cout << kruskal_res.edges[i].u << " " 
                  << kruskal_res.edges[i].v << " " 
                  << kruskal_res.edges[i].weight << "\n";
    }
    std::cout << "Total MST weight: " << kruskal_res.total_weight << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << kruskal_res.execution_time_ms << " ms\n\n";

    // Print Prim's output format matching Section 5.3
    std::cout << "Algorithm: Prim's MST\n";
    std::cout << "MST edges:\n";
    for (int i = 0; i < graph.V - 1; ++i) {
        std::cout << prim_res.edges[i].u << " " 
                  << prim_res.edges[i].v << " " 
                  << prim_res.edges[i].weight << "\n";
    }
    std::cout << "Total MST weight: " << prim_res.total_weight << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << prim_res.execution_time_ms << " ms\n";

    // Clean up allocated memory cleanly
    free_mst_result(kruskal_res);
    free_mst_result(prim_res);
    free_csr_graph(graph);

    return 0;
}