struct TwoStack{
    using T = int;
    struct node{
        T val, sum;
        node(const T &val, const T &sum):val(val), sum(sum){}
    };
    T op(T l, T r){
        return min(l, r);
    }
    stack<node> front, back;
    T eval(){
//        assert(front.size() + back.size() > 0);
        if(!back.empty()){
            if(!front.empty()){
                return op(front.top().sum, back.top().sum);
            }else{
                return back.top().sum;
            }
        }else{
            return front.top().sum;
        }
    }
    void pop_front(){
//        assert(front.size() + back.size() > 0);
        if(front.empty()){
            front.emplace(back.top().val, back.top().val);
            back.pop();
            while(!back.empty()){
                front.emplace(back.top().val, op(back.top().val, front.top().sum));
                back.pop();
            }
        }
        front.pop();
    }
    void push_back(const T &val){
        if(!back.empty()){
            back.emplace(val, op(back.top().sum, val));
        }else{
            back.emplace(val, val);
        }
    }
};
