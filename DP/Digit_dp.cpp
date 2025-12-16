#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define ll long long

const int mod = 1000000007;
const int N = 1e4+10;

string chl, chr;
int k; 
int dp[N][100][2][2];

int f(int ind, int sum, int sw1, int sw2){
  if(ind == chr.size()){
    return sum == 0;
  }
  if(dp[ind][sum][sw1][sw2] != -1){
    return dp[ind][sum][sw1][sw2];
  }
  int ans = 0;
  int l = (sw1 == 0) ? chl[ind] - '0' : 0;
  int r = (sw2 == 0) ? chr[ind] - '0' : 9;

  for(int i = l; i <= r; i++){
    int n_sw1 = (sw1 == 0 && i == l) ? 0 : 1;
    int n_sw2 = (sw2 == 0 && i == r) ? 0 : 1;

    ans += f(ind+1, (sum + i) % k, n_sw1, n_sw2);
    ans %= mod;
  }
  return dp[ind][sum][sw1][sw2] = ans;
}

void solve(){
  cin >> chr >> k;
  chl = "1";
  while(chl.size() < chr.size()){
    chl = "0" + chl;
  }
  memset(dp, -1, sizeof(dp));
  int ans = f(0, 0, 0, 0) % mod;
  cout << ans << endl;
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
