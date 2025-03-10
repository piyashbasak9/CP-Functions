struct info{
    ll lagy, sum;
    info(){
        lagy = 0;
        sum = 0;
    }
} tree[N * 4];

void push(int node, int l, int r){
    if(tree[node].lagy != 0){
        tree[node].sum += (r-l+1) * tree[node].lagy;
        if(l != r){
            int left = node * 2 , right = left + 1;

            tree[left].lagy += tree[node].lagy;
            tree[right].lagy += tree[node].lagy; 
        }
        tree[node].lagy = 0;
    }
}

void store(int node , int l, int r){
    if(l==r){
        tree[node].sum = 0;
        tree[node].lagy = 0;
        return ;
    }
    int left=node*2;
    int right=(node*2)+1;
    int mid=(l+r)/2;
    store(left,l,mid);
    store(right,mid+1,r);
    tree[node].sum = tree[left].sum + tree[right].sum;
}

void update(int node , int l , int r , int i, int j, ll val){
    push(node, l , r);
    if(i > r || j < l){
        return;
    }
    if(l >= i && r <= j){
        tree[node].lagy += val;
        push(node, l , r);
        return;
    }
    int left = node*2;
    int right = (node*2)+1;
    int mid = (l + r) / 2;
    update(left, l , mid, i, j, val);
    update(right, mid+1, r, i, j, val);
    tree[node].sum = tree[left].sum + tree[right].sum;
}
 
ll query(int node , int l, int r, int i , int j){
    push(node, l , r);
    if(l>=i && r<=j){
        return tree[node].sum;
    }
    if(r<i || l>j){
        return 0;
    }
    int left=node*2;
    int right=(node*2)+1;
    int mid=(l+r)/2;
    return query(left,l,mid,i,j) + query(right,mid+1,r,i,j);
}

void solve(){
    cin >> n >> m;
    store(1, 0, n-1);
    for(int i = 0; i < m; i++){
        int typ ; cin >> typ;
        if(typ == 1){
            ll l , r , val;
            cin >> l >> r >> val;
            r--;
            update(1, 0, n-1, l , r , val);
        }
        else{
            ll x ; cin >> x;
            cout <<  query(1, 0, n-1, x, x) << endl;

        }
    }
    
}
