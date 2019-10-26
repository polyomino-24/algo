//かなり遅い。int medofmed = a[rand()%a.size()];とするとだいぶ速くなるが、std::nth_element(begin,nth,last)を使ったほうが速い
int Find_median(vector<int>a){
    assert(a.size()<=5);
    sort(a.begin(),a.end());
    return a[a.size()/2];
}
//T(n) = T(n/5) + T(7n/10) + O(n)
//!!kが1-indexなことに注意!!
int kth_smallest(vector<int>&a, int l, int r, int k){
    if(k <= 0 or r - l < k)return INT_MAX;
    vector<int>med;
    for(int i = l; i < r;){
        vector<int>temp;
        for(int j = 0; j < 5; j++){
            if(i < r) temp.push_back(a[i++]);
        }
        med.push_back(Find_median(temp));
    }
    int medofmed = (med.size() == 1) ? med[0] :  kth_smallest(med, 0, (int) med.size(), (int) med.size() / 2);
    vector<int> b,c,d;
    for (int i = l; i < r; i++){
        if(a[i] < medofmed){
            b.push_back(a[i]);
        }else if(a[i] == medofmed){
            c.push_back(a[i]);
        }else{
            d.push_back(a[i]);
        }
    }
    if(b.size() >= k){
        return kth_smallest(b, 0, (int) b.size(), k);
    }else if(b.size() + c.size() >= k){
        return medofmed;
    }else{
        return kth_smallest(d, 0, (int) d.size(), k - (int) b.size() - (int) c.size());
    }
    return INT_MAX;
}
