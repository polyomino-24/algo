//verifyいいえ
vector<Node> d;
vector<typename Node::T>lazy;
int sz;
void init(vector<Node::T> a){
    sz = 1;
    while(sz < a.size())sz *= 2;
    d.resize(2 * sz - 1);
    for(int i = 0; i < a.size(); i++){
        d[i + sz - 1] = Node(a[i], 1);
    }
    for(int i = sz - 2; i >= 0; i--){
        d[i] = d[2 * i + 1] + d[2 * i + 2];
    }
    lazy.resize(2 * sz - 1, typename Node::T(Node::INF));
}
void eval(int k, int l, int r){
    if(lazy[k] != Node::INF){
        d[k] = Node(lazy[k], r - l);
        if(r - l > 1){
            lazy[2 * k + 1] = lazy[2 * k + 2] = lazy[k];
        }
        lazy[k] = Node::INF;
    }
}
void update(const int a, const int b, const typename Node::T x, int k = 0, int l = 0, int r = -1){
    if(r < 0)r = sz;
    eval(k, l, r);
    if(a >= r || b <= l) {
        return;
    }
    if(a <= l && r <= b) {
        lazy[k] = x;
        eval(k, l, r);
        return;
    }
    update(a, b, x, 2 * k + 1, l, (l + r) / 2);
    update(a, b, x, 2 * k + 2, (l + r ) / 2, r);
    d[k] = d[2 * k + 1] + d[2 * k + 2];
}
Node query(const int a, const int b, int k = 0, int l = 0, int r = -1){
    if(r < 0)r = sz;
    eval(k, l, r);
    if(a >= r || b <= l) return Node();
    if(a <= l && r <= b) return d[k];
    return query(a, b, 2 * k + 1, l, (l + r) / 2) + query(a, b, 2 * k + 2, (l + r) / 2, r);
}
