#ifdef DEBUG
template<typename T>
class Vec : public vector<T>{
public:
    Vec(){}
    Vec(int n):vector<T>(n){}
    Vec(int n, T a):vector<T>(n,a){}
    T& operator[](long long n){
        if(n < 0 or n >= this->size())throw out_of_range("Vec");
        return this->at(n);
    }
    const T& operator[](long long n)const{
        if(n < 0 or n >= this->size())throw out_of_range("Vec");
        return this->at(n);
    }
};
#define vector Vec
#endif
