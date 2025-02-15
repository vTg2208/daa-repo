#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int u, vector<bool>& visited, stack<int>& stk, const vector<vector<int>>& adj) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, visited, stk, adj);
        }
    }
    stk.push(u);
}

void dfs2(int u, vector<bool>& visited, vector<int>& scc, const vector<vector<int>>& reversed_adj) {
    visited[u] = true;
    scc.push_back(u);
    for (int v : reversed_adj[u]) {
        if (!visited[v]) {
            dfs2(v, visited, scc, reversed_adj);
        }
    }
}

vector<vector<int>> kosaraju(int n, const vector<vector<int>>& adj) {
    stack<int> stk;
    vector<bool> visited(n, false);

    // First pass to fill the stack with finishing times
    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            dfs1(u, visited, stk, adj);
        }
    }

    // Create reversed graph
    vector<vector<int>> reversed_adj(n);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            reversed_adj[v].push_back(u);
        }
    }

    // Second pass to find SCCs
    vector<bool> visited2(n, false);
    vector<vector<int>> sccs;
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        if (!visited2[u]) {
            vector<int> scc;
            dfs2(u, visited2, scc, reversed_adj);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<vector<int>> sccs = kosaraju(n, adj);

    cout << "Strongly Connected Components:" << endl;
    for (const auto& scc : sccs) {
        for (int node : scc) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}