#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/csr.h"
#include "../src/graph.h"
#include "../src/sssp.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <algorithm> <inputfile>\n", argv[0]);
        printf("1 : BFS\n");
        printf("2 : DFS\n");
        printf("3 : SSSP\n");
        printf("4 : Exit\n");
        return 1;
    }

    int choice = atoi(argv[1]);

    if (choice == 1)
    {
        adjacency_list graph = read_unweighted_graph(argv[2]);

        if (graph.V <= 0)
        {
            printf("Failed to load graph from %s\n", argv[2]);
            return 1;
        }

        csr_graph csr = adjacency_list_to_csr(&graph);

        clock_t start = clock();

        bfs_result result = bfs(&csr, graph.source);

        clock_t end = clock();

        printf("Algorithm : BFS\n");
        printf("Source : %d\n", graph.source);

        printf("Traversal : ");
        for (int i = 0; i < result.traversal_size; i++)
            printf("%d ", result.traversal[i]);
        printf("\n");

        printf("Distances\n");
        for (int i = 0; i < graph.V; i++)
            printf("%d %d\n", i, result.distance[i]);

        printf("Execution Time : %.3f ms\n",
               1000.0 * (end - start) / CLOCKS_PER_SEC);

        free_bfs_result(&result);
        free_csr_graph(&csr);
        free_adjacency_list(&graph);
    }

    else if (choice == 2)
    {
        adjacency_list graph = read_unweighted_graph(argv[2]);

        if (graph.V <= 0)
        {
            printf("Failed to load graph from %s\n", argv[2]);
            return 1;
        }

        csr_graph csr = adjacency_list_to_csr(&graph);

        clock_t start = clock();

        dfs_result result = dfs(&csr, graph.source);

        clock_t end = clock();

        printf("Algorithm : DFS\n");
        printf("Source : %d\n", graph.source);

        printf("Traversal : ");
        for (int i = 0; i < result.traversal_size; i++)
            printf("%d ", result.traversal[i]);
        printf("\n");

        printf("Execution Time : %.3f ms\n",
               1000.0 * (end - start) / CLOCKS_PER_SEC);

        free_dfs_result(&result);
        free_csr_graph(&csr);
        free_adjacency_list(&graph);
    }

    else if (choice == 3)
    {
        readGraph(argv[2]);
        makeCSR();

        clock_t start = clock();

        dijkstra();

        clock_t end = clock();

        printf("Algorithm : SSSP\n");
        printf("Source : %d\n", source);
        printf("Vertex Distance\n");

        printDistance();

        printf("Execution Time : %.3f ms\n",
               1000.0 * (end - start) / CLOCKS_PER_SEC);
    }

    else if(choice == 4) {
        return 0;
    }

    else
    {
        printf("Invalid algorithm choice.\n");
    }

    return 0;
}