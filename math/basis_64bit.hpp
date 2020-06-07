vector<ll> basis(const vector<ll>& a){
    vector<ll> basis;
    for(auto x : a){
        ll k = x;
        for(auto y : basis){
            k = min(k, k ^ y);
        }
        if(k){
            basis.push_back(k);
        }
    }
    return basis;
}
