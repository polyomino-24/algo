// V<= 40
//dp[i] = i (\subseteq S1)による誘導部分グラフのMIS
//f[i] =  S1からi (\in S2)につながっている頂点を削除した集合
template<typename T = int>
vector<int> MaximumIndependentSet(const vector<vector<int>> &g, vector<T>cost = {}){
    const int n = (int) g.size();
    if(cost.size() == 0) cost = vector<T>(n, 1);
    assert(cost.size() == n);
    const int half = n / 2, half2 = n - n / 2;
    vector<T> dp(1 << half2), dp2(1 << half2);
    vector<long long> bit(n);
    for(int i = 0; i < n; i++){
        bit[i] = 1LL << i;
        for(int x : g[i]){
            bit[i] |= 1LL << x;
        }
    }
    vector<int> f(1 << half2);
    f[0] = (1 << half) - 1;
    for(int i = 1; i < 1 << half2; i++){
        for(int j = 0; j < half2; j++){
            if(!(i >> j & 1))continue;
            dp[i] = max(dp[i], dp[i & (~bit[j])] + cost[j]);
            dp2[i] = max(dp2[i], dp2[i & ((~bit[j + half]) >> half)] + cost[j + half]);
        }
        int j = __builtin_ctz(i);
        f[i] = f[i ^ (1 << j)] & (~bit[j + half]);
    }
    T res = 0;
    int id = -1;
    for(int i = 0; i < 1 << half2; i++){
        if(res < dp2[i] + dp[f[i]]){
            res = dp2[i] + dp[f[i]];
            id = i;
        }
    }
//    return res;
    int id2 = -1;
    for(int i = 0; i < 1 << half2; i++){
        if((i|(f[id])) == f[id] and dp[i] == dp[f[id]]){
            id2 = i;
            break;
        }
    }
    vector<int> p;
    for(int i = 0; i < half2; i++){
        if(id >> i & 1){
            p.push_back(i + half);
        }
        if(id2 >> i & 1){
            p.push_back(i);
        }
    }
    assert(res == int(p.size()));
    return p;
}
