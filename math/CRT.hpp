//ax+by=gcd(a,b)を満たすx,yを求め、gcd(a,b)を返す
//(a/b*b+a%b)x+by=gcd(a,b)=gcd(b,a%b)
//b(a/b*x+y)+(a%b)x=gcd(b,a%b)
//https://qiita.com/drken/items/b97ff231e43bce50199a
template<typename T>
T ext_gcd(T a, T b, T &x, T &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }else{
        T g = ext_gcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
//x=v_i(mod m_i)を満たすx=r(mod m=lcm(m_1,m_2))を求める
//m_iが互いに素な必要なし
template<typename T>
pair<T, T> CRT(T v1, T m1, T v2, T m2){
    T a, b;
    T g = ext_gcd(m1, m2, a, b);
    if(v1 % g != v2 % g){
        return make_pair(-1, -1);//存在しない
    }
    T m = m1 / g * m2;
    T temp = (v2 - v1) / g * a % (m2 / g);
    T r = ((v1 + temp * m1) % m + m) % m;
    return make_pair(r, m);
}
