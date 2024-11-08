#include <bits/stdc++.h>
using namespace std;

int V, E, timeCount;
vector<vector<int>> adj;
vector<int> disc, low;
vector<bool> visited;
set<int> articulationPoints;
vector<pair<int, int>> bridges;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = timeCount++;
    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (parent == -1 && children > 1) articulationPoints.insert(u);
            if (parent != -1 && low[v] >= disc[u]) articulationPoints.insert(u);
            if (low[v] > disc[u]) bridges.push_back({u, v});
        } else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void findArticulationPointsAndBridges() {
    timeCount = 0;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) dfs(i, -1);
    }
    cout << "Articulation Points:\n";
    for (int point : articulationPoints) cout << point << " ";
    cout << "\nBridges:\n";
    for (auto bridge : bridges) cout << bridge.first << " - " << bridge.second << "\n";
}

int main() {
    cin >> V >> E;
    adj.resize(V);
    disc.assign(V, -1);
    low.assign(V, -1);
    visited.assign(V, false);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findArticulationPointsAndBridges();

    return 0;
}

