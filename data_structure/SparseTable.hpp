template <typename T>
class SparseTable {
    const int n, h;
    vector<vector<T>> t;
public:
    SparseTable(const vector<T>& a)
    : n((int)a.size()), h(31 - __builtin_clz(n)), t(h + 1, vector<T>(a.size())) {
        t[0] = a;
        for (int i = 0; i < h; i++){
            for (int j = 0; j + (1 << i) < n; j++){
                t[i + 1][j] = min(t[i][j], t[i][j + (1 << i)]);
            }
        }
    }
    T find(int l, int r) {
        int lg = 31 - __builtin_clz(r - l);
        return min(t[lg][l], t[lg][r - (1 << lg)]);
    }
};
