#ifndef CSR_H
#define CSR_H

#include <stdio.h>
#include <stdlib.h>

// Edge Structure
typedef struct {
    int to;
    double weight;
} edge;

// Adjacency-list representation
typedef struct {
    int V;
    int E;
    int source;
    int weighted;
    edge **adj;
    int *degree;
} adjacency_list;

// CSRGraph
typedef struct {
    int V;
    int *row_ptr;
    int *col_idx;
    double *values;
} csr_graph;

// Reads unweighted Adjacency

adjacency_list read_unweighted_graph(const char *path);

// Reads weighted Adjacency

adjacency_list read_weighted_graph(const char *path);

// Converts Adjacency list to CSR

csr_graph adjacency_list_to_csr(const adjacency_list *g);

// Free Memory

void free_adjacency_list(adjacency_list *g);
void free_csr_graph(csr_graph *g);

#endif
