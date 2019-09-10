//負の数を掛けたりするとバグる
template<int MOD>
class Modint{
public:
    int a;
    Modint(const long long v = 0):a(v % MOD){}
    int getmod() const{
        return MOD;
    }
    Modint operator+(const Modint rhs) const{
        return Modint(*this) += rhs;
    }
    Modint operator-(const Modint rhs) const{
        return Modint(*this) -= rhs;
    }
    Modint operator*(const Modint rhs) const{
        return Modint(*this) *= rhs;
    }
    Modint operator/(const Modint rhs) const{
        return Modint(*this) /= rhs;
    }
    Modint operator+(const long long rhs) const{
        return Modint(*this) += rhs;
    }
    Modint operator-(const long long rhs) const{
        return Modint(*this) -= rhs;
    }
    Modint operator*(const long long rhs) const{
        return Modint(*this) *= rhs;
    }
    Modint operator/(const long long rhs) const{
        return Modint(*this) /= rhs;
    }
    friend Modint operator+(const long long a, const Modint b){
        return b + a;
    }
    friend Modint operator-(const long long a, const Modint b){
        return -b + a;
    }
    friend Modint operator*(const long long a, const Modint b){
        return b * a;
    }
    friend Modint operator/(const long long a, const Modint b){
        return Modint(a) / b;
    }
    Modint &operator+=(const Modint rhs){
        a += rhs.a;
        if(a >= MOD){
            a -= MOD;
        }
        return *this;
    }
    Modint &operator-=(const Modint rhs){
        if(a < rhs.a){
            a += MOD;
        }
        a -= rhs.a;
        return *this;
    }
    Modint &operator*=(const Modint rhs){
        a = (long long)a * rhs.a % MOD;
        return *this;
    }
    Modint &operator/=(Modint rhs){
        int x = MOD - 2;
        while(x){
            if(x % 2){
                *this *= rhs;
            }
            rhs *= rhs;
            x /= 2;
        }
        return *this;
    }
    Modint &operator++(){
        *this += 1;
        return *this;
    }
    Modint &operator--(){
        *this -= 1;
        return *this;
    }
    Modint operator++(int){
        Modint res = *this;
        ++(*this);
        return res;
    }
    Modint operator--(int){
        Modint res = *this;
        --(*this);
        return res;
    }
    Modint &operator+=(const long long rhs){
        *this += Modint(rhs);
        return *this;
    }
    Modint &operator-=(const long long rhs){
        *this -= Modint(rhs);
        return *this;
    }
    Modint &operator*=(const long long rhs){
        *this *= Modint(rhs);
        return *this;
    }
    Modint &operator/=(const long long rhs){
        *this /= Modint(rhs);
        return *this;
    }
    Modint operator+() const{
        return *this;
    }
    Modint operator-() const{
        return Modint()-*this;
    }
    bool operator==(const Modint rhs) const{
        return a == rhs.a;
    }
    bool operator==(const long long rhs) const{
        return a == rhs;
    }
    friend bool operator==(const long long a, const Modint b){
        return a == b.a;
    }
    bool operator!=(const Modint rhs) const{
        return a != rhs.a;
    }
    bool operator!=(const long long rhs) const{
        return a != rhs;
    }
    friend ostream &operator<<(ostream &os, const Modint x){
        os << x.a;
        return os;
    }
    friend istream &operator>>(istream &is, Modint &x){
        is >> x.a;
        return is;
    }
    explicit operator bool() const{
        return a > 0;
    }
    bool operator!(){
        return a == 0;
    }
    explicit operator int() const{
        return a;
    }
    explicit operator long long() const{
        return (long long) a;
    }
    friend Modint pow(Modint a, long long b){
        Modint res = 1;
        while(b){
            if(b % 2){
                res *= a;
            }
            a *= a;
            b /= 2;
        }
        return res;
    }
};
using mint = Modint<1000000007>;
