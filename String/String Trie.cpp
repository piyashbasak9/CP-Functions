#include <bits/stdc++.h>
using namespace std;

#define int long long int

const int N = 2e6 + 5;
int trie[N][26], pc[N], tot = 0;

void add(string &s) {
    int u = 0;
    for (auto c : s) {
        int f = c - 'a';
        if (!trie[u][f]) trie[u][f] = ++tot;
        u = trie[u][f];
        pc[u]++;
    }
}

int query(string &s) {
    int u = 0;
    for (auto c : s) {
        int f = c - 'a';
        if (!trie[u][f]) return 0;
        u = trie[u][f];
    }
    return pc[u];
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(s);
    }
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        cout << query(s) << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
