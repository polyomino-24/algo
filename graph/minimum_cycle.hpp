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