//最大ヒープ
//emplace実装したい(できるの?)
//TODO ヒープのmeldのverify
template<typename T>
struct SkewHeap{
    struct Node{
        using NP = Node*;
        NP l, r;
        T val;
        Node(T x) : l(nullptr), r(nullptr),val(x){}
        friend NP meld(NP a, NP b){
            if(!a) return b;
            if(!b) return a;
            if(a -> val < b -> val) swap(a, b);
//            if(a -> val > b -> val) swap(a, b);
            a->l = meld(a->l, b);
            swap(a->l, a->r);
            return a;
        }
    };
    using NP = Node*;
    NP root;
    int sz;
    SkewHeap():root(nullptr), sz(0){}
    void push(T x){
        sz++;
        NP temp = new Node(x);
        root = meld(root, temp);
    }
    T top(){
        return root -> val;
    }
    void pop(){
        sz--;
        NP temp = root;
        root = meld(root->r, root->l);
        delete temp;
    }
    friend SkewHeap* meld(SkewHeap *a, SkewHeap *b){
        SkewHeap *res = new SkewHeap();
        res -> sz = a -> sz + b -> sz;
        res -> root = meld(a -> root, b -> root);
        return res;
    }
};
