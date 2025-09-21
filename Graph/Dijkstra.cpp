#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
#define pb push_back
#define full(x) x.begin(), x.end()
const ll inf = 1e12;
const int maxx = 100005; // Adjust based on constraints

vector<pi> graph[maxx];
priority_queue<pi, vector<pi>, greater<pi>> pq;
ll dis[maxx];
int parent[maxx];

void solve() {
    int n, m;
    cin >> n >> m;
    
    // Initialize graphs and arrays
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        dis[i] = inf;
        parent[i] = i;
    }
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].pb({b, w});
        graph[b].pb({a, w});
    }
    
    // Dijkstra's algorithm
    dis[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        int v = pq.top().second;
        ll d_v = pq.top().first;
        pq.pop();
        
        if (d_v != dis[v]) continue; // Skip outdated entries
        
        for (auto &edge : graph[v]) {
            int u = edge.first;
            int ucost = edge.second;
            
            if (dis[u] > dis[v] + ucost) {
                dis[u] = dis[v] + ucost;
                parent[u] = v;
                pq.push({dis[u], u});
            }
        }
    }
    
    // Reconstruct path
    if (dis[n] == inf) {
        cout << -1 << endl;
        return;
    }
    
    vector<int> path;
    int at = n;
    
    while (at != 1) {
        if (parent[at] == at) {
            cout << -1 << endl;
            return;
        }
        path.pb(at);
        at = parent[at];
    }
    path.pb(1);
    
    reverse(full(path));
    
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
