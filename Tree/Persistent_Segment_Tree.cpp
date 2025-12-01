#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define ll long long

const int mod = 1000000007;
const int N = 2e5+10;

struct node{
  int val ;
  node* lc; node* rc;
};

int ar[N], n , q;

node* version[N];

node* build(int l, int r){
  if(l == r){
    node* me = new node();
    me->val = ar[l];
    me->lc = NULL;
    me->rc = NULL;
    return me;
  }
  int mid = (l + r) / 2;
  node* me = new node();
  me->lc = build(l, mid);
  me->rc = build(mid+1, r);
  me->val = me->lc->val + me->rc->val;
  return me;
}

int query(node* me, int l, int r, int i, int j){
  if(r < i || l > j){
    return 0;
  }
  if(l >= i && r <= j){
    return me->val;
  }
  int mid = (l + r) / 2;

  return query(me->lc, l, mid, i, j) + query(me->rc, mid+1, r, i, j);
}


node* update(node* me, int l, int r, int x, int val){
  if(l == r){
    node* newme = new node();
    newme->val = val;
    newme->lc = NULL;
    newme->rc = NULL;
    return newme;
  }

  int mid = (l + r) / 2;
  node* newme = new node();

  if(x <= mid){
    newme->lc = update(me->lc, l, mid, x, val);
    newme->rc = me->rc;
  }
  else{
    newme->rc = update(me->rc, mid+1, r, x, val);
    newme->lc = me->lc;
  }
  newme->val = newme->lc->val + newme->rc->val;
  return newme;
}



void solve(){
  cin >> n >> q;
  for(int i = 1; i <= n; i++){
    cin >> ar[i];
  }
  version[1] = build(1, n);
  int ver = 1;
  while(q--){
    int typ ; cin >> typ;
    if(typ == 1){
      int k, a, x; cin >> k >> a >> x;
      version[k] = update(version[k], 1, n, a, x);
    }
    else if(typ == 2){
      int k, a, b; cin >> k >> a >> b;
      cout << query(version[k], 1, n, a, b) << endl;
    }
    else{
      int k; cin >> k;
      ver++;
      version[ver] = version[k];
    }

  }
}

int32_t main(){
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  ll t=1;
  // cin >> t;
  while(t--){
    solve();
  }
}
