#ifndef MAXFLOW_MINCUT_H
#define MAXFLOW_MINCUT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../Assignment__01/src/csr.h"
#ifdef __cplusplus
}
#endif

#include <vector>
#include <string>

// One directed capacity edge, as read from the input file (Section 7.1).
struct mf_edge {
    int from;
    int to;
    long long capacity;
};

struct mf_input {
    adjacency_list graph;  // directed adjacency list; weight field holds capacity
    int source;
    int sink;
    bool valid;
    std::string error;
};

struct mf_result {
    long long max_flow;
    long long min_cut_capacity;
    std::vector<int> source_side;
    std::vector<int> sink_side;
    std::vector<mf_edge> cut_edges;
};

// Reads and validates a Maxflow-Mincut input file (Section 7.1 format).
// Builds an adjacency_list; the caller converts it to CSR with Assignment
// 1's adjacency_list_to_csr() -- this file does not duplicate that
// conversion, per the assignment instructions.
mf_input read_maxflow_input(const std::string &path);

// Runs Dinic's max-flow algorithm on the CSR graph and extracts the
// minimum cut from the final residual graph. Building the residual
// network from the CSR is part of this timed call.
mf_result maxflow_mincut(const csr_graph *graph, int source, int sink);

#endif
