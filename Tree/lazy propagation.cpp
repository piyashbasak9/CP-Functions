#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 10;

int n;
int ar[N];
int seg[4*N], lazy[4*N];

void build(int ind, int l, int r){
    if(l == r){
        seg[ind] = ar[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*ind, l, mid);
    build(2*ind+1, mid+1, r);
    seg[ind] = seg[2*ind] + seg[2*ind+1];
}

void push(int ind, int l, int r){
    if(lazy[ind] != 0){
        seg[ind] += (r - l + 1) * lazy[ind];
        
        if(l != r){
            lazy[2*ind] += lazy[ind];
            lazy[2*ind+1] += lazy[ind];
        }
        lazy[ind] = 0;
    }
}

void update(int ind, int l, int r, int ql, int qr, int val){
    push(ind, l, r);

    if(r < ql || l > qr) return;

    if(l >= ql && r <= qr){
        lazy[ind] += val;
        push(ind, l, r);
        return;
    }

    int mid = (l + r) / 2;
    update(2*ind, l, mid, ql, qr, val);
    update(2*ind+1, mid+1, r, ql, qr, val);

    seg[ind] = seg[2*ind] + seg[2*ind+1];
}

int query(int ind, int l, int r, int ql, int qr){
    push(ind, l, r);

    if(r < ql || l > qr) return 0;

    if(l >= ql && r <= qr){
        return seg[ind];
    }

    int mid = (l + r) / 2;
    return query(2*ind, l, mid, ql, qr) +
           query(2*ind+1, mid+1, r, ql, qr);
}










struct ST {
  #define lc (n << 1)
  #define rc ((n << 1) + 1)
  long long t[4 * N], lazy[4 * N];
  ST() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) { // change this
    if (lazy[n] == 0) return;
    t[n] = t[n] + lazy[n] * (e - b + 1);
    if (b != e) {
      lazy[lc] = lazy[lc] + lazy[n];
      lazy[rc] = lazy[rc] + lazy[n];
    }
    lazy[n] = 0;
  }
  inline long long combine(long long a,long long b) { // change this
    return a + b;
  }
  inline void pull(int n) { // change this
    t[n] = t[lc] + t[rc];
  }
  void build(int n, int b, int e) {
    lazy[n] = 0; // change this
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, long long v) {
    push(n, b, e);
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      lazy[n] = v; //set lazy
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  long long query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j) return 0; //return null
    if (i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
}t;
