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

int n , q;
int ar[N];

int K;
struct Query{
    int index, L, R;
    bool operator < (const Query &other) const {
		int block_own = L/K;
		int block_other = other.L/K;
		if(block_own == block_other)
            return R < other.R;
		return block_own < block_other;
	}
}query[N];


map<int,int>mp;

void add(int index){
    mp[ar[index]]++;
}
 
void remove(int index){
    mp[ar[index]]--;
    if(mp[ar[index]] == 0){
        mp.erase(ar[index]);
    }
}


void solve(){
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        cin >> ar[i];
    }
    K = sqrt(n);               // block size
    for(int i = 0; i < q; i++){
        int l , r;cin >> l >> r;
        l--, r--;
        query[i].L = l;
        query[i].R = r;
        query[i].index = i;
    }
    int ans[q];
    sort(query, query+q);
    int L=0, R=-1;
    for(int i=0;i<q;i++){
        while(R<query[i].R) add(++R);
        while(L<query[i].L) remove(L++);
        while(R>query[i].R) remove(R--);
        while(L>query[i].L) add(--L);
        ans[query[i].index] = mp.size();
    }
    for(int i = 0; i < q; i++){
        cout << ans[i] << endl;
    }
    
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
