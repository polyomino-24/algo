template<typename T>
struct BIT{
    const int n;
    vector<T> dat;
    BIT(){}
    BIT(int N) : n(N + 1), dat(n, T()){}
    BIT(const vector<T> & a) : n((int) a.size() + 1), dat(n, T(0)){
        for(int i = 0; i < n - 1; i++){
            add(i, a[i]);
        }
    }
    //0-index
    void add(int i, T x){
        i++;
        while(i < n){
            dat[i] += x;
            i += i & - i;
        }
    }
    //0-index [0,i]
    T sum(int i){
        i++;
        T res = 0;
        while(i > 0){
            res += dat[i];
            i -= i & - i;
        }
        return res;
    }
    //min index i s.t. a[0] + ... + a[i] >= x
    //if there is no i, return n
    //assume a[k] >= 0
    //TODO:verify
    int lower_bound(T x){
        int res = 0;
        int h = 31 - __builtin_clz(n);
        for(int i = h; i >= 0; i--){
            if(res + (1 << i) < n and dat[res + (1 << i)] < x){
                x -= dat[res + (1 << i)];
                res += 1 << i;
            }
        }
        return res;
    }
};
