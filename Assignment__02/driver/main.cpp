#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "../src/csr_weighted.h"
#include "../src/triangleCounting.h"

using namespace std;
using clk = chrono::high_resolution_clock;

static double elapsed_ms(clk::time_point start, clk::time_point end){
    return chrono::duration<double, milli>(end - start).count();
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Usage: " << argv[0] << " <inputfile>\n";
        return 1;
    }

    const char *path = argv[1];
    ifstream fin(path);

    if(!fin.is_open()){
        cout << "Failed to load graph from " << path << "\n";
        return 1;
    }

    int V, E;
    fin >> V >> E;

    if(!fin || V <= 0){
        cout << "Failed to load graph from " << path << "\n";
        return 1;
    }

    vector<vector<int>> adj(V);
    for(int i = 0; i < V; i++){
        int u, degree;
        fin >> u >> degree;

        if(!fin){
            cout << "Failed to load graph from " << path << "\n";
            return 1;
        }

        adj[u].resize(degree);
        for(int j = 0; j < degree; j++)
            fin >> adj[u][j];
    }

    csr_graph graph = buildCSR(V, adj); // preprocessing, not timed

    // Listing individual triangles is only required for the two smallest
    // graph sizes (10 and 100 vertices) per the spec.
    bool collect = (V <= 100);

    auto start = clk::now();
    triangleCount result = triangle_counting(&graph, collect);
    auto end = clk::now();

    cout << "Algorithm: Triangle Counting\n";
    cout << "Total triangles: " << result.total << "\n";

    if(collect){
        cout << "Triangles found:\n";
        for(auto &t : result.triangles)
            cout << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
    }

    cout << "Execution time: " << elapsed_ms(start, end) << " ms\n";

    return 0;
}
