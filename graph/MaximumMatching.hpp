struct Matching{
    using uint = unsigned int;
    using ull = unsigned long long;
    int n;
    const int v;
    vector<vector<uint>> adj;
    vector<int>id;
    vector<bool>row, col;
    vector<int>match;
    vector<vector<uint>> a, b;
    vector<pair<int,int>>ans;
    static constexpr uint MOD = 1e9+7;
    uint mod_inv(uint a){
        uint res = 1;
        uint exponent = MOD - 2;
        while(exponent){
            if(exponent & 1){
                res = (ull) res * a % MOD;
            }
            a = (ull) a * a % MOD;
            exponent >>= 1;
        }
        return res;
    }
    Matching(const vector<vector<int>> &g): v((int)g.size()),adj(v, vector<uint>(v,0)),id(v),row(v,false),col(v,false),match(v,-1){
        random_device seed;
        mt19937 random_engine(seed());
        uniform_int_distribution<> rand_val(1, MOD - 1);
        for(int i = 0; i < v; i++){
            for(int j : g[i]){
                if(i < j){
                    adj[i][j] = rand_val(random_engine);
                    adj[j][i] = MOD - adj[i][j];
                }
            }
        }
        n = v;
        a = adj;
        iota(id.begin(), id.end(), 0);
        gauss(false);
        vector<int> temp(n, -1);
        n = 0;
        for(int i = 0; i < v; i++){
            if(a[id[i]][id[i]]){
                temp[n++] = i;
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = adj[temp[i]][temp[j]];
            }
        }
        b.resize(n, vector<uint>(n, 0));
        for(int i = 0; i < n; i++){
            b[i][i] = 1;
        }
        gauss(true);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = adj[temp[i]][temp[j]];
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(match[temp[i]] >= 0 or match[temp[j]] >=0)continue;
                if(a[i][j] and b[j][i]){
                    eliminate(i, j);
                    eliminate(j, i);
                    match[temp[i]] = temp[j];
                    match[temp[j]] = temp[i];
                    ans.push_back({temp[i], temp[j]});
                }
            }
        }
    }
    void gauss(bool flag){
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                if(a[j][i]){
                    swap(id[i], id[j]);
                    swap(a[i], a[j]);
                    if(flag)swap(b[i], b[j]);
                    break;
                }
            }
            if(!a[i][i]) continue;
            const uint inv = mod_inv(a[i][i]);
            for(int j = 0; j < n; j++){
                if(j != i and a[j][i]){
                    const uint t = (ull)a[j][i] * inv % MOD;
                    for(int k = i; k < n; k++){
                        a[j][k] = (a[j][k] + MOD - (ull) t * a[i][k] % MOD) % MOD;
                    }
                    if(flag)for(int k = 0; k < n; k++){
                        if(b[i][k]) b[j][k] = (b[j][k] + MOD - (ull) t * b[i][k] % MOD) % MOD;
                    }
                }
            }
        }
        if(flag){
            for(int i = 0; i < n; i++){
                const uint t = mod_inv(a[i][i]) % MOD;
                for(int j = 0; j < n; j++){
                    b[i][j] = (ull) b[i][j] * t % MOD;
                }
            }
        }
    }
    void eliminate(int x, int y){
        row[x] = col[y] = true;
        const uint inv = mod_inv(b[x][y]);
        for(int i = 0; i < n; i++){
            if(row[i])continue;
            const uint t = (ull)b[i][y] * inv % MOD;
            for(int j = 0; j < n; j++){
                if(!col[j]){
                    b[i][j] = (b[i][j] + MOD - (ull) b[x][j] * t % MOD) % MOD;
                }
            }
        }
    }
};
