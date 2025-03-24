// it's apply for find inverse module, when mod can be a composite number

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll gcd = extended_gcd(a, m, x, y);
    if (gcd != 1) return -1; // No inverse exists
    else return (x % m + m) % m; // Ensure positive result
}
