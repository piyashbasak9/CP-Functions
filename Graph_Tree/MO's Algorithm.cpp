//Mo’s Algorithm is an offline query processing technique used to efficiently answer range queries in O((N + Q) * sqrt(N)) time complexity. 
//It is particularly useful when dealing with static array problems where updates are not required.

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;

int n, q;
int ar[N];
int K;

struct Query {
    int index, L, R;
    bool operator < (const Query &other) const {
        int block_own = L / K;
        int block_other = other.L / K;
        if (block_own == block_other)
            return R < other.R;
        return block_own < block_other;
    }
} query[N];

int freq[N];
int distinct = 0;

void add(int index) {
    freq[ar[index]]++;
    if (freq[ar[index]] == 1) distinct++;
}

void remove(int index) {
    freq[ar[index]]--;
    if (freq[ar[index]] == 0) distinct--;
}

vector<int> mo_algorithm() {
    vector<int> ans(q);
    sort(query, query + q);
    int L = 0, R = -1;
    
    for (int i = 0; i < q; i++) {
        while (R < query[i].R) add(++R);
        while (L < query[i].L) remove(L++);
        while (R > query[i].R) remove(R--);
        while (L > query[i].L) add(--L);
        ans[query[i].index] = distinct;
    }
    return ans;
}

void solve() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ar[i]);
    }
    
    K = max(1, (int)sqrt(n));
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--, r--; 
        query[i] = {i, l, r};
    }
    
    vector<int> ans = mo_algorithm();
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    solve();
    return 0;
}

