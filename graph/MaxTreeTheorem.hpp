//行列木定理
//T:modintか有理数,g:隣接行列
template<typename T>
T MatrixTreeTheorem(const vector<vector<int>>& g){
    int n = (int) g.size();
    vector<vector<T>> D(n - 1, vector<T>(n - 1));
    for(int i = 0; i < n - 1; i++){
        for(int j : g[i]){
            if(j < n - 1){
                D[i][j] = -1;
            }
        }
    }
    for(int i = 0; i < n - 1; i++){
        D[i][i] = (T) g[i].size();
    }
    T res = det(D);
    return res;
}
