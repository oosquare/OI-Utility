template <typename T>
T power(T x, T k, T mod) {
    T res = 1;
    while (k) {
        if (k % 2)
            res = res * x % mod;
        x = x * x % mod;
        k /= 2;
    }
    return res % mod;
}