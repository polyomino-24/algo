template <typename T>
T gcd(T a, T b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
template <typename T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}
