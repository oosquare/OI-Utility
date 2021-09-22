#ifndef QUICKPOWER_HPP
#define QUICKPOWER_HPP

namespace QuickPower {

template <typename T> T power(T x, T k, T mod) {
    T res = 1;
    while (k) {
        if (k % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
        k /= 2;
    }
    return res % mod;
}

} // namespace QuickPower

#endif
