#include "triangleCounting.h"
#include <algorithm>
#include <set>

using namespace std;

// True if `other` appears in the (sorted) neighbour segment of `owner`.
static bool has_edge(const csr_graph *graph, int owner, int other){
    const int *begin = graph->col_idx.data() + graph->row_ptr[owner];
    const int *end   = graph->col_idx.data() + graph->row_ptr[owner+1];

    return binary_search(begin, end, other);
}

triangleCount triangle_counting(csr_graph *graph, bool collect_triangles){
    triangleCount res;
    int V = graph->V;

    // Sort each vertex's neighbour segment so has_edge() above can binary
    // search instead of scanning linearly.
    for(int u = 0; u < V; u++){
        sort(graph->col_idx.begin() + graph->row_ptr[u],
             graph->col_idx.begin() + graph->row_ptr[u+1]);
    }

    long long cnt = 0;
    set<array<int,3>> tr;

    for(int u = 0; u < V; u++){
        int begin = graph->row_ptr[u];
        int end   = graph->row_ptr[u+1];

        for(int i = begin; i < end; i++){
            int v = graph->col_idx[i];

            for(int j = i+1; j < end; j++){
                int w = graph->col_idx[j];

                if(has_edge(graph, v, w)){
                    cnt++;

                    if(collect_triangles){
                        array<int,3> tri = {u, v, w};
                        sort(tri.begin(), tri.end());
                        tr.insert(tri);
                    }
                }
            }
        }
    }

    res.total = cnt / 3;

    if(collect_triangles){
        res.triangles.assign(tr.begin(), tr.end());
    }

    return res;
}
