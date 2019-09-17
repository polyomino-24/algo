int gauss(vector<vector<mint>>&a){
    int n = (int) a.size();
    int m = (int) a[0].size();
    int res = 0;
    for(int i = 0; i < m; i++){
        if(res == n)break;
        for(int j = res + 1; j < n; j++){
            if(a[j][i] and !a[res][i]){
                swap(a[j],a[res]);
                break;
            }
        }
        if(!a[res][i])continue;
        mint inv = mint(1) / a[res][i];
        for(int j = i; j < m; j++){
            a[res][j] *= inv;
        }
        for(int j = res + 1; j < n; j++){
            mint coef = a[j][i];
            for(int k = i; k < m; k++){
                a[j][k] -= coef * a[res][k];
            }
        }
        res++;
    }
    return res;
}
vector<vector<mint>>a;
void add_edge(int i,int j){
    if(i > j)swap(a[i],a[j]);
    a[i][j] = -(a[j][i] = rand()%(MOD-1)+1);
}
