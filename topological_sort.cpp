#include <bits/stdc++.h>
using namespace std;

void topologicalDFS(int node, vector<bool>& visited, stack<int>& topoStack, vector<vector<int>>& adjacencyList) {
    visited[node] = true;
    
    for (int neighbor : adjacencyList[node]) {
        if (!visited[neighbor])
            topologicalDFS(neighbor, visited, topoStack, adjacencyList);
    }
    
    topoStack.push(node);
}

vector<int> getTopologicalOrder(int numVertices, vector<vector<int>>& adjacencyList) {
    vector<bool> visited(numVertices, false);
    stack<int> topoStack;

    for (int vertex = 0; vertex < numVertices; vertex++) {
        if (!visited[vertex]) {
            topologicalDFS(vertex, visited, topoStack, adjacencyList);
        }
    }
    
    vector<int> topologicalOrder;
    while (!topoStack.empty()) {
        topologicalOrder.push_back(topoStack.top());
        topoStack.pop();
    }
    
    return topologicalOrder;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<int>> adjacencyList(numVertices); 

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        adjacencyList[u].push_back(v);
    }

    vector<int> topologicalOrder = getTopologicalOrder(numVertices, adjacencyList);

    for (int node : topologicalOrder) {
        cout << node << " ";
    }

    return 0;
}
