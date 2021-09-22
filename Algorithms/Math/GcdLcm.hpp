#ifndef GCDLCM_HPP
#define GCDLCM_HPP

#if __cplusplus < 201703L
#error "A C++ 17 compiler is required."
#error "Add \"-std=c++17\" to your compiler arguments if you have one."
#endif

namespace GcdLcm {

template <typename T> T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T> T lcm(T a, T b) {
    return a / gcd(a, b) * b; 
}

template <typename T> T exgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        T d = exgcd(b, a % b, x, y);
        T t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

/** ax \equiv c (mod p) */
template <typename T> optional<T> solveEquation(T a, T c, T p) {
    a = (a % p + p) % p;
    c = (c % p + p) % p;
    T x, y;
    T d = exgcd(a, p, x, y);
    if (c % d != 0) return nullopt;
    x *= c / d;
    x = (x % (p / d) + (p / d)) % (p / d);
    return x;
}

} // namespace GcdLcm

#endif
