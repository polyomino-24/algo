#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <list>
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
//#define cerr if(false) cerr
#ifdef DEBUG
#define show(...) cerr << #__VA_ARGS__ << " = ", debug(__VA_ARGS__);
#else
#define show(...) 42
#endif
using namespace std;
using ll = long long;
using pii = pair<int, int>;
template <typename T, typename S>
ostream& operator<<(ostream& os, pair<T, S> a) {
    os << '(' << a.first << ',' << a.second << ')';
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (auto x : v) os << x << ' ';
    return os;
}
void debug() {
    cerr << '\n';
}
template <typename H, typename... T>
void debug(H a, T... b) {
    cerr << a;
    if (sizeof...(b)) cerr << ", ";
    debug(b...);
}


/*
O(log^3N) per Query
   */
vector<vector<int>> seg;
int n;
int sz;
vector<int> a;
vector<int> sorted;
vector<int> node_id;

void build(){
    n = (int) a.size();
    sorted = a;
    sort(sorted.begin(), sorted.end());
    sz = 1;
    while(sz < n)sz *= 2;
    seg.resize(2 * sz - 1);
    for(int i = 0; i < n; i++){
        seg[i + sz - 1].push_back(a[i]);
    }
    for(int i = sz - 2; i >= 0; i--){
        merge(seg[2 * i + 1].begin(), seg[2 * i + 1].end(), seg[2 * i + 2].begin(), seg[2 * i + 2].end(), back_inserter(seg[i]));
    }
}

void calc(const int a, const int b, int k = 0, int l = 0, int r = sz){
    if(r <= a or b <= l){
        return;
    }
    if(a <= l and r <= b){
        node_id.push_back(k);
    }else{
        calc(a, b, 2 * k + 1, l, (l + r) / 2);
        calc(a, b, 2 * k + 2, (l + r) / 2, r);
    }
}

int query(const int l, const int r, const int k){
    node_id.clear();
    calc(l, r);
    int low = 0;
    int high = n - 1;
    auto cnt = [&](int e){
        int r = 0;
        for(int id : node_id){
            r +=  (int)(upper_bound(seg[id].begin(), seg[id].end(), e) - seg[id].begin());
        }
        return r;
    };
    if(cnt(sorted[0]) == k){
        return sorted[0];
    }
    while(high - low > 1){
        int mid = (low + high) / 2;
        int e = sorted[mid];
        int r = cnt(e);
        if(r < k){
            low = mid;
        }else{
            high = mid;
        }
    }
    return sorted[high];
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    build();
    while(q--){
        int l, r, k;
        cin >> l >> r >> k;
        cout << query(l, r, k + 1) << "\n";
    }
}


/*
O(log^2N) per query
セグ木の最下層をソート列の逆元として、マージセグ木をする。
queryは[l,r)にあるものが何個かを調べると左右どちらに進めばいいかわかる

   */
vector<vector<int>> seg;
int n;
int sz;
vector<int> a;
vector<pair<int,int>> sorted;

void build(){
    n = (int) a.size();
    for(int i = 0; i < n; i++){
        sorted.emplace_back(a[i], i);
    }
    sort(sorted.begin(), sorted.end());
    sz = 1;
    while(sz < n)sz *= 2;
    seg.resize(2 * sz - 1);
    for(int i = 0; i < n; i++){
        seg[i + sz - 1].push_back(sorted[i].second);
    }
    for(int i = sz - 2; i >= 0; i--){
        merge(seg[2 * i + 1].begin(), seg[2 * i + 1].end(), seg[2 * i + 2].begin(), seg[2 * i + 2].end(), back_inserter(seg[i]));
    }
}
int calc(const int l, const int r, int k, int id = 0){
    while(id < sz - 1){
        int num = (int)(lower_bound(seg[2 * id + 1].begin(), seg[2 * id + 1].end(), r) - lower_bound(seg[2 * id + 1].begin(), seg[2 * id + 1].end(), l));
        if(num >= k){
            id = 2 * id + 1;
        }else{
            id = 2 * id + 2;
            k = k - num;
        }
    }
    return seg[id][0];
}
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    build();
    while(q--){
        int l, r, k;
        cin >> l >> r >> k;
        int id = calc(l, r, k + 1);
        cout << a[id] << "\n";
    }
}

