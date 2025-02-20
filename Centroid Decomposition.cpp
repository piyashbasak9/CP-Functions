#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 2e5+5;
 
int n, k;
vector<int> adj[N];
int sz[N], cen[N];
ll ans = 0;
 
void dfs_sz(int u, int p) {
  sz[u] = 1;
  for (auto v: adj[u]) {
    if (v != p and !cen[v]) {
      dfs_sz(v, u);
      sz[u] += sz[v];
    }
  }
}
 
int get_cen(int u, int p, int s) {
  for (auto v: adj[u]) {
    if (v != p and !cen[v] and 2 * sz[v] > s)  return get_cen(v, u, s);
  }
  return u;
}
 
int t, tin[N], tout[N], nodes[N], dep[N];
 
void dfs(int u, int p) {
  nodes[t] = u;
  tin[u] = t++;
  for (auto v: adj[u]) {
    if (v != p and !cen[v]) {
      dep[v] = dep[u] + 1;
      dfs(v, u);
    }
  }
  tout[u] = t - 1;
}
 
void go(int u) {
  dfs_sz(u, u);
  int c = get_cen(u, u, sz[u]);
  cen[c] = 1;
 
  t = 0;
  dep[c] = 0;
  dfs(c, c);
  int cnt[t]{1};
  for (auto v: adj[c]) {
    if (!cen[v]) {
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = nodes[i];
        int req = k - dep[w];
        if (req >= 0 and req < t) {
          ans += cnt[req];
        }
      }
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = nodes[i];
        cnt[dep[w]]++;
      }
    }
  }
 
  for (auto v: adj[c]) {
    if (!cen[v]) {
      go(v);
    }
  }
}
 
void solve () {
  cin >> n >> k;
  for (int e = 0; e < n - 1; ++e) {
    int u, v;  cin >> u >> v;  u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  go(0);
  cout << ans << "\n";
}
 
int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  solve();
  return 0;
}
