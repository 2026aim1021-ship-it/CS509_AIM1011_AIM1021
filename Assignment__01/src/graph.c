#include "graph.h"
#include <string.h>

// Linked-list adjacency representation (legacy loader, not used by the CSR
// driver but kept buildable). Node/Graph were previously declared in an
// older version of graph.h; they are defined locally here since bfs_result
// and dfs_result now live in graph.h instead.
typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct {
    int vertices;
    int edges;
    int source;
    Node **adj_list;
} Graph;

static Node *create_node(int vertex, int weight)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

Graph *read_graph(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));

    if (graph == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    fscanf(fp, "%d %d", &graph->vertices, &graph->edges);

    graph->adj_list = (Node **)calloc(graph->vertices, sizeof(Node *));
    graph->source = -1;

    if (graph->adj_list == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fp);
        free(graph);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        int vertex;
        int degree;

        fscanf(fp, "%d %d", &vertex, &degree);

        Node *tail = NULL;

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            fscanf(fp, "%d", &neighbour);

            Node *new_node = create_node(neighbour, 1);

            if (graph->adj_list[vertex] == NULL)
            {
                graph->adj_list[vertex] = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    char word[20];

    fscanf(fp, "%s %d", word, &graph->source);

    fclose(fp);

    return graph;
}


// Renamed from read_weighted_graph to avoid conflicting with the
// "adjacency_list read_weighted_graph(const char *path)" declared in csr.h.
Graph *read_graph_weighted(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));

    if (graph == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    fscanf(fp, "%d %d", &graph->vertices, &graph->edges);

    graph->adj_list = (Node **)calloc(graph->vertices, sizeof(Node *));
    graph->source = -1;

    if (graph->adj_list == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fp);
        free(graph);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        int vertex;
        int degree;

        fscanf(fp, "%d %d", &vertex, &degree);

        Node *tail = NULL;

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            int weight;

            fscanf(fp, "%d %d", &neighbour, &weight);

            Node *new_node = create_node(neighbour, weight);

            if (graph->adj_list[vertex] == NULL)
            {
                graph->adj_list[vertex] = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    char word[20];

    fscanf(fp, "%s %d", word, &graph->source);

    fclose(fp);

    return graph;
}

void free_graph(Graph *graph)
{
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertices; i++)
    {
        Node *current = graph->adj_list[i];

        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adj_list);
    free(graph);
}