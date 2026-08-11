#include "betweenness.hpp"

#include <algorithm>
#include <vector>

extern "C" {
#include "../../Assignment__01/src/graph.h"
}

using namespace std;

vector<double> betweenness_centrality(const csr_graph *graph)
{
    const int V = graph->V;
    vector<double> centrality(V, 0.0);

    // Brandes algorithm: run BFS from every source.
    for (int source = 0; source < V; ++source)
    {
        // BFS is the BFS implementation from Assignment 1.
        bfs_result bfs_result_data = bfs(graph, source);

        if (bfs_result_data.traversal == nullptr ||
            bfs_result_data.distance == nullptr)
        {
            free_bfs_result(&bfs_result_data);
            continue;
        }

        // sigma[v] = number of shortest paths from source to v.
        vector<double> sigma(V, 0.0);
        sigma[source] = 1.0;

        // Stack in BFS discovery order. It is reversed during dependency
        // accumulation, as required by Brandes' algorithm.
        vector<int> order;
        order.reserve(bfs_result_data.traversal_size);

        for (int i = 0; i < bfs_result_data.traversal_size; ++i)
            order.push_back(bfs_result_data.traversal[i]);

        // Reconstruct predecessor information using the distances returned
        // by Assignment 1 BFS. For an unweighted graph, u is a predecessor
        // of v exactly when dist[v] = dist[u] + 1.
        vector<vector<int>> predecessors(V);

        for (int u : order)
        {
            for (int i = graph->row_ptr[u];
                 i < graph->row_ptr[u + 1]; ++i)
            {
                const int v = graph->col_idx[i];

                if (bfs_result_data.distance[v] ==
                    bfs_result_data.distance[u] + 1)
                {
                    predecessors[v].push_back(u);
                    sigma[v] += sigma[u];
                }
            }
        }

        // dependency[v] = amount of source-to-other-vertex shortest-path
        // dependency that is accumulated at v.
        vector<double> dependency(V, 0.0);

        for (auto it = order.rbegin(); it != order.rend(); ++it)
        {
            const int w = *it;

            for (int v : predecessors[w])
            {
                if (sigma[w] != 0.0)
                {
                    dependency[v] +=
                        (sigma[v] / sigma[w]) * (1.0 + dependency[w]);
                }
            }

            if (w != source)
                centrality[w] += dependency[w];
        }

        free_bfs_result(&bfs_result_data);
    }

    // In an undirected graph every unordered pair is considered twice:
    // (s,t) and (t,s). Assignment 2 asks for the raw unnormalized value,
    // so divide only by 2 for this double counting.
    for (double &value : centrality)
        value /= 2.0;

    return centrality;
}
