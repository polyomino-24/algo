struct edge{
    int to, cost;
    edge(int a = 0, int b = 0) : to(a), cost(b) {}
};
vector<ll> dijkstra(int s, vector<vector<edge>> &g){
    int n = (int)g.size();
    vector<ll> dist(n, 1LL<<60);
    using ll_i = pair<ll, int>;
    priority_queue<ll_i,vector<ll_i>,greater<ll_i>>pq;
    dist[s] = 0;
    pq.push({dist[s], s});
    while(!pq.empty()){
        auto a = pq.top();
        pq.pop();
        int v = a.second;
        if(a.first > dist[v])continue;
        for(auto &x:g[v]){
            if(dist[x.to] > dist[v] + x.cost){
                dist[x.to] = dist[v] + x.cost;
                pq.push({dist[x.to], x.to});
            }
        }
    }
    return dist;
}
