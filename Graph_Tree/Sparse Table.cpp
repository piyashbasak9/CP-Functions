int sparse[200010][20];


void store(int ar[], int n){
    for(int i=0; i<n; i++){
        sparse[i][0]=ar[i];
    }
    int l=1,r=n-1;
    for(int i=1; i<=n; i*=2){
        for(int j=0; (j+i)<=r; j++){
            sparse[j][l]=__gcd(sparse[j][l-1] , sparse[j+i][l-1]);
        }
        r-=i,l++;
    }
}

int find_range(int l, int r){
    int x=(r-l+1);
    int bit=0,bit_val=1,ans=0;
    while(x>0){
        if(x&1){
            ans=__gcd(ans,sparse[l][bit]);
            l+=bit_val;
        }
        bit++,bit_val*=2;
        x>>=1;
    }
    return ans;
}
