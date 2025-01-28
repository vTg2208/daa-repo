#include <bits/stdc++.h>
using namespace std;

void biconnectedDFS(int u, int parent, vector<int>& disc, vector<int>& low, 
                    vector<vector<int>>& adj, stack<pair<int,int>>& st, 
                    vector<vector<pair<int,int>>>& components) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    
    for(int v : adj[u]) {
        if(disc[v] == -1) {
            st.push({u, v});
            biconnectedDFS(v, u, disc, low, adj, st, components);
            
            low[u] = min(low[u], low[v]);
            
            if(low[v] >= disc[u]) {
                vector<pair<int,int>> component;
                while(!st.empty()) {
                    pair<int,int> edge = st.top();
                    st.pop();
                    component.push_back(edge);
                    if(edge.first == u && edge.second == v)
                        break;
                }
                components.push_back(component);
            }
        }
        else if(v != parent && disc[v] < disc[u]) {
            low[u] = min(low[u], disc[v]);
            st.push({u, v});
        }
    }
}

vector<vector<pair<int,int>>> findBiconnectedComponents(vector<vector<int>>& adj, int V) {
    vector<int> disc(V, -1), low(V, -1);
    stack<pair<int,int>> st;
    vector<vector<pair<int,int>>> components;
    
    for(int i = 0; i < V; i++) {
        if(disc[i] == -1) {
            biconnectedDFS(i, -1, disc, low, adj, st, components);
            
            vector<pair<int,int>> component;
            while(!st.empty()) {
                component.push_back(st.top());
                st.pop();
            }
            if(!component.empty())
                components.push_back(component);
        }
    }
    return components;
}

void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() {
    int V = 5; 
    vector<vector<int>> adj(V);
    
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 1, 3);
    addEdge(adj, 3, 4);
    
    vector<vector<pair<int,int>>> components = findBiconnectedComponents(adj, V);
    
    cout << "Biconnected Components:\n";
    for(int i = 0; i < components.size(); i++) {
        cout << "Component " << i+1 << ":\n";
        for(auto edge : components[i]) {
            cout << edge.first << " -- " << edge.second << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}