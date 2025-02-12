#include <bits/stdc++.h>
using namespace std;

vector<int> getTopologicalOrderBFS(int numVertices, vector<vector<int>> &adjacencyList) {
    vector<int> indegree(numVertices, 0);
    for (int i = 0; i < numVertices; i++) {
        for (int neighbor : adjacencyList[i]) {
            indegree[neighbor]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < numVertices; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }
    
    vector<int> topologicalOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topologicalOrder.push_back(node);
        
        for (int neighbor : adjacencyList[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
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
    
    vector<int> topologicalOrder = getTopologicalOrderBFS(numVertices, adjacencyList);
    
    for (int node : topologicalOrder) {
        cout << node << " ";
    }
    
    return 0;
}
