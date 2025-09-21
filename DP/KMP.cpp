#include <vector>
#include <string>
using namespace std;
typedef long long ll;

vector<ll> build_lps(string &p) {
    ll sz = p.size();
    vector<ll> lps(sz, 0);
    ll j = 0;
    lps[0] = 0;
    for (ll i = 1; i < sz; i++) {
        while (j >= 0 && p[i] != p[j]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        j++;
        lps[i] = j;
    }
    return lps;
}

vector<ll> ans;

void kmp(vector<ll> &lps, string &s, string &p) {
    ll psz = p.size(), ssz = s.size();
    ll j = 0;
    for (ll i = 0; i < ssz; i++) {
        while (j >= 0 && p[j] != s[i]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        j++;
        if (j == psz) {
            j = lps[j - 1];
            ans.push_back(i - psz + 1); // pattern found at position i-psz+1
        }
    }
}
