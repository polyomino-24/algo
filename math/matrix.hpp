ll mod;
using M = vector<vector<ll>>;
M operator*(M &a, M &b){
    auto res = a;
    rep(i,a.size())rep(j,a[0].size()){
        auto &t = res[i][j];
        t = 0;
        rep(k,a[0].size()){
            (t += a[i][k]*b[k][j]%mod) %= mod;
        }
    }
    return res;
}
M power(M a, ll k){
    auto res = a;
    rep(i,a.size())rep(j,a.size())res[i][j] = (i == j ? 1 : 0);
    while(k){
        if(k&1){
            res = res * a;
        }
        k>>=1;
        a = a * a;
    }
    return res;
}
