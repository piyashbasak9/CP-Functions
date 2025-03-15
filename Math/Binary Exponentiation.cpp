ll Expo(ll a,ll b)
{
    a%=mod;
    ll res=1;
    while(b>0){
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b=b>>1;
    }
    return res;
}
