//原子根
//const mint g = 3;
void ntt(vector<mint> &a, const bool rev = false){
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    if(n == 1)return;
    vector<mint> b, c;
    rep(i,n){
        (i & 1 ? c : b).push_back(a[i]);
    }
    ntt(b, rev);
    ntt(c, rev);
    mint w = 1;
    const mint t = pow(g, rev ? (mint::getmod()-1 -(mint::getmod()-1)/n) : (mint::getmod()-1)/n);
    rep(i,n){
        a[i] = b[i & ((n >> 1) - 1)] + w * c[i & ((n >> 1) - 1)];
        w *= t;
    }
}
vector<mint> mul(const vector<mint> &a, const vector<mint> &b){
    int s = (int) a.size() + (int) b.size() - 1;
    int t = 1;
    while(t < s) t *= 2;
    vector<mint> A(t), B(t);
    rep(i,a.size())A[i] = a[i];
    rep(i,b.size())B[i] = b[i];
    ntt(A);
    ntt(B);
    rep(i,t)A[i] *= B[i];
    ntt(A, true);
    vector<mint> res(s);
    const mint inv = mint(1)/t;
    rep(i,s)res[i] = A[i] * inv;
    return res;
}
