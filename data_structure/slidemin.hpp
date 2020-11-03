vector<int> slidemin(vector<int>a, int k){
    int n = (int) a.size();
    vector<int> res;
    res.reserve(n - k + 1);
    deque<int> dq;
    for(int i = 0; i < n; i++){
        while(!dq.empty() and a[dq.back()] >= a[i])dq.pop_back();
        dq.push_back(i);
        if(i >= k - 1){
            res.push_back(a[dq.front()]);
            if(dq.front() == i - k + 1)dq.pop_front();
        }
    }
    return res;
}
