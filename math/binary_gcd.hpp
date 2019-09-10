//binary gcd
ll gcd(ll a, ll b){
    if(!a)return b;
    if(!b)return a;
    const int shift = __builtin_ctzll(a|b);
    a >>= __builtin_ctzll(a);
    do{
        b >>= __builtin_ctzll(b);
        if(a > b)swap(a, b);
        b -= a;
    }while(b);
    return a << shift;
}
