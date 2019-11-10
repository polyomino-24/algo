template<typename T>
class SegmentTree{
public:
    int n;
    vector<T> node;
    const T id = numeric_limits<T>::max();
    SegmentTree(const vector<T>&d){
        n = 1;
        while(d.size() > n)n *= 2;
        node.resize(2 * n - 1, id);
        for(int i = 0; i < d.size(); i++){
            node[i + n - 1] = d[i];
        }
        for(int i = n - 2; i >= 0; i--){
            node[i] = min(node[2 * i + 1], node[2 * i + 2]);
        }
    }
    SegmentTree(int sz){
        n = 1;
        while(n < sz)n *= 2;
        node.resize(2 * n - 1, id);
    }
    void update(int x, T k){
        x += n - 1;
        node[x] = k;
        while(x){
            x = (x - 1) / 2;
            node[x] = min(node[2 * x + 1], node[2 * x + 2]);
        }
    }
    T query(const int a, const int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a or b <= l){
            return id;
        }
        if(a <= l and r <= b){
            return node[k];
        }else{
            T lv = query(a, b, 2 * k + 1, l, (l + r) / 2);
            T rv = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return min(lv, rv);
        }
    }
};
