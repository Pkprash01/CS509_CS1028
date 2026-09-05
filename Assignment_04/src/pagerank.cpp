#include "pagerank.hpp"
#include <cmath>
#include <chrono>

PageRankResult run_pagerank(const CSRGraph& graph, double damping, double tolerance, int max_iterations) {
    int N = graph.V;

    auto start = std::chrono::high_resolution_clock::now();

    double* pr_old = new double[N];
    double* pr_new = new double[N];

    double initial_val = 1.0 / (double)N;
    for (int i = 0; i < N; ++i) {
        pr_old[i] = initial_val;
    }

    int* out_degree = new int[N];
    for (int u = 0; u < N; ++u) {
        out_degree[u] = graph.row_ptr[u + 1] - graph.row_ptr[u];
    }

    double base_rank = (1.0 - damping) / (double)N;
    int iter = 0;
    bool converged = false;

    while (iter < max_iterations) {
        iter++;

        for (int i = 0; i < N; ++i) {
            pr_new[i] = base_rank;
        }

        double dangling_sum = 0.0;
        for (int u = 0; u < N; ++u) {
            if (out_degree[u] == 0) {
                dangling_sum += pr_old[u];
            } else {
                double contrib = damping * (pr_old[u] / (double)out_degree[u]);
                for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; ++e) {
                    int v = graph.col_idx[e];
                    pr_new[v] += contrib;
                }
            }
        }

        double dangling_contrib = damping * (dangling_sum / (double)N);
        for (int i = 0; i < N; ++i) {
            pr_new[i] += dangling_contrib;
        }

        double diff = 0.0;
        for (int i = 0; i < N; ++i) {
            diff += std::fabs(pr_new[i] - pr_old[i]);
            pr_old[i] = pr_new[i];
        }

        if (diff <= tolerance) {
            converged = true;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    delete[] pr_old;
    delete[] out_degree;

    PageRankResult res;
    res.ranks = pr_new;
    res.iterations = iter;
    res.converged = converged;
    res.execution_time_ms = elapsed.count();

    return res;
}

void free_pagerank_result(PageRankResult& result) {
    if (result.ranks != nullptr) {
        delete[] result.ranks;
        result.ranks = nullptr;
    }
}