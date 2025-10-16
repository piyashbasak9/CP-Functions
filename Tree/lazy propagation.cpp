#include<bits/stdc++.h>
#define int long long int
#define ll long long
 
using namespace std;
int ts=1;
// start journey
 
const int N = 2e5+10;
int n, q;
int ar[N];
 
struct info {
    int sum;
    int lazy_add;
    int lazy_increment;
} tree[N * 4];
 
void push(int node, int l, int r) {
    if (tree[node].lazy_add || tree[node].lazy_increment) {
        int len = r - l + 1;
        tree[node].sum += tree[node].lazy_add * len + tree[node].lazy_increment * (len * (len - 1)) / 2;
 
        if (l != r) {
            int mid = (l + r) / 2;
            int left = node * 2, right = left + 1;
 
            tree[left].lazy_add += tree[node].lazy_add;
            tree[left].lazy_increment += tree[node].lazy_increment;
 
            tree[right].lazy_add += tree[node].lazy_add + tree[node].lazy_increment * (mid - l + 1);
            tree[right].lazy_increment += tree[node].lazy_increment;
        }
 
        tree[node].lazy_add = 0;
        tree[node].lazy_increment = 0;
    }
}
 
void build(int node, int l, int r) {
    if (l == r) {
        tree[node].sum = ar[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}
 
void update(int node, int l, int r, int i, int j, int base) {
    push(node, l, r);
    if (i > r || j < l) return;
    if (l >= i && r <= j) {
        tree[node].lazy_add += base + (l - i);
        tree[node].lazy_increment += 1;
        push(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(node * 2, l, mid, i, j, base);
    update(node * 2 + 1, mid + 1, r, i, j, base);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}
 
int query(int node, int l, int r, int i, int j) {
    push(node, l, r);
    if (i > r || j < l) return 0;
    if (l >= i && r <= j) return tree[node].sum;
    int mid = (l + r) / 2;
    return query(node * 2, l, mid, i, j) + query(node * 2 + 1, mid + 1, r, i, j);
}
 
void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    build(1, 0, n - 1);
    while (q--) {
        int typ, l, r;
        cin >> typ >> l >> r;
        l--, r--;
        if (typ == 1) {
            update(1, 0, n - 1, l, r, 1);
        } else {
            cout << query(1, 0, n - 1, l, r) << endl;
        }
    }
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
