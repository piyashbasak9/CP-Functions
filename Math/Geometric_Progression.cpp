ll geo_all(ll n, ll x) { //1 + x + x^2 + x^3....x^n = f(n, x)
	if (n == 0) return 0;
	ll ret = 1ll * (1 + x) * geo_all(n / 2, 1ll * x * x % mod) % mod;
	if (n & 1) ret = (1 + 1ll * x * ret) % mod;
	return ret;
}
