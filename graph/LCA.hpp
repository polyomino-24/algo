//lgを計算し直す感じでやると少しだけ(ランダムケースで)早くなるけどどうなんだろう
struct LCA{
    int n;
    int root;
    int lg;
    vector<vector<int>> g;
    vector<int>parent;
    vector<int> depth;
    vector<vector<int>> dp;
    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void dfs(int s, int p, int d){
        depth[s] = d;
        parent[s] = p;
        for(int x : g[s]){
            if(x == p)continue;
            dfs(x, s, d + 1);
        }
    }
    LCA(int N, int root = 0):n(N),g(n),parent(n),depth(n),root(root),lg(31 - __builtin_clz(n)),dp(lg + 1,vector<int>(n)){
    }
    void cal(){
        parent[root] = root;
        dfs(root, root, 0);
        dp[0] = parent;
        for(int i = 1; i <= lg; i++){
            for(int j = 0; j < n; j++){
                dp[i][j] = dp[i-1][dp[i-1][j]];
            }
        }
    }
    int up(int a, int num){
        if(!num)return a;
        int h = 31 - __builtin_clz(num);
        for(int i = h; i >= 0 and num > 0; i--){
            if(num & (1 << i)){
                a = dp[i][a];
                num ^= 1 << i;
            }
        }
        return a;
    }
    int lca(int a, int b){
        if(depth[a] > depth[b])swap(a,b);
        b = up(b, depth[b] - depth[a]);
        if(a == b)return a;
        int h = 31 - __builtin_clz(depth[a]);
        for(int i = h; i >= 0; i--){
            if(dp[i][a] != dp[i][b]){
                a = dp[i][a];
                b = dp[i][b];
            }
        }
        return parent[a];
    }
    int dist(int a, int b){
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};
