const int N = 2e6+5;
const int A = 26;

int trie[N * A][2], pc[N], wc[N], tot = 1, root;

void init() {
  pc[tot] = wc[tot] = 0;
  root = tot;
}

void add(string &s) {
  int u = root;
  pc[u]++;
  for (auto c: s) {
    int f = c - 'a';
    if (!trie[u][f])  trie[u][f] = ++tot;
    u = trie[u][f];
    pc[u]++;
  }
  wc[u]++;
}

int prefCount(string &s) {
  int u = root, ret = 0;
  for (auto c: s) {
    int f = c - 'a';
    if (!trie[u][f])  return 0;
    u = trie[u][f];
  }
  return pc[u];
}




void solve(){
    ll n , m ;
    cin >> n >> m;
    for(ll i = 0; i < n; i++){
        string ch;
        cin >> ch;
        add(ch);
    }
    for(ll i = 0; i < m; i++){
        string ch;
        cin >> ch;
        cout << prefCount(ch) << endl;
    }

}
