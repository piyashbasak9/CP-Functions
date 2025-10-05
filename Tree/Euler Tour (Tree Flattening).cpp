#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define endl "\n"

const int N = 2e5+5;

vector<int> g[N];
int start_time[N], end_time[N], flat[2*N], val[N];
int timer = 0;

void dfs(int u, int p){
    start_time[u] = timer;
    flat[timer++] = val[u];
    for(auto v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }
    end_time[u] = timer;
    flat[timer++] = val[u];
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    for(int i=1;i<=n;i++) cin >> val[i];
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1,-1);
    
    cout << "Flat Euler Tour:" << endl;
    for(int i=0;i<timer;i++) cout << flat[i] << " ";
    cout << endl;

    cout << "Start / End Times:" << endl;
    for(int i=1;i<=n;i++)
        cout << i << ": " << start_time[i] << " " << end_time[i] << endl;
}
