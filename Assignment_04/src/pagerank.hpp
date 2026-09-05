#ifndef PAGERANK_HPP
#define PAGERANK_HPP

#include "../../individual_csr/individual_csr.hpp"

struct PageRankResult {
    double* ranks;
    int iterations;
    bool converged;
    double execution_time_ms;
};

PageRankResult run_pagerank(const CSRGraph& graph, double damping, double tolerance, int max_iterations);
void free_pagerank_result(PageRankResult& result);

#endif