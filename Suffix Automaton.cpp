// problem link : https://cses.fi/alon/task/2103
const int N = 2e6+10; // 2x size taken
int len[N], lnk[N]{-1}, cnt[N];
int last, sz = 1;
unordered_map<char, int> to[N]; // because of use unordered map, always check "to[u].count(c) != 0" before access


void init() {
  while (sz) {
    sz--;
    to[sz].clear();
  }
  last = 0, sz = 1;
}
void add(char c) {
    int cur = sz++;
    cnt[cur] = 1;
    len[cur] = len[last] + 1;
    int u = last;
    while (u != -1 and !to[u].count(c)) {
      to[u][c] = cur;
      u = lnk[u];
    }
    if (u == -1) {
      lnk[cur] = 0;
    }
    else {
      int v = to[u][c];
      if (len[v] == len[u] + 1) {
        lnk[cur] = v;
      }
      else {
        int w = sz++;
        len[w] = len[u] + 1, lnk[w] = lnk[v], to[w] = to[v];
        while (u != -1 and to[u][c] == v) {
          to[u][c] = w;
          u = lnk[u];
        }
        lnk[cur] = lnk[v] = w;
      }
    }
    last = cur;
}

void build() // this function is for finding the count of a subarray
{
    vector<int>deg(sz+10);
    for(int i = 1; i < sz; i++){
        deg[lnk[i]]++;
    }
    queue<int>q;
    for(int i = 1; i < sz; i++){
        if(deg[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int p = lnk[u];
        cnt[p] += cnt[u];
        deg[p]--;
        if(p && deg[p] == 0){
            q.push(p);
        }
    }
}

void solve(){
    string ch; cin >> ch;
    for(auto c : ch){
        add(c);
    }
    build();
    int u = 0;
    string str; cin >> str;
    for(auto c : str){
        if(to[u].count(c) == 0){
            cout << 0 << endl;
            return;
        }
        u = to[u][c];
    }

    cout << cnt[u] << endl;
}


int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t=1;
    //cin >> t;
    while(t--){
        init();
        solve();
    }
}
