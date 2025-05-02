#include<bits/stdc++.h>
//#define int long long int
#define ll long long

using namespace std;
int ts=1;
// start journey

const int N = 5e5+1;
int ar[N];
vector<int>dv[N];
vector<int>x;

struct trie{
    vector<array<int, 2>>to;
    trie(){
        to.push_back({0, 0});
        to.push_back({0, 0});
    }
    int tot = 1;
    void add(int val){
        int u = 1;
        for(int i = 31; i >= 0; i--){
            int bit = (val >> i) & 1;
            if(to[u][bit] == 0){
                to.push_back({0, 0});
                to[u][bit] = ++tot;
            }
            u = to[u][bit];
        }
    }

    int find(int val){
        int u = 1, ans = 0;
        for(int i = 31; i >= 0; i--){
            int bit = (val >> i) & 1;
            int tar = bit ^ 1;
            if(to[u][tar] != 0){
                ans = ans | (1 << i);
                u = to[u][tar];
            }
            else{
                u = to[u][bit];
            }
        }
        return ans;
    }
}t[N];



void solve(){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        ar[x]++;
    }
    for(int i = 1; i < N; i++){
        for(int j = i; j < N; j += i){
            if(ar[j]){
                dv[j].push_back(i);
            }
            if(ar[j]){
                t[i].add(j);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i < N; i++){
        if(dv[i].size() == 0) continue;
        for(auto it : dv[i]){
            ans = max(ans, it + t[it].find(i));
        }
    }
    cout << ans << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t=1;
    //cin >> t;
    while(t--){
        solve();
    }
}














const int N = 2e5+5;
const int IDX = 31;

int trie[N * IDX][2], cnt[N * IDX], tot = 1, root;

void init() {
  cnt[tot] = 0;
  root = tot;
}

void add(int x) {
  int u = 1;
  cnt[u]++;
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = x >> idx & 1;
    if (!trie[u][f])  trie[u][f] = ++tot;
    u = trie[u][f];
    cnt[u]++;
  }
}

void rem(int x) {
  int u = 1;
  assert(cnt[u] > 0);
  cnt[u]--;
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = x >> idx & 1;
    u = trie[u][f];
    assert(cnt[u] > 0);
    cnt[u]--;
  }
}

int maxXor(int x) {
  int u = 1, ret = 0;
  assert(cnt[u] > 0);
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = x >> idx & 1;
    if (trie[u][!f])  ret |= 1 << idx, u = trie[u][!f];
    else  u = trie[u][f];
  }
  return ret;
}

