void fft(vector<complex<double>> &a, const bool rev = false){
    const int n = (int) a.size();
    assert((n & (n - 1)) == 0);
    if(n == 1)return;
    vector<complex<double>> b, c;
    rep(i,n){
        (i & 1 ? c : b).push_back(a[i]);
    }
    fft(b, rev);
    fft(c, rev);
    complex<double> w = 1;
    const complex<double> t = polar(1.0, (rev ? -1 : 1) * 2 * acos(-1) / n);
    rep(i,n){
        a[i] = b[i & ((n >> 1) - 1)] + w * c[i & ((n >> 1) - 1)];
        w *= t;
    }
}
vector<int> mul(const vector<int> &a, const vector<int> &b){
    int s = (int) a.size() + (int) b.size() - 1;
    int t = 1;
    while(t < s) t *= 2;
    vector<complex<double>> A(t), B(t);
    rep(i,a.size())A[i] = a[i];
    rep(i,b.size())B[i] = b[i];
    fft(A);
    fft(B);
    rep(i,t)A[i] *= B[i];
    fft(A, true);
    vector<int> res(s);
    rep(i,s)res[i] = round(A[i].real()/t);
    return res;
}
