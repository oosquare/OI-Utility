#ifndef LINEARBASIS_HPP
#define LINEARBASIS_HPP

#if __cplusplus < 201103L
#error "A C++ 11 compiler is required."
#error "Add \"-std=c++11\" to your compiler arguments if you have one."
#endif

namespace LinearBasis {

class LinearBasis {
public:
    LinearBasis() {
        for (int i = 0; i < len; ++i)
            a[i] = 0;
    }

    void insert(long long x) {
        if (!x)
            return;

        for (int i = len - 1; i >= 0; --i) {
            if (((x >> i) & 1) == 0)
                continue;

            if (a[i]) {
                x ^= a[i];
            } else {
                for (int j = i - 1; j >= 0; --j)
                    if ((x >> j) & 1)
                        x ^= a[j];

                for (int j = len - 1; j > i; --j)
                    if ((a[j] >> i) & 1)
                        a[j] ^= x;

                a[i] = x;
                return;
            }
        }
    }

    void merge(const LinearBasis &rhs) {
        for (int i = 0; i < len; ++i)
            insert(rhs.a[i]);
    }

    static LinearBasis merge(const LinearBasis &lhs, const LinearBasis &rhs) {
        LinearBasis res = lhs;
        res.merge(rhs);
        return res;
    }

    long long query() {
        long long res = 0;

        for (int i = len - 1; i >= 0; --i)
            res ^= a[i];

        return res;
    }

private:
    static constexpr int len = 64;
    long long a[len];
};

} // namespace LinearBasis

#endif