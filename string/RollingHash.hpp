static constexpr int SZ = 323456;
int basepow[2][SZ];
struct RollingHash{
    static constexpr int mod = 1e9+7;
    static const int basemod[2];
    vector<int> pre[2];
    const string s;
    const int n;
    void make(){
        rep(i,2){
            basepow[i][0] = 1;
            rep(j,SZ-1){
                basepow[i][j+1] = (long long)basepow[i][j] * basemod[i] % mod;
            }
        }
    }
    RollingHash(const string &_s) : s(_s),n((int)s.size()){
        if(!basepow[0][0])make();
        pre[0].resize(n + 1);
        pre[1].resize(n + 1);
        rep(i,2){
            rep(j,n){
                pre[i][j+1] =((long long)pre[i][j] * basemod[i] % mod + (int)s[j]) % mod;
            }
        }
    }
    // [l,r)
    ll cal_hash(int l, int r){
        ll a = (pre[0][r] - (long long)pre[0][l] * basepow[0][r-l] % mod + mod) % mod;
        ll b = (pre[1][r] - (long long)pre[1][l] * basepow[1][r-l] % mod + mod) % mod;
        return (ll)(a<<30) + b;
    }
    static ll cal(const string &t){
        ll temp[2] = {};
        rep(i,t.size()){
            rep(j,2){
                temp[j] = (temp[j] * basemod[j] + (ll) t[i]) % mod;
            }
        }
        return (ll)(temp[0]<<30) + temp[1];
    }
};
const int RollingHash::basemod[]= {1007, 1000000021};
