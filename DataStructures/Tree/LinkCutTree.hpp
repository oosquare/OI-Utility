#ifndef LINKCUTTREE_H
#define LINKCUTTREE_H

namespace LinkCutTree {

/**
 * This implement of Link-Cut Tree is an example.
 * What to add and how to use it depend on your need.
 */

template <typename T, int size> class LinkCutTree {
public:
    void init(int x, T key) {
        tree[x].key = tree[x].sum = key;
        tree[x].size = 1;
    }

    void link(int x, int y) {
        makeRoot(x);

        if (findRoot(y) != x)
            tree[x].fa = y;
    }

    void cut(int x, int y) {
        makeRoot(x);

        if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls) {
            tree[x].rs = tree[y].fa = 0;
            pushup(x);
        }
    }

    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }

    /** add your own operation here. */
    void add(int x, int y, T v) {
        updateAdd(split(x, y), v);
    }

    T query(int x, int y) {
        return tree[split(x, y)].sum;
    }

private:
    struct Node {
        int ls, rs, fa, size;
        bool rev;
        T key, sum, add;

        int &operator[](int x) {
            return (x == 0 ? ls : rs);
        }
    };

    Node tree[size];
    int st[size];

    void pushup(int x) {
        tree[x].size = tree[tree[x].ls].size + 1 + tree[tree[x].rs].size;
        tree[x].sum = tree[tree[x].ls].sum + tree[x].key + tree[tree[x].rs].sum;
    }

    void updateReverse(int x) {
        tree[x].rev ^= 1;
        swap(tree[x].ls, tree[x].rs);
    }

    /** add your own operation here. */
    void updateAdd(int x, T v) {
        tree[x].key += v;
        tree[x].sum += v;
        tree[x].add += v;
    }

    void pushdown(int x) {
        if (tree[x].rev) {
            if (tree[x].ls)
                updateReverse(tree[x].ls);

            if (tree[x].rs)
                updateReverse(tree[x].rs);

            tree[x].rev = false;
        }

        /** add your own operation here. */
        if (tree[x].add) {
            if (tree[x].ls)
                updateAdd(tree[x].ls, tree[x].add);

            if (tree[x].rs)
                updateAdd(tree[x].rs, tree[x].add);

            tree[x].add = 0;
        }
    }

    int which(int x) {
        return tree[tree[x].fa].rs == x;
    }

    bool isRoot(int x) {
        return tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x;
    }

    void rotate(int x) {
        int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

        if (!isRoot(y))
            tree[z][which(y)] = x;

        tree[x][k ^ 1] = y;
        tree[y][k] = w;
        tree[x].fa = z;
        tree[y].fa = x;

        if (w)
            tree[w].fa = y;

        pushup(y);
        pushup(x);
    }

    void splay(int x) {
        int top = 0;
        st[++top] = x;

        for (int y = x; !isRoot(y); y = tree[y].fa)
            st[++top] = tree[y].fa;

        while (top)
            pushdown(st[top--]);

        for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
            if (!isRoot(y))
                rotate(which(x) == which(y) ? y : x);
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = tree[x].fa) {
            splay(x);
            tree[x].rs = y;
            pushup(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        updateReverse(x);
    }

    int findRoot(int x) {
        access(x);
        splay(x);
        pushdown(x);

        while (tree[x].ls) {
            x = tree[x].ls;
            pushdown(x);
        }

        splay(x);
        return x;
    }

    int split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return y;
    }
};

} // namespace LinkCutTree

#endif
