class UnionFind {
private:
    int n;
    vector<int> par;
    vector<int> rank;
    
public:
    UnionFind(int sz) : n(sz), par(sz), rank(sz) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (x == par[x])
            return x;
        else
            return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
class LCA {
    int n;
    UnionFind uf;
    vector<vector<int>> g;
    vector<vector<pair<int, int>>> query;
    vector<int> ancestor;
    vector<bool> used;
    vector<int> ans;
    void dfs(int s, int p) {
        ancestor[s] = s;
        for (int x : g[s]) {
            if (x == p) continue;
            dfs(x, s);
            uf.unite(s, x);
            ancestor[uf.find(s)] = s;
        }
        used[s] = true;
        for (auto &x : query[s]) {
            if (used[x.first]) {
                ans[x.second] = ancestor[uf.find(x.first)];
            }
        }
    }
    
public:
    LCA(vector<vector<int>> g, vector<vector<pair<int, int>>> query, int root,
        int query_size)
    : n((int)g.size()),
    uf(n),
    g(g),
    query(query),
    ancestor(n, -1),
    used(n, false),
    ans(query_size) {
        dfs(root, -1);
    }
    int solve(int id) {
        return ans[id];
    }
};
