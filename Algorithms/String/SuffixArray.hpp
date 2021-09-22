#ifndef SUFFIXARRAY_HPP
#define SUFFIXARRAY_HPP

namespace SuffixArray {

template <int size> class SuffixArray {
public:
    inline void init(char str[]) {
        len = strlen(str + 1);
        for (int i = 1; i <= len; ++i)
            data[i] = str[i];
    }

    inline void preprocess(bool sa, bool height) {
        if (sa)
            saPreprocess(len);
        if (height)
            heightPreprocess(len);
    }

    inline int atRank(int x) { return rank[cur][x]; }

    inline int atSa(int x) { return sa[x]; }

    inline int atHeight(int x) { return height[x]; }

public:
    int sa[size], rank[2][size], height[size], tmp[size], data[size];
    int cur, len;

    void sort(int n, int m) {
        for (int i = 0; i <= m; ++i)
            tmp[i] = 0;
        for (int i = 1; i <= n; ++i)
            ++tmp[rank[cur][rank[cur ^ 1][i]]];
        for (int i = 1; i <= m; ++i)
            tmp[i] += tmp[i - 1];
        for (int i = n; i >= 1; i--)
            sa[tmp[rank[cur][rank[cur ^ 1][i]]]--] = rank[cur ^ 1][i];
    }

    inline bool equal(int f[], int x, int y, int l) {
        return f[x] == f[y] && f[x + l] == f[y + l];
    }

    void saPreprocess(int n) {
        int m;
        for (int i = 1; i <= n; ++i) {
            rank[cur][i] = data[i];
            rank[cur ^ 1][i] = i;
        }
        m = 127;
        sort(n, m);
        for (int w = 1, p = 1, i; p < n; w *= 2, m = p) {
            for (p = 0, i = n - w + 1; i <= n; ++i)
                rank[cur ^ 1][++p] = i;
            for (i = 1; i <= n; ++i)
                if (sa[i] > w)
                    rank[cur ^ 1][++p] = sa[i] - w;
            sort(n, m);
            cur ^= 1;
            rank[cur][sa[1]] = p = 1;
            for (i = 2; i <= n; ++i)
                rank[cur][sa[i]] =
                    equal(rank[cur ^ 1], sa[i], sa[i - 1], w) ? p : ++p;
        }
    }

    void heightPreprocess(int n) {
        int j, k = 0;
        for (int i = 1; i <= n; height[rank[cur][i++]] = k)
            for (k = k ? k - 1 : k, j = sa[rank[cur][i] - 1];
                    data[i + k] == data[j + k]; ++k)
                ;
    }
};

} // namespace SuffixArray

#endif
