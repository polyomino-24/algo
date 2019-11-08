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
struct edge{
    int to, cost;
    edge(int a = 0, int b = 0) : to(a), cost(b) {}
};
class UnionFind {
private:
    int sz;
    vector<int> par, size_;
public:
    UnionFind(){}
    UnionFind(int node_size) : sz(node_size), par(sz), size_(sz, 1){
        iota(par.begin(), par.end(), 0);
    }
    int find(int x){
        if(par[x] == x) return x;
        else return par[x] = find(par[x]);
    }
    void unite(int x,int y){
        x = find(x), y = find(y);
        if(x == y) return;
        if(size_[x] < size_[y]) swap(x,y);
        par[y] = x;
        size_[x] += size_[y];
    }
    int size(int x){
        x = find(x);
        return size_[x];
    }
    bool same(int x,int y){
        return find(x) == find(y);
    }
};
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<edge>> g(n);
    vector<vector<int>>a(n, vector<int>(n));
    vector<vector<ll>>dist(n, vector<ll>(n,1LL<<60));
    rep(i,n)rep(j,n){
        cin >> a[i][j];
        if(a[i][j] > 0){
            g[i].emplace_back(j, a[i][j]);
        }
        if(a[i][j] != -1)dist[i][j] = a[i][j];
    }
    rep(k,n)rep(i,n)rep(j,n)dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for(int s = 0; s < n; s++){
        ll ans = 1LL<<60;
        const auto &dist2 = dist[s];
        vector<bool>used(n);
        vector<vector<bool>> st(n, vector<bool>(n));
        UnionFind uf(n);
        for(int i = 0; i < n; i++){
            for(auto x : g[i]){
                if(dist2[x.to] == dist2[i] + x.cost){
                    if(used[x.to])continue;
                    st[i][x.to] = st[x.to][i] = true;
                    if(i != s){
                        uf.unite(i, x.to);
                    }
                    used[x.to] = true;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(auto x : g[i]){
                if(st[i][x.to])continue;
                if(!uf.same(i, x.to)){
                    ans = min(ans, dist2[i] + dist2[x.to] + x.cost);
                }
            }
        }
        if(ans == 1LL<<60)ans = -1;
        cout << ans << "\n";
    }
}
