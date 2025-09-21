#include <bits/stdc++.h>
using namespace std;

int dp[10][90][90][2];
string num;
int c;

int fun(int pos, int digSum, int dig, int smaint) {
    if (pos == num.size()) {
        if (dig == 0 && digSum == 0) return 1;
        return 0;
    }
    
    if (dp[pos][digSum][dig][smaint] != -1) 
        return dp[pos][digSum][dig][smaint];
    
    int ans = 0;
    int limit = num[pos] - '0';
    if (smaint == 1) limit = 9;
    
    for (int i = 0; i <= limit; i++) {
        int nsm = (i < limit) || smaint;
        int ndigSum = (digSum + i) % c;
        int ndig = (dig * 10 + i) % c;
        ans += fun(pos + 1, ndigSum, ndig, nsm);
    }
    
    return dp[pos][digSum][dig][smaint] = ans;
}

int solve(string n) {
    num = n;
    memset(dp, -1, sizeof(dp));
    return fun(0, 0, 0, 0);
}

int main() {
    string n;
    cin >> n >> c;
    cout << solve(n) << endl;
    return 0;
}
