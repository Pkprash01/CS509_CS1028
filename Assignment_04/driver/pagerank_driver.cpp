#include <iostream>
#include <fstream>
#include <iomanip>
#include "../../individual_csr/individual_csr.hpp"
#include "../src/pagerank.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graph_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    int dummy_source = 0;

    CSRGraph graph = load_unweighted_csr(filepath, dummy_source);
    if (graph.V == 0) {
        std::cerr << "[ERROR] Failed to load graph file at " << filepath << "\n";
        return 1;
    }

    double damping = 0.85;
    double tolerance = 0.0001;
    int max_iterations = 100;

    std::ifstream fin(filepath);
    std::string token;
    while (fin >> token) {
        if (token == "DAMPING") fin >> damping;
        else if (token == "TOLERANCE") fin >> tolerance;
        else if (token == "MAX_ITERATIONS") fin >> max_iterations;
    }
    fin.close();

    PageRankResult res = run_pagerank(graph, damping, tolerance, max_iterations);

    double sum_ranks = 0.0;
    for (int i = 0; i < graph.V; ++i) {
        sum_ranks += res.ranks[i];
    }

    std::cout << "Algorithm: PageRank\n";
    std::cout << "Damping: " << damping << "\n";
    std::cout << "Vertex ranks:\n";
    for (int i = 0; i < graph.V; ++i) {
        std::cout << i << " " << std::fixed << std::setprecision(6) << res.ranks[i] << "\n";
    }
    std::cout << "Sum of ranks: " << std::fixed << std::setprecision(6) << sum_ranks << "\n";
    std::cout << "Iterations: " << res.iterations << "\n";
    std::cout << "Converged: " << (res.converged ? "true" : "false") << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << res.execution_time_ms << " ms\n";

    free_pagerank_result(res);
    free_csr_graph(graph);

    return 0;
}