#ifndef MST_HPP
#define MST_HPP

#include "../../individual_csr/individual_csr.hpp"

struct Edge {
    int u;
    int v;
    int weight;
};

struct MSTResult {
    Edge* edges;
    long long total_weight;
    double execution_time_ms;
};

MSTResult run_kruskal(const CSRGraph& graph);
MSTResult run_prim(const CSRGraph& graph);
void free_mst_result(MSTResult& result);

#endif