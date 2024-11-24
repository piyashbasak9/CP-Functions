#include<bits/stdc++.h>
//#define int long long int
#define ll long long 
#define mod 1000000007
#define int_max 1e18
#define inf 10000001
#define hae cout << "YES\n";
#define na cout << "NO\n";
#define endl "\n"

using namespace std;
int ts=1;
// start journey

const int N = 2e5+10;


vector<vector<ll>> multiply(const vector<vector<ll>>& A, const vector<vector<ll>>& B) { // multiply (n * n) with (n * n);
    int nn = A.size();
    vector<vector<ll>> C(nn, vector<ll>(nn, 0));
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nn; j++) {
            for (int k = 0; k < nn; k++) {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
            }
        }
    }
    return C;
}


vector<ll> multiplyVector(const vector<vector<ll>>& A, const vector<ll>& B) { // multiply (n * n) with (n * 1); 
    int nn = A.size();
    vector<ll> C(nn, 0);
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nn; j++) {
            C[i] = (C[i] + (A[i][j] * B[j]) % mod) % mod;
        }
    }
    return C;
}

vector<vector<ll>> power(vector<vector<ll>> M, ll expo) { // exponentiation
    int size = M.size();
    vector<vector<ll>> ans(size, vector<ll>(size, 0));
    for (int i = 0; i < size; i++) ans[i][i] = 1; // Identity matrix

    while (expo) {
        if (expo & 1)
            ans = multiply(ans, M);
        M = multiply(M, M);
        expo >>= 1;
    }
    return ans;
}


void solve(){
    ll n; cin >> n;
    if(n == 1){
        cout << 2 << endl;
        return;
    }
    else if(n == 2){
        cout << 3 << endl;
        return;
    }
    vector<vector<ll>> cal = {{3 , 2, 1, 3}, {1, 0, 0, 0}, {0, 1, 0 ,0}, {0, 0, 0, 1}};
    vector<vector<ll>> ans = power(cal, n-2);
    vector<ll> tamp = {3, 2, 1, 1};
    vector<ll> res = multiplyVector(ans, tamp); 
    cout << res[0] << endl;


}


int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t=1;
    //cin >> t;
    while(t--){
        solve();
    }
}
