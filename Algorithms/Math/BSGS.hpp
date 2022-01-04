#ifndef BSGS_HPP
#define BSGS_HPP

#if __cplusplus < 201703L
#error "A C++ 17 compiler is required."
#error "Add \"-std=c++17\" to your compiler arguments if you have one."
#endif

#include <optional>

namespace Bsgs {

template <typename T> optional<T> bsgs(T a, T b, T p) {
    T sqrtp = sqrt(p) + 1, prod = b;
    T base = power(a, sqrtp, p);
    unordered_map<T, T> mp;
    for (T i = 1; i <= sqrtp; ++i) {
        prod = prod * a % p;
        mp[prod] = i;
    }
    prod = base;
    for (T i = 1; i <= sqrtp; ++i) {
        auto it = mp.find(prod);
        if (it != mp.end()) {
            return i * sqrtp - it->second;
        }
        prod = prod * base % p;
    }
    return nullopt;
}

} // namespace Bsgs

#endif
