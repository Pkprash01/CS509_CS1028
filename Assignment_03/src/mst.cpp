#include "mst.hpp"
#include <chrono>

struct KruskalEdge {
    int u;
    int v;
    int weight;
};

static int find_parent(int* parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_parent(parent, parent[i]);
}

static bool union_sets(int* parent, int* rank_arr, int i, int j) {
    int root_i = find_parent(parent, i);
    int root_j = find_parent(parent, j);
    if (root_i != root_j) {
        if (rank_arr[root_i] < rank_arr[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_arr[root_i] > rank_arr[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank_arr[root_i]++;
        }
        return true;
    }
    return false;
}

static void sort_edges(KruskalEdge* edges, int n) {
    for (int i = 1; i < n; ++i) {
        KruskalEdge key = edges[i];
        int j = i - 1;
        while (j >= 0 && edges[j].weight > key.weight) {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }
}

MSTResult run_kruskal(const CSRGraph& graph) {
    int V = graph.V;
    int E = graph.E;

    KruskalEdge* all_edges = new KruskalEdge[E];
    int edge_count = 0;

    for (int u = 0; u < V; ++u) {
        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u + 1];

        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_idx[e];
            int w = graph.values[e];
            if (u < v) {
                all_edges[edge_count++] = {u, v, w};
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    sort_edges(all_edges, edge_count);

    int* parent = new int[V];
    int* rank_arr = new int[V];
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        rank_arr[i] = 0;
    }

    Edge* mst_edges = new Edge[V - 1];
    int selected_count = 0;
    long long total_weight = 0;

    for (int i = 0; i < edge_count && selected_count < V - 1; ++i) {
        if (union_sets(parent, rank_arr, all_edges[i].u, all_edges[i].v)) {
            mst_edges[selected_count++] = {all_edges[i].u, all_edges[i].v, all_edges[i].weight};
            total_weight += all_edges[i].weight;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    delete[] all_edges;
    delete[] parent;
    delete[] rank_arr;

    MSTResult result;
    result.edges = mst_edges;
    result.total_weight = total_weight;
    result.execution_time_ms = elapsed.count();

    return result;
}

MSTResult run_prim(const CSRGraph& graph) {
    int V = graph.V;

    bool* in_mst = new bool[V];
    int* min_weight = new int[V];
    int* parent_node = new int[V];

    for (int i = 0; i < V; ++i) {
        in_mst[i] = false;
        min_weight[i] = 2147483647;
        parent_node[i] = -1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    min_weight[0] = 0;
    long long total_weight = 0;
    int selected_edges_count = 0;
    Edge* mst_edges = new Edge[V - 1];

    for (int i = 0; i < V; ++i) {
        int u = -1;
        int min_val = 2147483647;
        for (int v = 0; v < V; ++v) {
            if (!in_mst[v] && min_weight[v] < min_val) {
                min_val = min_weight[v];
                u = v;
            }
        }

        if (u == -1) break;

        in_mst[u] = true;

        if (parent_node[u] != -1) {
            mst_edges[selected_edges_count++] = {parent_node[u], u, min_weight[u]};
            total_weight += min_weight[u];
        }

        int start_edge = graph.row_ptr[u];
        int end_edge = graph.row_ptr[u + 1];

        for (int e = start_edge; e < end_edge; ++e) {
            int v = graph.col_idx[e];
            int weight = graph.values[e];

            if (!in_mst[v] && weight < min_weight[v]) {
                min_weight[v] = weight;
                parent_node[v] = u;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    delete[] in_mst;
    delete[] min_weight;
    delete[] parent_node;

    MSTResult result;
    result.edges = mst_edges;
    result.total_weight = total_weight;
    result.execution_time_ms = elapsed.count();

    return result;
}

void free_mst_result(MSTResult& result) {
    if (result.edges != nullptr) {
        delete[] result.edges;
        result.edges = nullptr;
    }
}