struct Node{
    using Type = int;
    Type val;
    static const Type id = numeric_limits<Type>::max();
    Node(Type v = id):val(v){}
    friend Node merge(const Node &a, const Node &b){
        return Node(min(a.val, b.val));
    }
};
template<class Node>
struct SegmentTree{
    int n;
    vector<Node> seg;
    using T = typename Node::Type;
    SegmentTree(const vector<Node>&d){
        n = 1;
        while(d.size() > n)n *= 2;
        seg.resize(2 * n - 1, Node::id);
        for(int i = 0; i < d.size(); i++){
            seg[i + n - 1] = d[i];
        }
        for(int i = n - 2; i >= 0; i--){
            seg[i] = merge(seg[2 * i + 1], seg[2 * i + 2]);
        }
    }
    SegmentTree(int sz){
        n = 1;
        while(n < sz)n *= 2;
        seg.resize(2 * n - 1, Node::id);
    }
    void update(int x, T k){
        x += n - 1;
        seg[x] = Node(k);
        while(x){
            x = (x - 1) / 2;
            seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
        }
    }
    Node query(const int a, const int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a or b <= l){
            return Node();
        }
        if(a <= l and r <= b){
            return seg[k];
        }else{
            return merge(query(a, b, 2 * k + 1, l, (l + r) / 2), query(a, b, 2 * k + 2, (l + r) / 2, r));
        }
    }
};
