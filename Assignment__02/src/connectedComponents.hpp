#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../Assignment__01/src/csr.h"
#ifdef __cplusplus
}
#endif

#include <vector>

// Finds connected components in an undirected graph.
// DFS from Assignment 1 is called once for every undiscovered component.
std::vector<int> connected_components(const csr_graph *graph, int &component_count);

#endif
