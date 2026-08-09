#include "bellmanford.hpp"
#include <iostream>
#include <chrono>
#include <limits>

static const long long BF_INF = std::numeric_limits<long long>::max();

BellmanFordResult run_bellman_ford(const CSRGraph& graph, int source) {
    int V = graph.V;
    long long* dist = new long long[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = BF_INF;
    }
    dist[source] = 0;

    auto start = std::chrono::high_resolution_clock::now(); 
    for (int i = 0; i < V - 1; ++i) {
        bool updated = false;
        for (int u = 0; u < V; ++u) {
            if (dist[u] == BF_INF) continue;
            
            int start_edge = graph.row_ptr[u];
            int end_edge = graph.row_ptr[u + 1];

            for (int e = start_edge; e < end_edge; ++e) {
                int v = graph.col_idx[e];
                long long weight = graph.values[e];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    bool negative_cycle = false;
    for (int u = 0; u < V; ++u) {
        if (dist[u] == BF_INF) continue;

        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u + 1];

        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_idx[e];
            long long weight = graph.values[e];

            if (dist[u] + weight < dist[v]) {
                negative_cycle = true;
                break;
            }
        }
        if (negative_cycle) break;
    }

    auto end = std::chrono::high_resolution_clock::now();     
    std::chrono::duration<double, std::milli> elapsed = end - start;

    BellmanFordResult result;
    result.distances = dist;
    result.has_negative_cycle = negative_cycle;
    result.execution_time_ms = elapsed.count();

    return result;
}

void free_bellman_ford_result(BellmanFordResult& result) {
    if (result.distances != nullptr) {
        delete[] result.distances;
        result.distances = nullptr;
    }
}