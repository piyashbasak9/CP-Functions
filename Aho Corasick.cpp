const ll N = 1000010, A = 26;

ll to[N][A],tot = 0, dp[N], node[N], slink[N];
vector<ll>adj;

void add(string &s, ll i){
    ll u = 0;
    for(auto c : s){
        c -= 'a';
        if(to[u][c] == 0){
            to[u][c] = ++tot;
        }
        u = to[u][c];
    }
    node[i] = u;
}
void build()
{
    queue<ll>q;
    q.push(0);
    while(!q.empty()){
        ll p = q.front();
        q.pop();
        adj.push_back(p);
        for(ll c = 0; c < A; c++){
            ll u = to[p][c];
            if(u == 0)continue;
            q.push(u);
            if(p == 0)continue;
            ll v = slink[p];
            while(v && !to[v][c]){
                v = slink[v];
            }
            if(to[v][c] != 0){
                slink[u] = to[v][c];
            }
        }
    }
}

void solve(){
    for(ll i = 0; i < N; i++){
        dp[i] = 1e18;
    }
    ll n;
    string str;
    cin >> str;
    cin >> n;
    ll len[n];
    for(ll i = 0; i <n ; i++){
        string ch;
        cin >> ch;
        len[i] = ch.length() -1;
        add(ch,i);
    }
    build();
    ll u = 0;
    for(ll i = 0; i < str.length(); i++){
        int c = str[i] - 'a';
        while(u && !to[u][c]){
            u = slink[u];
        }
        u = to[u][c];
        dp[u] = min(dp[u], i+1);
    }
    reverse(adj.begin(),adj.end());
    for(auto p : adj){
        dp[slink[p]] = min (dp[slink[p]] , dp[p]);
    }
    for(ll i = 0; i < n; i++){
        if(dp[node[i]] > str.length()){
            cout << -1 << endl;
        }
        else{
            cout << dp[node[i]]-len[i] << endl; 
        }
    }
}
