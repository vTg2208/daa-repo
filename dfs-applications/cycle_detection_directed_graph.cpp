#include <iostream>
#include <vector>
using namespace std;

bool isCyclicUtil(int v, vector<bool>& visited, vector<bool>& recStack, const vector<vector<int>>& adj) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor] && isCyclicUtil(neighbor, visited, recStack, adj))
                return true;
            else if (recStack[neighbor])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool hasCycleDirectedGraph(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for (int i = 0; i < V; ++i)
        if (!visited[i] && isCyclicUtil(i, visited, recStack, adj))
            return true;
    
    return false;
}

// Usage example:
int main() {
    int V = 4;
    vector<vector<int>> adj(V);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(3);
    
    cout << (hasCycleDirectedGraph(V, adj) ? "Cycle exists" : "No cycle");
}