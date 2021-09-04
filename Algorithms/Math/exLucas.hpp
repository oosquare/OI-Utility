namespace exLucas {

typedef long long ll;

ll n, m, p;
ll a[100001], b[100001], total;

ll power(ll x, ll k, ll p) {
    ll res = 1;
    while (k) {
        if (k % 2)
            res = res * x % p;
        x = x * x % p;
        k /= 2;
    }
    return res % p;
}

ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int d = exGCD(b, a % b, x, y);
        int t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

ll inverse(ll x, ll p) {
    ll x0, y0;
    exGCD(x, p, x0, y0);
    return (x0 + p) % p;
}

ll factor(ll n, ll p, ll pk) {
    if (n == 0)
        return 1;
    ll a = 1, b = 1;
    for (ll i = 1; i <= pk; ++i)
        if (i % p)
            a = a * i % pk;
    a = power(a, n / pk, pk);
    for (ll i = (n / pk) * pk; i <= n; ++i)
        if (i % p)
            b = b * (i % pk) % pk;
    return factor(n / p, p, pk) * a % pk * b % pk;
}

ll exponent(ll n, ll p) {
    if (n < p)
        return 0;
    return exponent(n / p, p) + n / p;
}

ll C(ll n, ll m, ll p, ll pk) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    ll fn = factor(n, p, pk), fm = factor(m, p, pk), fnm = factor(n - m, p, pk);
    ll ex = power(p, exponent(n, p) - exponent(m, p) - exponent(n - m, p), pk);
    return fn * inverse(fm, pk) % pk * inverse(fnm, pk) % pk * ex % pk;
}

ll CRT(ll prod) {
    ll ans = 0;
    for (int i = 1; i <= total; ++i) {
        ll m = prod / a[i];
        ll v = inverse(m, a[i]);
        ans = (ans + b[i] * m % prod * v % prod) % prod;
    }
    return ans;
}

ll calculate(ll n, ll m, ll p) {
    ll p2 = p;
    total = 0;
    for (ll i = 2; i * i <= p; ++i) {
        if (p2 % i == 0) {
            ll pk = 1;
            while (p2 % i == 0) {
                pk *= i;
                p2 /= i;
            }
            a[++total] = pk;
            b[total] = C(n, m, i, pk);
        }
    }
    if (p2 != 1) {
        a[++total] = p2;
        b[total] = C(n, m, p2, p2);
    }
    return CRT(p);
}

} // namespace exLucas