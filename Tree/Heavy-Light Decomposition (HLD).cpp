
// for edge weight


#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

const int N=200005,mod=1e9+7; // 🔹 Adjust limit & mod as needed
vector<pair<int,int>> g[N];
int p[N],d[N],sz[N],h[N],pos[N],heavy[N],a[N],cur,n,q;

// 🔹 Segment Tree (supports range multiply & range sum query)
struct seg{
    int n;vector<int>s,lz;
    void init(int m){n=m;s.assign(4*m,0);lz.assign(4*m,1);} // lazy = 1 for multiplication

    // 🔹 Apply lazy value to a node
    void apply(int p,int l,int r,int v){
        s[p]=s[p]*v%mod; // multiply all values in segment
        lz[p]=lz[p]*v%mod; // combine lazy values
    }

    // 🔹 Push lazy to children
    void push(int p,int l,int r){
        if(lz[p]!=1){
            int m=(l+r)>>1;
            apply(p<<1,l,m,lz[p]);
            apply(p<<1|1,m+1,r,lz[p]);
            lz[p]=1;
        }
    }

    // 🔹 Range update: multiply values [i, j] by v
    void upd(int p,int l,int r,int i,int j,int v){
        if(i>r||j<l)return;
        if(i<=l&&r<=j){apply(p,l,r,v);return;}
        push(p,l,r);
        int m=(l+r)>>1;
        upd(p<<1,l,m,i,j,v);
        upd(p<<1|1,m+1,r,i,j,v);
        s[p]=(s[p<<1]+s[p<<1|1])%mod; // 🔹 merge (change to gcd/min/xor if needed)
    }

    // 🔹 Range query: sum of values in [i, j]
    int qry(int p,int l,int r,int i,int j){
        if(i>r||j<l)return 0;
        if(i<=l&&r<=j)return s[p];
        push(p,l,r);
        int m=(l+r)>>1;
        return (qry(p<<1,l,m,i,j)+qry(p<<1|1,m+1,r,i,j))%mod; // 🔹 combine query results
    }
}st;

// 🔹 DFS to find sizes, depths, and heavy child
int dfs(int u,int par){
    p[u]=par;sz[u]=1;heavy[u]=-1;
    for(auto [v,w]:g[u])if(v!=par){
        d[v]=d[u]+1;a[v]=w;
        sz[u]+=dfs(v,u);
        if(heavy[u]==-1||sz[v]>sz[heavy[u]])heavy[u]=v;
    }
    return sz[u];
}

// 🔹 Decompose into heavy paths
void decomp(int u,int top){
    h[u]=top;pos[u]=++cur;
    if(heavy[u]!=-1)decomp(heavy[u],top);
    for(auto [v,w]:g[u])if(v!=p[u]&&v!=heavy[u])decomp(v,v);
}

// 🔹 Short wrappers for segtree operations
void updr(int l,int r,int v){st.upd(1,1,n,l,r,v);}
int qryr(int l,int r){return st.qry(1,1,n,l,r);}

// 🔹 Update all edges on path (multiply by x)
void updp(int u,int v,int x){
    while(h[u]!=h[v]){
        if(d[h[u]]<d[h[v]])swap(u,v);
        updr(pos[h[u]],pos[u],x);
        u=p[h[u]];
    }
    if(d[u]>d[v])swap(u,v);
    if(u!=v)updr(pos[u]+1,pos[v],x);
}

// 🔹 Query sum of all edges on path
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
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    dfs(1,-1);
    decomp(1,1);

    // 🔹 Map edge values to HLD position
    vector<int> tmp(n+1);
    for(int i=1;i<=n;i++) tmp[pos[i]]=a[i];
    for(int i=1;i<=n;i++) a[i]=tmp[i];

    st.init(n);

    // 🔹 Build initial segment tree
    function<void(int,int,int)> build=[&](int p,int l,int r){
        if(l==r){st.s[p]=a[l]%mod;return;}
        int m=(l+r)>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        st.s[p]=(st.s[p<<1]+st.s[p<<1|1])%mod;
    };
    build(1,1,n);

    // 🔹 Handle queries
    while(q--){
        int u,v,x;cin>>u>>v>>x;
        updp(u,v,x); // multiply all edges on path u-v by x
        cout<<qryp(u,v)%mod<<endl; // print sum of path
    }
}







// for vartex weight


#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

const int N=200005,mod=1e9+7; // 🔹 Adjust N & mod if needed
vector<int> g[N];
int p[N],d[N],sz[N],h[N],pos[N],heavy[N],a[N],cur,n,q;

// 🔹 Segment Tree (currently supports range add & range sum)
struct seg{
    int n;vector<int>s,lz;
    void init(int m){n=m;s.assign(4*m,0);lz.assign(4*m,0);} // 🔹 set lazy=0 for add updates

    // 🔹 Apply an update to a segment
    void apply(int p,int l,int r,int v){
        s[p]=(s[p]+v*(r-l+1))%mod; // 🔹 sum += v * length
        lz[p]=(lz[p]+v)%mod;       // 🔹 accumulate lazy add
    }

    // 🔹 Push lazy values to child segments
    void push(int p,int l,int r){
        if(lz[p]){
            int m=(l+r)>>1;
            apply(p<<1,l,m,lz[p]);
            apply(p<<1|1,m+1,r,lz[p]);
            lz[p]=0;
        }
    }

    // 🔹 Range update: add v to range [i, j]
    void upd(int p,int l,int r,int i,int j,int v){
        if(i>r||j<l)return;
        if(i<=l&&r<=j){apply(p,l,r,v);return;}
        push(p,l,r);
        int m=(l+r)>>1;
        upd(p<<1,l,m,i,j,v);
        upd(p<<1|1,m+1,r,i,j,v);
        s[p]=(s[p<<1]+s[p<<1|1])%mod; // 🔹 combine results (change for gcd/xor/min/etc.)
    }

    // 🔹 Range query: get sum in range [i, j]
    int qry(int p,int l,int r,int i,int j){
        if(i>r||j<l)return 0;
        if(i<=l&&r<=j)return s[p];
        push(p,l,r);
        int m=(l+r)>>1;
        return (qry(p<<1,l,m,i,j)+qry(p<<1|1,m+1,r,i,j))%mod; // 🔹 combine query results
    }
}st;

// 🔹 DFS to compute size, depth, and heavy child
int dfs(int u,int par){
    p[u]=par;sz[u]=1;heavy[u]=-1;
    for(int v:g[u])if(v!=par){
        d[v]=d[u]+1;
        sz[u]+=dfs(v,u);
        if(heavy[u]==-1||sz[v]>sz[heavy[u]])heavy[u]=v;
    }
    return sz[u];
}

// 🔹 Decompose tree into heavy-light chains
void decomp(int u,int top){
    h[u]=top;pos[u]=++cur;
    if(heavy[u]!=-1)decomp(heavy[u],top);
    for(int v:g[u])if(v!=p[u]&&v!=heavy[u])decomp(v,v);
}

// 🔹 Segment tree wrappers for simplicity
void updr(int l,int r,int v){st.upd(1,1,n,l,r,v);}
int qryr(int l,int r){return st.qry(1,1,n,l,r);}

// 🔹 Update all vertices on the path u→v
void updp(int u,int v,int x){
    while(h[u]!=h[v]){
        if(d[h[u]]<d[h[v]])swap(u,v);
        updr(pos[h[u]],pos[u],x);
        u=p[h[u]];
    }
    if(d[u]>d[v])swap(u,v);
    updr(pos[u],pos[v],x); // 🔹 include both u and v
}

// 🔹 Query sum of vertex values along path u→v
int qryp(int u,int v){
    int res=0;
    while(h[u]!=h[v]){
        if(d[h[u]]<d[h[v]])swap(u,v);
        res=(res+qryr(pos[h[u]],pos[u]))%mod;
        u=p[h[u]];
    }
    if(d[u]>d[v])swap(u,v);
    res=(res+qryr(pos[u],pos[v]))%mod;
    return res;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i]; // 🔹 vertex weights

    // 🔹 read unweighted tree edges
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 🔹 build HLD
    dfs(1,-1);
    decomp(1,1);

    // 🔹 reorder vertex weights by position
    vector<int> tmp(n+1);
    for(int i=1;i<=n;i++) tmp[pos[i]]=a[i];
    for(int i=1;i<=n;i++) a[i]=tmp[i];

    // 🔹 build segment tree
    st.init(n);
    function<void(int,int,int)> build=[&](int p,int l,int r){
        if(l==r){st.s[p]=a[l]%mod;return;}
        int m=(l+r)>>1;
        build(p<<1,l,m);
        build(p<<1|1,m+1,r);
        st.s[p]=(st.s[p<<1]+st.s[p<<1|1])%mod;
    };
    build(1,1,n);

    // 🔹 query format:
    // 1 u v x → add x to all vertices on path (u,v)
    // 2 u v   → query sum of vertices on path (u,v)
    while(q--){
        int t;cin>>t;
        if(t==1){
            int u,v,x;cin>>u>>v>>x;
            updp(u,v,x);
        }else{
            int u,v;cin>>u>>v;
            cout<<qryp(u,v)<<endl;
        }
    }
}

