#include <bits/stdc++.h>
#define int long long
#define ll long long
#define mod 1000000007
#define endl "\n"

using namespace std;

// Precompute factorials and inverse factorials
const int N = 1e6 + 10;
vector<int> fact(N), invFact(N);

// Function to compute power under modulo
int power(int a, int b, int m) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[N - 1] = power(fact[N - 1], mod - 2, mod);
    for (int i = N - 2; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

// Function to compute nPr
int nPr(int n, int r) {
    if (r > n || r < 0) return 0; // Invalid case
    return (fact[n] * invFact[n - r]) % mod;
}

// Function to compute nCr
int nCr(int n, int r) {
    if (r > n || r < 0) return 0; // Invalid case
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Precompute factorials and inverse factorials
    precompute();

    int n, r;
    cout << "Enter n and r: ";
    cin >> n >> r;

    // Calculate nPr and nCr
    cout << "nPr(" << n << ", " << r << ") = " << nPr(n, r) << endl;
    cout << "nCr(" << n << ", " << r << ") = " << nCr(n, r) << endl;

    return 0;
}
