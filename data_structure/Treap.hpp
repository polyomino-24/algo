template<typename T>
struct Treap{
    struct Node{
        T key;
        int priority;
        Node *l, *r;
        int cnt;
        Node(){}
        Node(T _key, int _priority) : key(_key), priority(_priority), l(nullptr), r(nullptr),cnt(1){}
    };
    using NP = Node*;
    int cnt(NP t){
        if(!t) return 0;
        else return t -> cnt;
    }
    void update_cnt(NP t){
        if(!t) return;
        t -> cnt = 1 + cnt(t -> l) + cnt(t -> r);
    }
    NP merge(NP l, NP r){
        if(!l) return r;
        if(!r) return l;
        if(l -> priority > r -> priority){
            l ->r = merge(l -> r, r);
            update_cnt(l);
            return l;
        }else{
            r -> l = merge(l, r -> l);
            update_cnt(r);
            return r;
        }
    }
    //key未満,key以上に分割
    pair<NP, NP> split(NP t, T key){
        if(!t) return make_pair(nullptr, nullptr);
        if(key < t -> key){
            auto s = split(t -> l, key);
            t -> l = s.second;
            update_cnt(t);
            return make_pair(s.first, t);
        }else{
            auto s = split(t -> r, key);
            t -> r = s.first;
            update_cnt(t);
            return make_pair(t, s.second);
        }
    }
    void insert(NP &t, NP a){
        if(!t){
            t = a;
            update_cnt(t);
            return;
        }
        if(a -> priority > t -> priority){
            tie(a -> l, a -> r) = split(t, a -> key);
            t = a;
        }else{
            if(a -> key < t -> key){
                insert(t -> l, a);
            }else{
                insert(t -> r, a);
            }
        }
        update_cnt(t);
    }
    void erase(NP &t, T key){
        if(!t) return;
        if(t -> key == key){
            t = merge(t -> l, t -> r);
        }else if(key < t -> key){
            erase(t -> l, key);
        }else{
            erase(t -> r, key);
        }
        update_cnt(t);
    }
    bool find(NP t, T key){
        if(!t) return false;
        if(t -> key == key){
            return true;
        }else if(key < t -> key){
            return find(t -> l, key);
        }else{
            return find(t -> r, key);
        }
    }
    //0-index
    T kth_element(NP t, int k){
        int sz = cnt(t -> l);
        if(sz == k){
            return t -> key;
        }else if(sz > k){
            return kth_element(t -> l, k);
        }else{
            return kth_element(t -> r, k - sz - 1);
        }
    }
    NP root;
    Treap():root(nullptr){}
    int size(){
        return cnt(root);
    }
    void insert(T key){
        insert(root, new Node(key,rand()));
    }
    void erase(T key){
        erase(root,key);
    }
    bool find(T key){
        return find(root, key);
    }
    T kth_element(int k){
        // assert(k < size());
        return kth_element(root, k);
    }
};
