// Generates a sparse directed capacitated graph for Maxflow-Mincut testing
// (Section 4.2/4.3 required sizes: 10, 100, 1000, 10000, 50000, optional
// 100000).
//
// Guarantees a source(0) -> sink(V-1) path and keeps every edge going from
// a lower-numbered vertex to a higher-numbered one (a DAG). That is a
// simple, sufficient way to satisfy "the graph must contain a valid
// source, sink, and at least one source-to-sink path" (Section 3) without
// needing cycle detection.
//
// Usage: generate_maxflow_graph <V> <E> <output_file> [seed]
//   V      number of vertices (>= 2)
//   E      target number of directed edges (>= V-1, recommended ~2V-4V to
//          stay sparse, per the required-sizes note); the guaranteed
//          chain edges are always included, and the actual edge count
//          actually written is printed to stderr and used in the file
//          header
//   seed   optional RNG seed (default 42, for reproducibility)
//
// Build:   g++ -std=c++17 -O2 -o generate_maxflow_graph generate_maxflow_graph.cpp
// Example: ./generate_maxflow_graph 50000 150000 ../tests/maxflow_50000.txt

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <V> <E> <output_file> [seed]\n";
        return 1;
    }

    long long V = atoll(argv[1]);
    long long E = atoll(argv[2]);
    string outfile = argv[3];
    unsigned seed = (argc >= 5) ? (unsigned)atoll(argv[4]) : 42u;

    if (V < 2)
    {
        cerr << "V must be >= 2.\n";
        return 1;
    }

    long long min_edges = V - 1;
    if (E < min_edges)
        E = min_edges;

    mt19937_64 rng(seed);
    uniform_int_distribution<int> cap_dist(1, 1000);

    vector<vector<pair<int, int>>> edges(V); // edges[u] = (v, capacity)
    set<pair<long long, long long>> present;

    auto add_edge = [&](long long u, long long v) -> bool
    {
        if (u == v || present.count({u, v}))
            return false;

        present.insert({u, v});
        edges[u].push_back({(int)v, cap_dist(rng)});
        return true;
    };

    // Guaranteed chain: 0 -> 1 -> 2 -> ... -> V-1, so a source(0)-sink(V-1)
    // path always exists regardless of what else gets added below.
    for (long long i = 0; i + 1 < V; ++i)
        add_edge(i, i + 1);

    long long current = V - 1;

    // Extra random forward edges (lower id -> higher id, within a local
    // window) until the requested edge count is reached, or the attempt
    // budget runs out for very dense requests.
    uniform_int_distribution<long long> span_dist(2, 8);
    long long attempts = 0;
    long long max_attempts = E * 20 + 1000;

    while (current < E && attempts < max_attempts)
    {
        ++attempts;

        uniform_int_distribution<long long> u_dist(0, V - 2);
        long long u = u_dist(rng);
        long long span = span_dist(rng);
        long long v = min(V - 1, u + span);

        if (add_edge(u, v))
            ++current;
    }

    ofstream out(outfile);
    if (!out)
    {
        cerr << "Cannot open output file " << outfile << "\n";
        return 1;
    }

    out << V << " " << current << "\n";

    for (long long u = 0; u < V; ++u)
    {
        out << u << " " << edges[u].size();
        for (auto &e : edges[u])
            out << " " << e.first << " " << e.second;
        out << "\n";
    }

    out << "SOURCE 0\n";
    out << "SINK " << (V - 1) << "\n";

    cerr << "Wrote " << outfile << " with V=" << V << " E=" << current << "\n";

    return 0;
}
