const int NUM = 400005;
mint fact[NUM + 1], fact_inv[NUM + 1], inv[NUM + 1];
mint combi(long long N_, long long K_){
    static const int Mod_ = fact[0].getmod();
    static_assert(NUM < Mod_, "");
    if(fact[0] == 0){
        inv[1] = fact[0] = fact_inv[0] = 1;
        for(int i = 2; i <= NUM; i++){
            inv[i] = inv[Mod_ % i] * (Mod_ - Mod_ / i);
        }
        for(int i = 1; i <= NUM; i++){
            fact[i] = fact[i - 1] * i;
            fact_inv[i] = fact_inv[i - 1] * inv[i];
        }
    }
    if(K_ < 0 or K_ > N_) return 0;
    return fact_inv[K_] * fact[N_] * fact_inv[N_ - K_];
}
mint hcomb(long long N_, long long K_){
    return ((N_ | K_) == 0) ? 1 : combi(N_ + K_ - 1, K_);
}
