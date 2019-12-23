template<int SZ = 26>
struct Trie{
    struct Node{
        Node *next[SZ];
        Node(){
            for(int i = 0; i < SZ; i++){
                next[i] = nullptr;
            }
        }
    };
    using NP = Node*;
    NP root;
    Trie(){
        root = new Node();
    }
    void add(const string &s){
        NP now = root;
        for(const char c : s){
            int i = c - 'a';//要変更
            if(!now -> next[i]){
                now -> next[i] = new Node();
            }
            now = now -> next[i];
        }
    }
    void query(NP *now){
        for(int i = 0; i < SZ; i++){
            if(now -> next[i]){
                query(now -> next[i]);
            }
        }
    }
};

