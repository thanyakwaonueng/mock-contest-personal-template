/**
 * Author: Tanya
 * Description: TODO
 */
//COPY FROM BENQ GITHUB I dont fucking know how this work 
//General graphs: O(V^2E);
//Bipartite matching(unit caps): O(E sqrt2(V))
struct Dinic {
    using F = long long; // flow type
    struct Edge { int to; F flow, cap; };
    int N;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level;
    vector<vector<int>::iterator> it;

    // Initialize Dinic for a graph with _N vertices (0-indexed or 1-indexed)
    void init(int _N) {
        N = _N;
        adj.assign(N, {});
        edges.clear();
        level.resize(N);
        it.resize(N);
    }

    // Add edge u -> v with capacity 'cap', and reverse edge v -> u with capacity 'rev_cap'
    void addEdge(int u, int v, F cap, F rev_cap = 0) {
        // forward edge
        adj[u].push_back((int)edges.size());
        edges.push_back({v, 0, cap});
        // reverse edge
        adj[v].push_back((int)edges.size());
        edges.push_back({u, 0, rev_cap});
    }

    // Build level graph via BFS
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        for (int i = 0; i < N; i++) it[i] = adj[i].begin();
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int idx : adj[u]) {
                const Edge &e = edges[idx];
                if (level[e.to] < 0 && e.flow < e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    // DFS to send flow
    F dfs(int u, int t, F pushed) {
        if (u == t || pushed == 0) return pushed;
        for (; it[u] != adj[u].end(); ++it[u]) {
            int idx = *it[u];
            Edge &e = edges[idx];
            if (level[e.to] != level[u] + 1 || e.flow == e.cap) continue;
            F tr = dfs(e.to, t, min(pushed, e.cap - e.flow));
            if (tr > 0) {
                e.flow += tr;
                edges[idx ^ 1].flow -= tr; // reverse edge
                return tr;
            }
        }
        return 0;
    }

    // Compute max flow from s to t
    F maxFlow(int s, int t) {
        F flow = 0;
        while (bfs(s, t)) {
            while (F pushed = dfs(s, t, numeric_limits<F>::max())) {
                flow += pushed;
            }
        }
        return flow;
    }

    // After maxFlow, vertices reachable from s in residual graph have level >= 0.
    // Edges from reachable u to unreachable v form a min-cut.
};
