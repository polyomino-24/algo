//ax+by=gcd(a,b)を満たすx,yを求め、gcd(a,b)を返す
//(a/b*b+a%b)x+by=gcd(a,b)=gcd(b,a%b)
//b(a/b*x+y)+(a%b)x=gcd(b,a%b)
//https://qiita.com/drken/items/b97ff231e43bce50199a
template<typename T>
T ext_gcd(const T a, T b, T &x, T &y){
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

