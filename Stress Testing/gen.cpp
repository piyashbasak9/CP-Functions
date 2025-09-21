#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline ll gen_random(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

inline double gen_random_real(double l, double r) {
    return uniform_real_distribution<double>(l, r)(rng);
}

int main(int argc, char* args[]) {
    int _ = atoi(args[1]);
    mt19937 mt(_);
    
    int n = gen_random(1, 5);
    cout << n << '\n';
    
    vector<int> per;
    string s;
    
    for (int i = 0; i < n; ++i) {
        per.push_back(i + 1);
        cout << gen_random(-50, 50) << " \n"[i == n - 1];
        char c = 'a' + gen_random(0, 25);
        s += c;
    }
    
    shuffle(per.begin(), per.end(), rng); // generates permutation
    
    return 0;
}
