#include "triangleCounting.hpp"

#include <algorithm>
#include <set>

using namespace std;

static bool has_edge(const csr_graph *graph,
                     int owner,
                     int other)
{
    int begin = graph->row_ptr[owner];
    int end   = graph->row_ptr[owner + 1];

    return binary_search(
        graph->col_idx + begin,
        graph->col_idx + end,
        other
    );
}


triangleCount triangle_counting(csr_graph *graph,
                                bool collect_triangles)
{
    triangleCount result;
    result.total = 0;

    const int V = graph->V;

    for (int u = 0; u < V; ++u)
    {
        sort(
            graph->col_idx + graph->row_ptr[u],
            graph->col_idx + graph->row_ptr[u + 1]
        );
    }

    long long count = 0;

    set<array<int, 3>> triangles;

    for (int u = 0; u < V; ++u)
    {
        int begin = graph->row_ptr[u];
        int end   = graph->row_ptr[u + 1];

        for (int i = begin; i < end; ++i)
        {
            int v = graph->col_idx[i];

            for (int j = i + 1; j < end; ++j)
            {
                int w = graph->col_idx[j];

                if (has_edge(graph, v, w))
                {
                    count++;

                    if (collect_triangles)
                    {
                        array<int, 3> triangle = {
                            u, v, w
                        };

                        sort(
                            triangle.begin(),
                            triangle.end()
                        );

                        triangles.insert(triangle);
                    }
                }
            }
        }
    }

    result.total = count / 3;

    if (collect_triangles)
    {
        result.triangles.assign(
            triangles.begin(),
            triangles.end()
        );
    }

    return result;
}