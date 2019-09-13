struct Treap{
    struct Node{
        int key;
        int priority;
        Node *l, *r;
        Node(){}
        Node(int _key, int _priority) : key(_key), priority(_priority), l(nullptr), r(nullptr){}
    };
    using NP = Node*;
    NP merge(NP l, NP r){
        if(!l) return r;
        if(!r) return l;
        if(l -> priority > r -> priority){
            l ->r = merge(l -> r, r);
            return l;
        }else{
            r -> l = merge(l, r -> l);
            return r;
        }
    }
    //key未満,key以上に分割
    pair<NP, NP> split(NP t, int key){
        if(!t) return make_pair(nullptr, nullptr);
        if(key < t -> key){
            auto s = split(t -> l, key);
            t -> l = s.second;
            return make_pair(s.first, t);
        }else{
            auto s = split(t -> r, key);
            t -> r = s.first;
            return make_pair(t, s.second);
        }
    }
    void insert(NP &t, NP a){
        if(!t){
            t = a;
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
    }
    void erase(NP &t, int key){
        if(!t) return;
        if(t -> key == key){
            t = merge(t -> l, t -> r);
        }else if(key < t -> key){
            erase(t -> l, key);
        }else{
            erase(t -> r, key);
        }
    }
    bool find(NP t, int key){
        if(!t) return false;
        if(t -> key == key){
            return true;
        }else if(key < t -> key){
            return find(t -> l, key);
        }else{
            return find(t -> r, key);
        }
    }
    NP root;
    Treap():root(nullptr){}
    void insert(int key){
        insert(root, new Node(key,rand()));
    }
    void erase(int key){
        erase(root,key);
    }
    bool find(int key){
        return find(root, key);
    }
};
