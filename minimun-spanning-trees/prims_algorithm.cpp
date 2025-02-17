#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (weight, node)

vector<vector<pii>> adj;

vector<pair<int, int>> primMST(int V) {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto &edge : adj[u]) {
            int v = edge.second;
            int w = edge.first;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    vector<pair<int, int>> mst;
    for (int i = 1; i < V; ++i)
        if (parent[i] != -1)
            mst.push_back({parent[i], i});
    
    return mst;
}

// Usage example:
int main() {
    int V = 4;
    adj.resize(V);
    adj[0].push_back({10, 1});
    adj[1].push_back({10, 0});
    adj[1].push_back({3, 2});
    adj[2].push_back({3, 1});
    adj[2].push_back({4, 3});
    adj[3].push_back({4, 2});
    adj[0].push_back({5, 3});
    adj[3].push_back({5, 0});
    
    vector<pair<int, int>> mst = primMST(V);
    for (auto &e : mst)
        cout << e.first << " - " << e.second << endl;
}