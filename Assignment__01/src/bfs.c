#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

bfs_result bfs(const csr_graph *graph, int source)
{
    int V = graph->V;

    bfs_result result;
    result.traversal = (int *)malloc(V * sizeof(int));
    result.distance = (int *)malloc(V * sizeof(int));
    result.traversal_size = 0;

    int *visited = (int *)calloc(V, sizeof(int));
    int *queue = (int *)malloc(V * sizeof(int));

    if (result.traversal == NULL || result.distance == NULL ||
        visited == NULL || queue == NULL)
    {
        printf("Memory allocation failed.\n");

        free(result.traversal);
        free(result.distance);
        free(visited);
        free(queue);

        result.traversal = NULL;
        result.distance = NULL;
        result.traversal_size = 0;

        return result;
    }

    for (int i = 0; i < V; i++)
    {
        result.distance[i] = -1;
    }

    int front = 0;
    int rear = 0;

    visited[source] = 1;
    result.distance[source] = 0;

    queue[rear++] = source;

    while (front < rear)
    {
        int current = queue[front++];

        result.traversal[result.traversal_size++] = current;

        for (int i = graph->row_ptr[current];
             i < graph->row_ptr[current + 1];
             i++)
        {
            int neighbour = graph->col_idx[i];

            if (!visited[neighbour])
            {
                visited[neighbour] = 1;
                result.distance[neighbour] = result.distance[current] + 1;

                queue[rear++] = neighbour;
            }
        }
    }

    free(visited);
    free(queue);

    return result;
}

void free_bfs_result(bfs_result *result)
{
    if (result == NULL)
        return;

    free(result->traversal);
    free(result->distance);

    result->traversal = NULL;
    result->distance = NULL;
    result->traversal_size = 0;
}
