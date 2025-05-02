// Range increment and decrement (increment before decrement) and number of positive elements in the whole array
const int N = 2e6+6;

int st[4 * N], cnt[4 * N];

void add(int l, int r, ll x, int u = 1, int s = 0, int e = N - 1) {
  if (s > r or e < l)  return ;
  int v = u << 1, w = v | 1, m = s + e >> 1;
  if (l <= s and e <= r) {
    cnt[u] += x;
    if (cnt[u])  st[u] = e - s + 1;
    else  st[u] = (s == e)? 0: st[v] + st[w];
    return ;
  }
  add(l, r, x, v, s, m);
  add(l, r, x, w, m + 1, e);
  if (!cnt[u])  st[u] = st[v] + st[w];
}
