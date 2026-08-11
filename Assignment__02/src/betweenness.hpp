#ifndef BETWEENNESS_H
#define BETWEENNESS_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../Assignment__01/src/csr.h"
#ifdef __cplusplus
}
#endif

#include <vector>

// Brandes' algorithm for unweighted undirected graphs.
// BFS from Assignment 1 is called internally for every source.
std::vector<double> betweenness_centrality(const csr_graph *graph);

#endif
