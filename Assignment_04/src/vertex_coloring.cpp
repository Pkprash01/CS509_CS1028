#include "vertex_coloring.hpp"
#include <chrono>

struct VertexNode {
    int id;
    int deg;
};

// Insertion sort for deterministic descending degree order (Welsh-Powell)
static void sort_vertices(VertexNode* nodes, int n) {
    for (int i = 1; i < n; ++i) {
        VertexNode key = nodes[i];
        int j = i - 1;
        while (j >= 0 && (nodes[j].deg < key.deg || (nodes[j].deg == key.deg && nodes[j].id > key.id))) {
            nodes[j + 1] = nodes[j];
            j--;
        }
        nodes[j + 1] = key;
    }
}

ColoringResult run_vertex_coloring(const CSRGraph& graph) {
    int V = graph.V;

    VertexNode* nodes = new VertexNode[V];
    for (int u = 0; u < V; ++u) {
        nodes[u].id = u;
        nodes[u].deg = graph.row_ptr[u + 1] - graph.row_ptr[u];
    }

    auto start = std::chrono::high_resolution_clock::now();

    sort_vertices(nodes, V);

    int* colors = new int[V];
    bool* unavailable = new bool[V];
    for (int i = 0; i < V; ++i) {
        colors[i] = -1;
        unavailable[i] = false;
    }

    int max_color = -1;

    for (int i = 0; i < V; ++i) {
        int u = nodes[i].id;
        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u + 1];

        // Mark colors of adjacent neighbors
        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_idx[e];
            if (colors[v] != -1) {
                unavailable[colors[v]] = true;
            }
        }

        // Pick lowest available color
        int c = 0;
        while (c < V && unavailable[c]) {
            c++;
        }

        colors[u] = c;
        if (c > max_color) {
            max_color = c;
        }

        // Reset flags for neighbors of u
        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_idx[e];
            if (colors[v] != -1) {
                unavailable[colors[v]] = false;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    delete[] nodes;
    delete[] unavailable;

    ColoringResult result;
    result.colors = colors;
    result.total_colors = (V == 0) ? 0 : (max_color + 1);
    result.execution_time_ms = elapsed.count();

    return result;
}

void free_coloring_result(ColoringResult& result) {
    if (result.colors != nullptr) {
        delete[] result.colors;
        result.colors = nullptr;
    }
}