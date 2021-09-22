#ifndef SCAPEGOATTREE_HPP
#define SCAPEGOATTREE_HPP

#include <limits>

namespace ScapegoatTree {

template <typename T, int size> class ScapegoatTree {
public:
    void insert(T key) {
        int o = root;
        insert(root, key);
        check(o, key);
    }

    int rank(T key) {
        int x = root, res = 1;
        while (x) {
            if (!(tree[x].key < key)) { // tree[x].key >= key
                x = tree[x][0];
            } else {
                res += tree[tree[x][0]].fact + tree[x].exist;
                x = tree[x][1];
            }
        }
        return res;
    }

    T rankat(int rk) {
        if (rk < 1 || rk > tree[root].size)
            return T();
        int x = root;
        while (x) {
            if (tree[x].exist && tree[tree[x][0]].fact + 1 == rk) {
                return tree[x].key;
            } else if (tree[tree[x][0]].fact >= rk) {
                x = tree[x][0];
            } else {
                rk -= tree[tree[x][0]].fact + tree[x].exist;
                x = tree[x][1];
            }
        }
        return T();
    }

    void remove(T key) {
        remove(root, rank(key));
        if (tree[root].size * Alpha > tree[root].fact)
            rebuild(root);
    }

    T previous(T key) {
        int rk = rank(key) - 1;
        if (rk < 1)
            return std::numeric_limits<T>::min();
        else
            return rankat(rk);
    }

    T next(T key) {
        int rk = rank(key + 1);
        if (rk > tree[root].size)
            return std::numeric_limits<T>::max();
        else
            return rankat(rk);
    }

private:
    static constexpr double Alpha = 0.718;
    struct Node {
        T key;
        int left, right, size, fact;
        bool exist;
        int &operator[](int x) { return x == 0 ? left : right; }
    } tree[size];
    int root, uuid, trash[size], top, tmp[size], length;

    int create(T key) {
        int root = top ? trash[top--] : ++uuid;
        tree[root] = { key, 0, 0, 1, 1, true };
        return root;
    }

    void pushup(int x) {
        tree[x].size = tree[tree[x][0]].size + tree[tree[x][1]].size + 1;
        tree[x].fact = tree[tree[x][0]].fact + tree[tree[x][1]].fact + tree[x].exist;
    }

    void enumerate(int x) {
        if (!x)
            return;
        enumerate(tree[x][0]);
        if (tree[x].exist)
            tmp[++length] = x;
        else
            trash[++top] = x;
        enumerate(tree[x][1]);
    }

    void make(int &x, int l, int r) {
        int mid = (l + r) >> 1;
        x = tmp[mid];
        if (l == r) {
            T k = tree[x].key;
            tree[x] = { k, 0, 0, 1, 1, true };
            return;
        }
        if (l < mid)
            make(tree[x][0], l, mid - 1);
        else
            tree[x][0] = 0;
        make(tree[x][1], mid + 1, r);
        pushup(x);
    }

    void rebuild(int &x) {
        length = 0;
        enumerate(x);
        if (length)
            make(x, 1, length);
        else
            x = 0;
    }

    bool imblanced(int x) {
        return tree[x].fact * Alpha <= max(tree[tree[x][0]].fact, tree[tree[x][1]].fact);
    }

    void check(int x, T key) {
        int s = !(tree[x].key < key) ? 0 : 1; // key <= tree[x].key
        while (tree[x][s]) {
            if (imblanced(tree[x][s])) {
                rebuild(tree[x][s]);
                return;
            }
            x = tree[x][s];
            s = !(tree[x].key < key) ? 0 : 1; // key <= tree[x].key
        }
    }

    void insert(int &x, T key) {
        if (!x) {
            x = create(key);
            return;
        }
        if (!(tree[x].key < key)) // key <= tree[x].key
            insert(tree[x][0], key);
        else
            insert(tree[x][1], key);
        pushup(x);
    }

    void remove(int &x, int rk) {
        if (tree[x].exist && tree[tree[x][0]].fact + 1 == rk) {
            tree[x].exist = 0;
            pushup(x);
            return;
        }
        if (tree[tree[x][0]].fact + tree[x].exist >= rk)
            remove(tree[x][0], rk);
        else
            remove(tree[x][1], rk - tree[tree[x][0]].fact - tree[x].exist);
        pushup(x);
    }
};

} // namespace ScapegoatTree

#endif