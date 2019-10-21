struct edge{
    int to, cost;
    edge(int a = 0, int b = 0) : to(a), cost(b) {}
};
vector<ll> dijkstra(const int s, const vector<vector<edge>> &g){
    const int n = (int) g.size();
    vector<ll> dist(n, 1LL<<60);
    vector<bool> used(n);
    dist[s] = 0;
    list<int> q;
    for(int i = 0; i < n; i++){
        q.push_back(i);
    }
    while(1){
        int v = -1;
        list<int>::iterator memo;
        for(auto itr = q.begin(); itr != q.end(); ++itr){
            int x = *itr;
            if(!used[x] and (v == -1 or dist[x] < dist[v])){
                v = x;
                memo = itr;
            }
        }
        if(v == -1)break;
        used[v] = true;
        q.erase(memo);
        for(const auto &x : g[v]){
            dist[x.to] = min(dist[x.to], dist[v] + x.cost);
        }
    }
    return dist;
}
vector<ll> dijkstra2(const int s, const vector<vector<edge>> &g){
    int n = (int) g.size();
    vector<ll> dist(n, 1LL<<60);
    vector<bool> used(n);
    dist[s] = 0;
    while(1){
        int v = -1;
        for(int i = 0; i < n; i++){
            if(!used[i] and (v == -1 or dist[i] < dist[v])){
                v = i;
            }
        }
        if(v == -1)break;
        used[v] = true;
        for(const auto &x : g[v]){
            dist[x.to] = min(dist[x.to], dist[v] + x.cost);
        }
    }
    return dist;
}
