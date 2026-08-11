#include "connectedComponents.hpp"

#include <vector>

extern "C" {
#include "../../Assignment__01/src/graph.h"
}

using namespace std;

std::vector<int> connected_components(const csr_graph *graph, int &component_count)
{
    const int V = graph->V;
    vector<int> component_id(V, -1);
    component_count = 0;

    // Each new undiscovered vertex starts one new component.
    for (int start = 0; start < V; ++start)
    {
        if (component_id[start] != -1)
            continue;

        // DFS is the DFS implementation from Assignment 1.
        dfs_result dfs_result_data = dfs(graph, start);

        for (int i = 0; i < dfs_result_data.traversal_size; ++i)
        {
            const int vertex = dfs_result_data.traversal[i];
            component_id[vertex] = component_count;
        }

        free_dfs_result(&dfs_result_data);
        ++component_count;
    }

    return component_id;
}
