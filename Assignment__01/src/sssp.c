#include <stdio.h>
#include <time.h>

#define mV 100
#define mE 100
#define INF 1000000000

int V, E, source;

int edgeFrom[mE], edgeTo[mE], wt[mE];
int degree[mV];
int idx[mV + 1], nei[mE], val[mE];

int dist[mV], visited[mV];

void readGraph(char *f)
{
    FILE *file = fopen(f, "r");

    if (file == NULL)
    {
        printf("Unable to open input file %s\n", f);
        return;
    }

    fscanf(file, "%d %d", &V, &E);

    for (int i = 0; i < E; i++)
        fscanf(file, "%d %d", &edgeFrom[i], &edgeTo[i]);

    for (int i = 0; i < E; i++)
        fscanf(file, "%d", &wt[i]);

    fscanf(file, "%d", &source);

    fclose(file);
}

void makeCSR()
{
    for (int i = 0; i < V; i++)
        degree[i] = 0;

    for (int i = 0; i < E; i++)
        degree[edgeFrom[i]]++;

    idx[0] = 0;

    for (int i = 0; i < V; i++)
        idx[i + 1] = idx[i] + degree[i];

    int pos[mV];

    for (int i = 0; i < V; i++)
        pos[i] = idx[i];

    for (int i = 0; i < E; i++)
    {
        int u = edgeFrom[i];

        nei[pos[u]] = edgeTo[i];
        val[pos[u]] = wt[i];

        pos[u]++;
    }
}

void dijkstra()
{
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int k = 0; k < V; k++)
    {
        int u = -1;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int i = idx[u]; i < idx[u + 1]; i++)
        {
            int v = nei[i];

            if (!visited[v] && dist[u] + val[i] < dist[v])
                dist[v] = dist[u] + val[i];
        }
    }
}

void printDistance()
{
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INF)
            printf("%d INF\n", i);
        else
            printf("%d %d\n", i, dist[i]);
    }
}

// This main() is only for building sssp.c as a standalone program
// (gcc -DSSSP_STANDALONE_MAIN src/sssp.c -o sssp). It is compiled out when
// sssp.c is linked into driver/main.c, which already defines main() and
// calls readGraph/makeCSR/dijkstra/printDistance directly for choice 3.
#ifdef SSSP_STANDALONE_MAIN
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s inputfile\n", argv[0]);
        return 1;
    }

    readGraph(argv[1]);
    makeCSR();

    clock_t start = clock();

    dijkstra();

    clock_t end = clock();

    double totalTime = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("Algorithm : SSSP\n");
    printf("Source : %d\n", source);
    printf("Vertex Distance\n");

    printDistance();

    printf("Execution Time : %.3f ms\n", totalTime);

    return 0;
}
#endif