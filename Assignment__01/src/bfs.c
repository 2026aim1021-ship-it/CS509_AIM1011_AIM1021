#include <stdio.h>
#include <stdlib.h>
#include "csr.h"

void bfs(csr_graph *csr, int source)
{
    int V = csr->vertices;

    int *visited = (int *)calloc(V, sizeof(int));
    int *distance = (int *)malloc(V * sizeof(int));
    int *queue = (int *)malloc(V * sizeof(int));

    if (visited == NULL || distance == NULL || queue == NULL)
    {
        printf("Memory allocation failed.\n");

        free(visited);
        free(distance);
        free(queue);

        return;
    }

    for (int i = 0; i < V; i++)
    {
        distance[i] = -1;
    }

    int front = 0;
    int rear = 0;

    visited[source] = 1;
    distance[source] = 0;

    queue[rear++] = source;

    printf("Algorithm : BFS\n");
    printf("Source    : %d\n", source);

    printf("Traversal : ");

    while (front < rear)
    {
        int current = queue[front++];

        printf("%d ", current);

        for (int i = csr->row_ptr[current];
             i < csr->row_ptr[current + 1];
             i++)
        {
            int neighbour = csr->col_idx[i];

            if (!visited[neighbour])
            {
                visited[neighbour] = 1;
                distance[neighbour] = distance[current] + 1;

                queue[rear++] = neighbour;
            }
        }
    }

    printf("\n");

    printf("Distances\n");

    for (int i = 0; i < V; i++)
    {
        printf("%d : ", i);

        if (distance[i] == -1)
            printf("INF\n");
        else
            printf("%d\n", distance[i]);
    }

    free(visited);
    free(distance);
    free(queue);
}
