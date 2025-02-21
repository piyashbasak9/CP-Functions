struct  segtree{
    int tree[N * 4];
    void build(int node , int l, int r){
        if(l==r){
            tree[node] = 0;
            return ;
        }
        int left = node*2, right = (node * 2) + 1;
        int mid = (l + r) / 2;
        build(left, l, mid);
        build(right, mid+1, r);
        tree[node] = tree[left] + tree[right];
    }

    void update(int node , int l , int r , int i, int val){
        if(l == r && l == i){
            tree[node] = val;
            return;
        }
        if(i > r || i < l) return;
        int left = node * 2, right = (node * 2) + 1;
        int mid = (l + r) / 2;
        update(left, l, mid, i, val);
        update(right, mid+1, r, i, val);
        tree[node] = tree[left] + tree[right];
    }

    int query(int node , int l, int r, int i , int j){
        if(l >= i && r <= j) return tree[node];
        if(r < i || l > j) return 0;
        int left = node*2, right = (node*2) + 1;
        int mid = (l + r) / 2;
        return query(left, l, mid, i, j) + query(right, mid+1, r, i, j);
    }
};

segtree tree;
