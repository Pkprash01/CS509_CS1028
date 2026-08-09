#ifndef FLOYDWARSHALL_HPP
#define FLOYDWARSHALL_HPP

#include <string>
#include <limits>

// Define INF_VAL globally so both the implementation and driver can access it
const long long INF_VAL = std::numeric_limits<long long>::max() / 4;

struct FWGraph {
    int V;
    long long** dist_matrix; // Dense V x V matrix
};

struct FWResult {
    long long** dist;        // Shortest-distance matrix result
    bool has_negative_cycle;
    double execution_time_ms;
};

// Helper loader and memory management functions
FWGraph load_fw_graph(const std::string& filepath);
void free_fw_graph(FWGraph& graph);

// Algorithm execution and cleanup
FWResult run_floyd_warshall(const FWGraph& graph);
void free_fw_result(FWResult& result, int V);

#endif