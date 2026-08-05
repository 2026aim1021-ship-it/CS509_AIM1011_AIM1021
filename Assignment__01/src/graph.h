#ifndef GRAPH_H
#define GRAPH_H

#include "csr.h"
#include <limits.h>
#include <float.h>

// BFS Result
typedef struct {
    int *traversal;
    int traversal_size;
    int *distance;
} bfs_result;

// DFS Result
typedef struct {
    int *traversal;
    int traversal_size;
} dfs_result;

// Breadth First Search
bfs_result bfs(const csr_graph *graph, int source);

//Depth First Search
dfs_result dfs(const csr_graph *graph, int source);

// Clean Memory
void free_bfs_result(bfs_result *result);
void free_dfs_result(dfs_result *result);

#endif
