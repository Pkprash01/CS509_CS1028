#ifndef VERTEX_COLORING_HPP
#define VERTEX_COLORING_HPP

#include "../../individual_csr/individual_csr.hpp"

struct ColoringResult {
    int* colors;
    int total_colors;
    double execution_time_ms;
};

ColoringResult run_vertex_coloring(const CSRGraph& graph);
void free_coloring_result(ColoringResult& result);

#endif