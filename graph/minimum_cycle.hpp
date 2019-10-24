//単純重みなしグラフのsを含むような最小サイクルの長さ
int minimum_cycle_length(const int s, const vector<vector<int>> &g){
    int ans = 1<<30;
    int n = (int) g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while(q.size()){
        int x = q.front();
        q.pop();
        for(int v : g[x]){
            if(dist[v] == -1){
                dist[v] = dist[x] + 1;
                q.push(v);
            }else if(dist[v] >= dist[x]){
                ans = min(ans, dist[v] + dist[x] + 1);
            }
            
        }
    }
    return ans;
}

//a:隣接行列(重みありもok),無向グラフ
ll minimum_cycle_length(const vector<vector<int>>&a){
    int n = (int) a.size();
    vector<vector<ll>> dist(n, vector<ll>(n, 1LL<<60));
    rep(i,n){
        rep(j,n){
            if(a[i][j] != -1)dist[i][j] = a[i][j];
        }
    }
    ll ans = 1LL<<60;
    for(int k = 0; k < n; k++){
        for(int i = 0; i < k; i++){
            for(int j = i + 1; j < k; j++){
                if(a[i][k] != -1 and a[j][k] != -1){
                    ans = min(ans, a[i][k] + a[j][k] + dist[i][j]);
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return ans;
}
//重みありの時：WFして(a,b)が最短経路木の辺でないかつlca(a,b)!=sとき計算する
//https://codeforces.com/gym/100917/problem/F
