class Manacher{
public:
    static vector<int> solve(const string& s){
        int n = (int) s.size();
        vector<int>d(n);
        for(int i = 0, l = 0, r = -1; i < n; i++){
            int k = i > r ? 1 : min(d[l + r - i], r - i + 1);
            while(i - k >= 0 and i + k < n and s[i - k] == s[i + k])k++;
            d[i] = k--;
            if(i + k > r){
                r = i + k;
                l = i - k;
            }
        }
        return d;
    }
    static vector<int> solve_even(const string& s){
        int n = (int) s.size();
        vector<int>d(n);
        for(int i = 0, l = 0, r = -1; i < n; i++){
            int k = i > r ? 0 : min(d[l + r - i + 1], r - i + 1);
            while(i - k - 1 >= 0 and i + k < n and s[i - k - 1] == s[i + k])k++;
            d[i] = k--;
            if(i + k > r){
                r = i + k;
                l = i - k - 1;
            }
        }
        return d;
    }
};

int longest_palindrome(const string &s){
    string t;
    t += '#';
    for(char c : s){
        t += c;
        t += '#';
    }
    auto d = manacher(t);
    /*
       https://cses.fi/problemset/task/1111/
    int id = (int)(max_element(d.begin(), d.end()) - d.begin());
    int len = d[id] - 1;
    return s.substr(id/2-len/2,len);
    */
    return *max_element(d.begin(), d.end()) - 1;
}
