//T:誤差なしで計算できる型を想定(基本的にmodint)
template<typename T>
T det(vector<vector<T>> &a){
    int n = (int) a.size();
    if(n == 0){
        return 0;
    }
    assert(a.size() == a[0].size());
    T res = 1;
    for(int j = 0; j < n; j++){
        int pivot = -1;
        for(int i = j; i < n; i++){
            if(a[i][j] != 0){
                pivot = i;
            }
        }
        if(pivot == -1){
            return 0;
        }
        if(pivot != j)res = - res;
        swap(a[pivot], a[j]);
        res *= a[j][j];
        for(int i = j + 1; i < n; i++){
            const T coeff = a[i][j] / a[j][j];
            for(int k = j; k < n; k++){
                a[i][k] -= a[j][k] * coeff;
            }
        }
    }
    return res;
}
