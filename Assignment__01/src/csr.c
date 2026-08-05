#include "csr.h"

adjacency_list read_unweighted_graph(const char *path)
{
    adjacency_list g;

    g.V = 0;
    g.E = 0;
    g.source = 0;
    g.weighted = 0;
    g.adj = NULL;
    g.degree = NULL;

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", path);
        return g;
    }

    fscanf(fp, "%d %d", &g.V, &g.E);

    g.degree = (int *)calloc(g.V, sizeof(int));
    g.adj = (Edge **)malloc(g.V * sizeof(Edge *));

    if (g.degree == NULL || g.adj == NULL)
    {
        printf("Memory allocation failed.\n");
        free(g.degree);
        free(g.adj);
        g.degree = NULL;
        g.adj = NULL;
        fclose(fp);
        return g;
    }

    for (int i = 0; i < g.V; i++)
    {
        int vertex;
        int deg;

        fscanf(fp, "%d %d", &vertex, &deg);

        g.degree[vertex] = deg;
        g.adj[vertex] = (Edge *)malloc(deg * sizeof(Edge));

        for (int j = 0; j < deg; j++)
        {
            int neighbour;
            fscanf(fp, "%d", &neighbour);

            g.adj[vertex][j].to = neighbour;
            g.adj[vertex][j].weight = 1.0;
        }
    }

    char word[20];
    g.source = 0;
    fscanf(fp, "%s %d", word, &g.source);

    fclose(fp);

    return g;
}

adjacency_list read_weighted_graph(const char *path)
{
    adjacency_list g;

    g.V = 0;
    g.E = 0;
    g.source = 0;
    g.weighted = 1;
    g.adj = NULL;
    g.degree = NULL;

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", path);
        return g;
    }

    fscanf(fp, "%d %d", &g.V, &g.E);

    g.degree = (int *)calloc(g.V, sizeof(int));
    g.adj = (Edge **)malloc(g.V * sizeof(Edge *));

    if (g.degree == NULL || g.adj == NULL)
    {
        printf("Memory allocation failed.\n");
        free(g.degree);
        free(g.adj);
        g.degree = NULL;
        g.adj = NULL;
        fclose(fp);
        return g;
    }

    for (int i = 0; i < g.V; i++)
    {
        int vertex;
        int deg;

        fscanf(fp, "%d %d", &vertex, &deg);

        g.degree[vertex] = deg;
        g.adj[vertex] = (Edge *)malloc(deg * sizeof(Edge));

        for (int j = 0; j < deg; j++)
        {
            int neighbour;
            double weight;

            fscanf(fp, "%d %lf", &neighbour, &weight);

            g.adj[vertex][j].to = neighbour;
            g.adj[vertex][j].weight = weight;
        }
    }

    char word[20];
    g.source = 0;
    fscanf(fp, "%s %d", word, &g.source);

    fclose(fp);

    return g;
}

void free_adjacency_list(adjacency_list *g)
{
    if (g == NULL)
        return;

    if (g->adj != NULL)
    {
        for (int i = 0; i < g->V; i++)
            free(g->adj[i]);

        free(g->adj);
    }

    free(g->degree);

    g->adj = NULL;
    g->degree = NULL;
}

csr_graph adjacency_list_to_csr(const adjacency_list *g)
{
    csr_graph csr;

    csr.V = g->V;

    // Use the sum of per-vertex degrees (the actual number of directed
    // entries in g->adj) rather than trusting g->E directly: if a caller
    // passes an E that doesn't match the real edge count, allocating by
    // g->E here would under-size col_idx/values and corrupt the heap
    // once the loop below writes past the end of the buffer.
    int total_edges = 0;
    for (int i = 0; i < g->V; i++)
        total_edges += g->degree[i];

    csr.row_ptr = (int *)malloc((g->V + 1) * sizeof(int));
    csr.col_idx = (int *)malloc(total_edges * sizeof(int));
    csr.values  = (double *)malloc(total_edges * sizeof(double));

    if (csr.row_ptr == NULL ||
        csr.col_idx == NULL ||
        csr.values == NULL)
    {
        printf("Memory allocation failed.\n");

        free(csr.row_ptr);
        free(csr.col_idx);
        free(csr.values);

        csr.row_ptr = NULL;
        csr.col_idx = NULL;
        csr.values = NULL;

        return csr;
    }

    int index = 0;
    csr.row_ptr[0] = 0;

    for (int i = 0; i < g->V; i++)
    {
        for (int j = 0; j < g->degree[i]; j++)
        {
            csr.col_idx[index] = g->adj[i][j].to;
            csr.values[index] = g->adj[i][j].weight;
            index++;
        }

        csr.row_ptr[i + 1] = index;
    }

    return csr;
}

void free_csr_graph(csr_graph *csr)
{
    if (csr == NULL)
        return;

    free(csr->row_ptr);
    free(csr->col_idx);
    free(csr->values);

    csr->row_ptr = NULL;
    csr->col_idx = NULL;
    csr->values = NULL;
}