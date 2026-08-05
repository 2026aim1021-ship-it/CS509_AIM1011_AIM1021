#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

static void dfs_visit(const csr_graph *graph, int vertex, int visited[], dfs_result *result)
{
    visited[vertex] = 1;

    result->traversal[result->traversal_size++] = vertex;

    for (int i = graph->row_ptr[vertex];
         i < graph->row_ptr[vertex + 1];
         i++)
    {
        int neighbour = graph->col_idx[i];

        if (!visited[neighbour])
        {
            dfs_visit(graph, neighbour, visited, result);
        }
    }
}

dfs_result dfs(const csr_graph *graph, int source)
{
    int V = graph->V;

    dfs_result result;
    result.traversal = (int *)malloc(V * sizeof(int));
    result.traversal_size = 0;

    int *visited = (int *)calloc(V, sizeof(int));

    if (result.traversal == NULL || visited == NULL)
    {
        printf("Memory allocation failed.\n");

        free(result.traversal);
        free(visited);

        result.traversal = NULL;
        result.traversal_size = 0;

        return result;
    }

    dfs_visit(graph, source, visited, &result);

    free(visited);

    return result;
}

void free_dfs_result(dfs_result *result)
{
    if (result == NULL)
        return;

    free(result->traversal);

    result->traversal = NULL;
    result->traversal_size = 0;
}
