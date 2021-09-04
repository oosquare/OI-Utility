template <typename T>
T GCD(T a, T b) {
    return b == 0 ? a : GCD(b, a % b);
}

template <typename T>
T LCM(T a, T b) {
    return a / GCD(a, b) * b; 
}

template <typename T>
T exGCD(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        T d = exGCD(b, a % b, x, y);
        T t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

template <typename T>
bool solveEquationAxByC(T a, T b, T c, T &x, T &y) {
    T d = exGCD(a, b, x, y);
    if (c % d)
        return false;
    T k = c / d;
    x *= k;
    y *= k;
    return true;
} 