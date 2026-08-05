#include <stdio.h>
#include <stdlib.h>
#include "csr.h"

static void dfs_visit(CSRGraph *csr, int vertex, int visited[])
{
    visited[vertex] = 1;

    printf("%d ", vertex);

    for (int i = csr->row_ptr[vertex];
         i < csr->row_ptr[vertex + 1];
         i++)
    {
        int neighbour = csr->col_idx[i];

        if (!visited[neighbour])
        {
            dfs_visit(csr, neighbour, visited);
        }
    }
}

void dfs(CSRGraph *csr, int source)
{
    int V = csr->vertices;

    int *visited = (int *)calloc(V, sizeof(int));

    if (visited == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Algorithm : DFS\n");
    printf("Source    : %d\n", source);
    printf("Traversal : ");

    dfs_visit(csr, source, visited);

    printf("\n");

    free(visited);
}
