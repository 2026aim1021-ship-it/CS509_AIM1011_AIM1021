#include "maxflowMincut.hpp"

#include <fstream>
#include <queue>
#include <climits>
#include <cstdlib>
#include <algorithm>

using namespace std;

namespace {

// Check whether a string is a (possibly negative) whole number.
bool is_number(const string &s)
{
    if (s.empty())
        return false;

    char *end;
    strtoll(s.c_str(), &end, 10);

    return end != s.c_str() && *end == '\0';
}

// Read the whole file and split it into whitespace-separated words.
vector<string> tokenize(const string &path, bool &opened)
{
    vector<string> tokens;
    ifstream file(path);

    opened = file.is_open();
    if (!opened)
        return tokens;

    string word;
    while (file >> word)
        tokens.push_back(word);

    return tokens;
}

// ---------------- DINIC GRAPH ----------------
struct DinicGraph
{
    int V;
    vector<int> to;
    vector<long long> cap;
    vector<vector<int>> adj;
    vector<int> level;
    vector<int> current;

    void init(int n)
    {
        V = n;
        adj.resize(n);
        level.resize(n);
        current.resize(n);
    }

    // Add forward edge and reverse edge (as a paired {even, odd} index,
    // so id ^ 1 always gives the matching reverse edge).
    void add_edge(int u, int v, long long capacity)
    {
        adj[u].push_back((int)to.size());
        to.push_back(v);
        cap.push_back(capacity);

        adj[v].push_back((int)to.size());
        to.push_back(u);
        cap.push_back(0);
    }

    // Create level graph using BFS.
    bool bfs(int source, int sink)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int id : adj[u])
            {
                int v = to[id];
                if (cap[id] > 0 && level[v] == -1)
                {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[sink] != -1;
    }

    // Send flow using DFS along the level graph, with a current-arc
    // pointer per vertex so exhausted edges are never re-scanned within
    // the same BFS phase.
    long long dfs(int u, int sink, long long flow)
    {
        if (u == sink)
            return flow;

        for (int &i = current[u]; i < (int)adj[u].size(); i++)
        {
            int id = adj[u][i];
            int v = to[id];

            if (cap[id] <= 0)
                continue;
            if (level[v] != level[u] + 1)
                continue;

            long long pushed = dfs(v, sink, min(flow, cap[id]));

            if (pushed > 0)
            {
                cap[id] -= pushed;
                cap[id ^ 1] += pushed;
                return pushed;
            }
        }

        return 0;
    }

    // Dinic's maximum flow: alternate BFS level-graph construction with
    // repeated blocking-flow DFS until the sink is unreachable.
    long long max_flow(int source, int sink)
    {
        long long flow = 0;

        while (bfs(source, sink))
        {
            fill(current.begin(), current.end(), 0);

            while (true)
            {
                long long pushed = dfs(source, sink, LLONG_MAX);
                if (pushed == 0)
                    break;
                flow += pushed;
            }
        }

        return flow;
    }
};

} // namespace

// ---------------- READ INPUT ----------------
mf_input read_maxflow_input(const string &path)
{
    mf_input input;
    input.valid = false;
    input.source = -1;
    input.sink = -1;

    // Safe defaults so a struct returned on an early-error path never
    // holds dangling/garbage pointers -- callers only touch input.graph
    // after checking input.valid, but this keeps free_adjacency_list()
    // safe even if that check is ever skipped.
    input.graph.V = 0;
    input.graph.E = 0;
    input.graph.source = 0;
    input.graph.weighted = 1;
    input.graph.adj = nullptr;
    input.graph.degree = nullptr;

    bool opened;
    vector<string> tokens = tokenize(path, opened);

    if (!opened)
    {
        input.error = "Cannot open file " + path;
        return input;
    }

    size_t pos = 0;

    auto get_number = [&](long long &x) -> bool
    {
        if (pos >= tokens.size() || !is_number(tokens[pos]))
            return false;
        x = stoll(tokens[pos]);
        pos++;
        return true;
    };

    // Read V and E
    long long V, E;
    if (!get_number(V) || !get_number(E) || V <= 0)
    {
        input.error = "Invalid V E";
        return input;
    }

    input.graph.V = (int)V;
    input.graph.E = (int)E;
    input.graph.degree = (int *)calloc((size_t)V, sizeof(int));
    input.graph.adj = (Edge **)malloc((size_t)V * sizeof(Edge *));

    // Read adjacency list
    for (long long i = 0; i < V; i++)
    {
        long long u, degree;
        if (!get_number(u) || !get_number(degree))
        {
            input.error = "Invalid adjacency line";
            return input;
        }

        // u is the vertex id this line describes -- it must be a valid
        // index before it's used to write into degree[]/adj[] below.
        // Without this check, a malformed or out-of-range u causes an
        // out-of-bounds write (heap corruption), not a clean rejection.
        if (u < 0 || u >= V || degree < 0)
        {
            input.error = "Invalid vertex or degree on adjacency line";
            return input;
        }

        input.graph.degree[u] = (int)degree;
        input.graph.adj[u] = (Edge *)malloc((size_t)degree * sizeof(Edge));

        for (long long j = 0; j < degree; j++)
        {
            long long v, capacity;
            if (!get_number(v) || !get_number(capacity))
            {
                input.error = "Invalid edge";
                return input;
            }

            if (v < 0 || v >= V || capacity < 0)
            {
                input.error = "Invalid vertex or capacity";
                return input;
            }

            input.graph.adj[u][j].to = (int)v;
            input.graph.adj[u][j].weight = (double)capacity;
        }
    }

    // Read SOURCE
    if (pos >= tokens.size() || tokens[pos] != "SOURCE")
    {
        input.error = "Missing SOURCE";
        return input;
    }
    pos++;

    long long source;
    if (!get_number(source))
    {
        input.error = "Invalid SOURCE";
        return input;
    }

    // Read SINK
    if (pos >= tokens.size() || tokens[pos] != "SINK")
    {
        input.error = "Missing SINK";
        return input;
    }
    pos++;

    long long sink;
    if (!get_number(sink))
    {
        input.error = "Invalid SINK";
        return input;
    }

    if (source < 0 || source >= V ||
        sink < 0 || sink >= V ||
        source == sink)
    {
        input.error = "Invalid source or sink";
        return input;
    }

    input.source = (int)source;
    input.sink = (int)sink;
    input.graph.source = (int)source;
    input.valid = true;

    return input;
}

// ---------------- MAX FLOW + MIN CUT ----------------
mf_result maxflow_mincut(
    const csr_graph *graph,
    int source,
    int sink)
{
    mf_result result;
    result.max_flow = 0;
    result.min_cut_capacity = 0;

    // 1. Build Dinic graph from CSR. This construction is part of the
    //    timed algorithm section (Section 8): the residual network isn't
    //    built until the algorithm call starts.
    DinicGraph dg;
    dg.init(graph->V);

    for (int u = 0; u < graph->V; u++)
    {
        for (int i = graph->row_ptr[u]; i < graph->row_ptr[u + 1]; i++)
        {
            int v = graph->col_idx[i];
            long long capacity = (long long)graph->values[i];
            dg.add_edge(u, v, capacity);
        }
    }

    // 2. Find maximum flow
    result.max_flow = dg.max_flow(source, sink);

    // 3. Find vertices reachable from source in the final residual graph
    vector<bool> reachable(graph->V, false);
    queue<int> q;
    q.push(source);
    reachable[source] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int id : dg.adj[u])
        {
            int v = dg.to[id];
            if (dg.cap[id] > 0 && !reachable[v])
            {
                reachable[v] = true;
                q.push(v);
            }
        }
    }

    // 4. Divide vertices into two sides
    for (int v = 0; v < graph->V; v++)
    {
        if (reachable[v])
            result.source_side.push_back(v);
        else
            result.sink_side.push_back(v);
    }

    // 5. Find edges crossing the cut (source side -> sink side). Their
    //    total capacity equals the minimum cut, which must equal the
    //    maximum flow value.
    for (int u = 0; u < graph->V; u++)
    {
        if (!reachable[u])
            continue;

        for (int i = graph->row_ptr[u]; i < graph->row_ptr[u + 1]; i++)
        {
            int v = graph->col_idx[i];

            if (!reachable[v])
            {
                long long capacity = (long long)graph->values[i];
                result.cut_edges.push_back({u, v, capacity});
                result.min_cut_capacity += capacity;
            }
        }
    }

    return result;
}
