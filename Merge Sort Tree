vector<int>tree[N * 4];

void store(int node , int l, int r){
    if(l==r){
        tree[node].push_back(ar[l]);
        return ;
    }
    int left=node*2;
    int right=(node*2)+1;
    int mid=(l+r)/2;
    store(left,l,mid);
    store(right,mid+1,r);
    int i = 0, j = 0;
    while(i < tree[left].size() && j < tree[right].size()){
        if(tree[left][i] < tree[right][j]){
            tree[node].push_back(tree[left][i]);
            i++;
        }
        else{
            tree[node].push_back(tree[right][j]);
            j++;
        }
    }
    while(i < tree[left].size()){
        tree[node].push_back(tree[left][i]);
        i++;
    }
    while(j < tree[right].size()){
        tree[node].push_back(tree[right][j]);
        j++;
    }
}

 
int help(int node , int l, int r, int i , int j, int k){
    if(l>=i && r<=j){
        int value = tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
        return value;
    }
    if(r<i || l>j){
        return 0;
    }
    int left=node*2;
    int right=(node*2)+1;
    int mid=(l+r)/2;
    return help(left,l,mid,i,j, k)+help(right,mid+1,r,i,j, k);
}
