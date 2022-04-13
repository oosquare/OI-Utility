#ifndef MODINTEGER_HPP
#define MODINTEGER_HPP

#if __cplusplus < 201703L
#error "A C++ 14 compiler is required."
#error "Add \"-std=c++14\" to your compiler arguments if you have one."
#endif

#include <istream>
#include <ostream>

namespace ModInteger {

template <int MOD>
class ModInteger {
public:
    using Self = ModInteger<MOD>;

    struct Hash {
        unsigned long long operator()(const Self &v) const { return v.hash(); }
    };

    constexpr ModInteger(const int val = 0) : val(val) {}
    constexpr ModInteger(const Self &) = default;
    constexpr ModInteger(Self &&) = default;
    ~ModInteger() = default;

    constexpr operator bool() const { return val != 0; }
    constexpr operator int() const { return val; }

    constexpr bool operator<(const Self &rhs) const { return val < rhs.val; }
    constexpr bool operator>(const Self &rhs) const { return val > rhs.val; }
    constexpr bool operator<=(const Self &rhs) const { return val <= rhs.val; }
    constexpr bool operator>=(const Self &rhs) const { return val >= rhs.val; }
    constexpr bool operator==(const Self &rhs) const { return val == rhs.val; }
    constexpr bool operator!=(const Self &rhs) const { return val != rhs.val; }

    constexpr Self &operator=(const Self &) = default;
    constexpr Self &operator=(Self &&) = default;

    constexpr Self operator+(const Self &rhs) const {
        int tmp = val + rhs.val;
        return Self(tmp >= MOD ? tmp - MOD : tmp);
    }

    constexpr Self operator-(const Self &rhs) const {
        int tmp = val - rhs.val;
        return Self(tmp < 0 ? tmp + MOD : tmp);
    }

    constexpr Self operator*(const Self &rhs) const { return Self(1ll * val * rhs.val % MOD); }
    constexpr Self operator/(const Self &rhs) const { return *this * rhs.power(Self(MOD - 2)); }
    constexpr Self operator%(const Self &rhs) const { return Self(val % rhs.val); }

    constexpr Self operator+() const { return *this; }
    constexpr Self operator-() const { return Self(MOD - val); }

    constexpr Self &operator+=(const Self &rhs) { return (*this = *this + rhs); }
    constexpr Self &operator-=(const Self &rhs) { return (*this = *this - rhs); }
    constexpr Self &operator*=(const Self &rhs) { return (*this = *this * rhs); }
    constexpr Self &operator/=(const Self &rhs) { return (*this = *this / rhs); }
    constexpr Self &operator%=(const Self &rhs) { return (*this = *this % rhs); }
    constexpr Self &operator&=(const Self &rhs) { return (*this = *this & rhs); }
    constexpr Self &operator|=(const Self &rhs) { return (*this = *this | rhs); }
    constexpr Self &operator^=(const Self &rhs) { return (*this = *this ^ rhs); }
    constexpr Self &operator<<=(const Self &rhs) { return (*this = *this << rhs); }
    constexpr Self &operator>>=(const Self &rhs) { return (*this = *this >> rhs); }

    constexpr friend std::istream &operator>>(std::istream &is, Self &v) { return (is >> v.val); }
    constexpr friend std::ostream &operator<<(std::ostream &os, const Self &v) { return (os << v.val); }

    constexpr void set(const int val) {
        this->val = val;
        adjust();
    }

    constexpr const int &get() const { return val; }
    constexpr int &get() { return val; }

    constexpr Self power(Self y) const {
        Self res(1), x(*this);

        for (; y.val; y.val /= 2) {
            if (y.val % 2 == 1)
                res = res * x;

            x = x * x;
        }

        return res;
    }

    constexpr Self inverse() const { return Self(1) / *this; }

    std::string toString() const { return std::to_string(val); }

    constexpr unsigned long long hash() const { return std::hash<int>()(val); }

    constexpr void adjustForAdd() {
        if (val >= MOD)
            val -= MOD;
    }

    constexpr void adjustForSub() {
        if (val < MOD)
            val += MOD;
    }

    constexpr void adjust() {
        val = val % MOD;
        adjustForSub();
    }

private:
    int val;
};
    
} // namespace ModInteger

namespace std {
    template <int MOD>
    struct hash<ModInteger::ModInteger<MOD>> {
        unsigned long long operator()(const ModInteger::ModInteger<MOD> &v) const { return v.hash(); }
    };
} // namespace std

#endif
