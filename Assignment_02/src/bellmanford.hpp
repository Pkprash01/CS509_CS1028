#ifndef BELLMANFORD_HPP
#define BELLMANFORD_HPP

#include "../../individual_csr/individual_csr.hpp"
struct BellmanFordResult {
    long long* distances;
    bool has_negative_cycle;
    double execution_time_ms;
};

BellmanFordResult run_bellman_ford(const CSRGraph& graph, int source);
void free_bellman_ford_result(BellmanFordResult& result);

#endif