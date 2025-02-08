#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;

int n;
vector<int> adj[N];
int parent[N], level[N];
int table[21][N];

// DFS to set parent and level of each node
void dfs(int ver, int l) {
    level[ver] = l;
    for (auto c : adj[ver]) {
        parent[c] = ver;
        dfs(c, l + 1);
    }
}

// Build sparse table for binary lifting
void build() {
    for (int i = 1; i <= n; i++) {
        table[0][i] = parent[i];
    }
    for (int lv = 1; lv < 20; lv++) {
        for (int j = 1; j <= n; j++) {
            int half = table[lv - 1][j];
            table[lv][j] = table[lv - 1][half];
        }
    }
}

// Find LCA using binary lifting
int query(int a, int b) {
    if (level[a] > level[b]) swap(a, b);

    int diff = level[b] - level[a];
    for (int i = 20; i >= 0; i--) {
        if (diff & (1 << i)) {
            b = table[i][b];
        }
    }
    if (a == b) return a;

    for (int i = 20; i >= 0; i--) {
        if (table[i][a] != table[i][b]) {
            a = table[i][a];
            b = table[i][b];
        }
    }
    return parent[a];
}

// Read input and process queries
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        adj[i].clear(); parent[i] = i; level[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        while (x--) {
            int u; cin >> u; adj[i].push_back(u);
        }
    }
    dfs(1, 1); build();
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b; cout << query(a, b) << endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1, tt = 1; cin >> t;
    while (t--) {
        cout << "Case " << tt++ << ":\n"; solve();
    }
}
