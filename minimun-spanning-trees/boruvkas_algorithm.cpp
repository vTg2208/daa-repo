#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

vector<Edge> boruvkaMST(int V, const vector<Edge>& edges) {
    vector<int> parent(V);
    iota(parent.begin(), parent.end(), 0);
    vector<Edge> mst;
    int numComponents = V;

    function<int(int)> find = [&](int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    };

    while (numComponents > 1) {
        vector<int> cheapest(V, -1);

        for (int i = 0; i < edges.size(); ++i) {
            const Edge &e = edges[i];
            int setU = find(e.u);
            int setV = find(e.v);
            if (setU == setV) continue;

            if (cheapest[setU] == -1 || edges[cheapest[setU]].w > e.w)
                cheapest[setU] = i;
            if (cheapest[setV] == -1 || edges[cheapest[setV]].w > e.w)
                cheapest[setV] = i;
        }

        bool edgeAdded = false;
        for (int i = 0; i < V; ++i) {
            if (cheapest[i] != -1) {
                const Edge &e = edges[cheapest[i]];
                int setU = find(e.u);
                int setV = find(e.v);
                if (setU != setV) {
                    mst.push_back(e);
                    parent[setV] = setU;
                    numComponents--;
                    edgeAdded = true;
                }
            }
        }

        if (!edgeAdded) break;
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
    
    vector<Edge> mst = boruvkaMST(V, edges);
    for (auto &e : mst)
        cout << e.u << " - " << e.v << endl;
}