//Range add, Range sum
template<typename T>
struct SegmentTree{
    int n;
    vector<T> node;
    vector<T> lazy;
    const T id = 0;
    SegmentTree(const vector<T>&d){
        n = 1;
        while(d.size() > n)n *= 2;
        node.resize(2 * n - 1, id);
        lazy.resize(2 * n - 1, id);
        for(int i = 0; i < d.size(); i++){
            node[i + n - 1] = d[i];
        }
        for(int i = n - 2; i >= 0; i--){
            node[i] = node[2 * i + 1] + node[2 * i + 2];
        }
    }
    SegmentTree(int sz){
        n = 1;
        while(n < sz)n *= 2;
        node.resize(2 * n - 1, id);
        lazy.resize(2 * n - 1, id);
    }
    void eval(int k,int l, int r){
        if(lazy[k] != 0){
            node[k] += lazy[k];
            if(r - l > 1){
                lazy[2 * k + 1] += lazy[k] / 2;
                lazy[2 * k + 2] += lazy[k] / 2;
            }
            lazy[k] = 0;
        }
    }
    void add(const int a,const int b,const T x, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        eval(k, l, r);
        if(r <= a or b <= l) return;
        if(a <= l and r <= b){
            lazy[k] += x * (r - l);
            eval(k, l, r);
        }else{
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = node[2 * k + 1] + node[2 * k + 2];
        }
    }
    T query(const int a,const int b,int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        if(r <= a or b <= l){
            return id;
        }
        eval(k, l, r);
        if(a <= l and r <= b){
            return node[k];
        }else{
            T lv = query(a, b, 2 * k + 1, l, (l + r) / 2);
            T rv = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return lv + rv;
        }
    }
};
