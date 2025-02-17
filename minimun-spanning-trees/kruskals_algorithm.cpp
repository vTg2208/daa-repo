#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

vector<Edge> kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    vector<int> parent(V);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    };

    vector<Edge> mst;
    for (Edge &e : edges) {
        int rootU = find(e.u);
        int rootV = find(e.v);
        if (rootU != rootV) {
            mst.push_back(e);
            parent[rootV] = rootU;
        }
    }
    return mst;
}

// Usage example:
int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {1, 2, 3}, 
        {2, 3, 4}, {0, 3, 5}
    };
    
    vector<Edge> mst = kruskalMST(V, edges);
    for (auto &e : mst)
        cout << e.u << " - " << e.v << endl;
}