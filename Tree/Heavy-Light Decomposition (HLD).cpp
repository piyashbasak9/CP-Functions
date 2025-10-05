#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int N=200005,mod=1e9+7;
vector<pair<int,int>> g[N];
int p[N],d[N],sz[N],h[N],pos[N],heavy[N],a[N],cur,n,q;

struct seg{
    int n;vector<int>s,lz;
    void init(int m){n=m;s.assign(4*m,0);lz.assign(4*m,1);}
    void push(int p,int l,int r){
        if(lz[p]!=1){
            int m=(l+r)>>1;
            apply(p<<1,l,m,lz[p]);
            apply(p<<1|1,m+1,r,lz[p]);
            lz[p]=1;
        }
    }
    void apply(int p,int l,int r,int v){
        s[p]=s[p]*v%mod;
        lz[p]=lz[p]*v%mod;
    }
    void upd(int p,int l,int r,int i,int j,int v){
        if(i>r||j<l)return;
        if(i<=l&&r<=j){apply(p,l,r,v);return;}
        push(p,l,r);
        int m=(l+r)>>1;
        upd(p<<1,l,m,i,j,v);upd(p<<1|1,m+1,r,i,j,v);
        s[p]=(s[p<<1]+s[p<<1|1])%mod;
    }
    int qry(int p,int l,int r,int i,int j){
        if(i>r||j<l)return 0;
        if(i<=l&&r<=j)return s[p];
        push(p,l,r);
        int m=(l+r)>>1;
        return (qry(p<<1,l,m,i,j)+qry(p<<1|1,m+1,r,i,j))%mod;
    }
}st;

int dfs(int u,int par){
    p[u]=par;sz[u]=1;heavy[u]=-1;
    for(auto [v,w]:g[u])if(v!=par){
        d[v]=d[u]+1;a[v]=w;
        sz[u]+=dfs(v,u);
        if(heavy[u]==-1||sz[v]>sz[heavy[u]])heavy[u]=v;
    }
    return sz[u];
}

void decomp(int u,int top){
    h[u]=top;pos[u]=++cur;
    if(heavy[u]!=-1)decomp(heavy[u],top);
    for(auto [v,w]:g[u])if(v!=p[u]&&v!=heavy[u])decomp(v,v);
}

void updr(int l,int r,int v){st.upd(1,1,n,l,r,v);}
int qryr(int l,int r){return st.qry(1,1,n,l,r);}

void updp(int u,int v,int x){
    while(h[u]!=h[v]){
        if(d[h[u]]<d[h[v]])swap(u,v);
        updr(pos[h[u]],pos[u],x);
        u=p[h[u]];
    }
    if(d[u]>d[v])swap(u,v);
    if(u!=v)updr(pos[u]+1,pos[v],x);
}

int qryp(int u,int v){
    int res=0;
    while(h[u]!=h[v]){
        if(d[h[u]]<d[h[v]])swap(u,v);
        res=(res+qryr(pos[h[u]],pos[u]))%mod;
        u=p[h[u]];
    }
    if(d[u]>d[v])swap(u,v);
    if(u!=v)res=(res+qryr(pos[u]+1,pos[v]))%mod;
    return res;
}

int32_t main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    dfs(1,-1);decomp(1,1);
    vector<int> tmp(n+1);
    for(int i=1;i<=n;i++) tmp[pos[i]]=a[i];
    for(int i=1;i<=n;i++) a[i]=tmp[i];
    st.init(n);
    function<void(int,int,int,int,int)> build=[&](int p,int l,int r,int _,int __){
        if(l==r){st.s[p]=a[l]%mod;return;}
        int m=(l+r)>>1;
        build(p<<1,l,m,_,__);build(p<<1|1,m+1,r,_,__);
        st.s[p]=(st.s[p<<1]+st.s[p<<1|1])%mod;
    };
    build(1,1,n,0,0);

    while(q--){
        int u,v,x;cin>>u>>v>>x;
        updp(u,v,x);
        cout<<qryp(u,v)%mod<<endl;
    }
}
