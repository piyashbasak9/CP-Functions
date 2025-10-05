#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define endl "\n"

const int N = 2e5+5;

vector<int> g[N];
int tin[N], tout[N], flat[2*N];
int timer = 0;

void dfs(int u, int p) {
    tin[u] = ++timer;
    flat[timer] = u;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
    tout[u] = ++timer;
    flat[timer] = u;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    dfs(1,-1);
    
    cout << "Euler Tour: ";
    for(int i=1;i<=timer;i++) cout << flat[i] << " ";
    cout << endl;

    cout << "In-Time / Out-Time:" << endl;
    for(int i=1;i<=n;i++) cout << i << ": " << tin[i] << " " << tout[i] << endl;
}
