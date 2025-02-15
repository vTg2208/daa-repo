/*
A graph is said to be Biconnected if: 

It is connected, i.e. it is possible to reach every vertex from every other vertex, by a simple path. 
Even after removing any vertex the graph remains connected.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> adj; // Graph adjacency list
vector<int> disc, low, parent;
vector<bool> isArticulation;
stack<pair<int, int>> edgeStack;
vector<vector<pair<int, int>>> components;
int time;

void dfs(int u) {
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : adj[u]) {
        if (disc[v] == -1) { // Tree edge
            children++;
            parent[v] = u;
            edgeStack.push({u, v});
            dfs(v);
            low[u] = min(low[u], low[v]);

            // Check for articulation point and biconnected component
            if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                isArticulation[u] = true;
                // Extract component
                vector<pair<int, int>> component;
                while (edgeStack.top() != make_pair(u, v)) {
                    component.push_back(edgeStack.top());
                    edgeStack.pop();
                }
                component.push_back(edgeStack.top());
                edgeStack.pop();
                components.push_back(component);
            }
        } else if (v != parent[u] && disc[v] < disc[u]) { // Back edge
            low[u] = min(low[u], disc[v]);
            edgeStack.push({u, v});
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    disc.assign(n, -1);
    low.assign(n, -1);
    parent.assign(n, -1);
    isArticulation.assign(n, false);
    time = 0;

    // Read edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            dfs(i);
            // Collect remaining edges as last component
            if (!edgeStack.empty()) {
                vector<pair<int, int>> component;
                while (!edgeStack.empty()) {
                    component.push_back(edgeStack.top());
                    edgeStack.pop();
                }
                components.push_back(component);
            }
        }
    }

    // Output articulation points
    cout << "Articulation Points: ";
    for (int i = 0; i < n; ++i) {
        if (isArticulation[i]) {
            cout << i << " ";
        }
    }
    cout << "\n\n";

    // Output biconnected components
    cout << "Biconnected Components:\n";
    for (int i = 0; i < components.size(); ++i) {
        cout << "Component " << i+1 << ": ";
        for (auto& edge : components[i]) {
            cout << "(" << edge.first << "-" << edge.second << ") ";
        }
        cout << "\n";
    }

    return 0;
}