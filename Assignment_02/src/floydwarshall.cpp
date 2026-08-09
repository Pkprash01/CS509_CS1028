#include "floydwarshall.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Load dense V x V adjacency matrix from file (Setup work - excluded from timer)[cite: 2]
FWGraph load_fw_graph(const std::string& filepath) {
    FWGraph graph;
    graph.V = 0;
    graph.dist_matrix = nullptr;

    std::ifstream infile(filepath.c_str());
    if (!infile.is_open()) {
        return graph;
    }

    if (!(infile >> graph.V)) {
        infile.close();
        return graph;
    }

    // Allocate matrix
    graph.dist_matrix = new long long*[graph.V];
    for (int i = 0; i < graph.V; ++i) {
        graph.dist_matrix[i] = new long long[graph.V];
    }

    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            std::string token;
            if (!(infile >> token)) {
                infile.close();
                return graph;
            }
            if (token == "INF" || token == "inf") {
                graph.dist_matrix[i][j] = INF_VAL;
            } else {
                std::stringstream ss(token);
                ss >> graph.dist_matrix[i][j];
            }
        }
    }

    infile.close();
    return graph;
}

void free_fw_graph(FWGraph& graph) {
    if (graph.dist_matrix != nullptr) {
        for (int i = 0; i < graph.V; ++i) {
            delete[] graph.dist_matrix[i];
        }
        delete[] graph.dist_matrix;
        graph.dist_matrix = nullptr;
    }
    graph.V = 0;
}

// Run Floyd-Warshall algorithm (Timing rule: measure only algorithm execution)[cite: 2]
FWResult run_floyd_warshall(const FWGraph& graph) {
    int V = graph.V;
    
    // Allocate working distance matrix
    long long** dist = new long long*[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = new long long[V];
        for (int j = 0; j < V; ++j) {
            dist[i][j] = graph.dist_matrix[i][j];
        }
    }

    // Start timer strictly before algorithm execution[cite: 2]
    auto start = std::chrono::high_resolution_clock::now();

    // Core Floyd-Warshall DP transitions
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if (dist[i][k] >= INF_VAL) continue;
            for (int j = 0; j < V; ++j) {
                if (dist[k][j] >= INF_VAL) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Negative cycle check via diagonal inspection[cite: 2]
    bool negative_cycle = false;
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            negative_cycle = true;
            break;
        }
    }

    // Stop timer immediately after algorithm and check finish[cite: 2]
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    FWResult result;
    result.dist = dist;
    result.has_negative_cycle = negative_cycle;
    result.execution_time_ms = elapsed.count();

    return result;
}

void free_fw_result(FWResult& result, int V) {
    if (result.dist != nullptr) {
        for (int i = 0; i < V; ++i) {
            delete[] result.dist[i];
        }
        delete[] result.dist;
        result.dist = nullptr;
    }
}