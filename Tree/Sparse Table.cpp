ll merge(ll a, ll b) {
    return min(a, b);
}

void build_sparse_table(const vector<ll>& arr) {
    N = arr.size();
    if (N == 0) return;

    K = floor(log2(N));
    st.assign(N, vector<ll>(K + 1));

    for (int i = 0; i < N; ++i) {
        st[i][0] = arr[i];
    }

    for (int j = 1; j <= K; ++j) {
        for (int i = 0; i + (1 << j) <= N; ++i) {
            st[i][j] = merge(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    log_table.assign(N + 1, 0);
    for (int i = 2; i <= N; ++i) {
        log_table[i] = log_table[i / 2] + 1;
    }
}

ll query_rmq(int L, int R) {
    if (L < 0 || R >= N || L > R) {
        return 2e18;
    }

    int len = R - L + 1;
    int p = log_table[len];
    
    ll val1 = st[L][p];
    ll val2 = st[R - (1 << p) + 1][p];
    
    return merge(val1, val2);
}
