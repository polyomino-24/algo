vector<int> manacher(const string& s){
    int n = (int) s.size();
    vector<int> res(n);
    for(int i = 0, j = 0; i < n;){
        while(i - j >= 0 and i + j < n and s[i - j] == s[i + j])j++;
        res[i] = j;
        int k = 1;
        while(i - k >= 0 and i + k < n and k + res[i - k] < j){
            res[i + k] = res[i - k];
            k++;
        }
        i += k;
        j -= k;
    }
    return res;
}
int longest_palindrome(const string &s){
    string t;
    t += '#';
    for(char c : s){
        t += c;
        t += '#';
    }
    auto d = manacher(t);
    /*
    int id = (int)(max_element(d.begin(), d.end()) - d.begin());
    int len = d[id] - 1;
    return s.substr(id/2-len/2,len);
    */
    return *max_element(d.begin(), d.end()) - 1;
}
