#include "csr_weighted.h"

csr_graph buildCSR(int V, const vector<vector<int>> &adj){
    csr_graph g;
    g.V = V;
    g.row_ptr.assign(V+1, 0);

    for(int u = 0; u < V; u++){
        g.row_ptr[u+1] = g.row_ptr[u] + (int)adj[u].size();
    }

    int entries = g.row_ptr[V];
    g.E = entries / 2; // each undirected edge appears twice

    g.col_idx.resize(entries);

    int pos = 0;
    for(int u = 0; u < V; u++){
        for(int v : adj[u]){
            g.col_idx[pos] = v;
            pos++;
        }
    }

    return g;
}
