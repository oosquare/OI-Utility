#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <limits>

namespace Splay {

template <typename T, int size> class Splay {
public:
    Splay() {
        insert(std::numeric_limits<T>::max());
        insert(std::numeric_limits<T>::min());
    }

    void insert(T key) {
        int x = root, f = 0;
        while (x != 0 && tree[x].key != key) {
            f = x;
            x = select(x, key);
        }
        if (x != 0) {
            ++tree[x].count;
        } else {
            x = create(key);
            if (f)
                select(f, key) = x;
            tree[x].father = f;    
        }
        splay(x);
    }

    int rank(T key) {
        findImpl(key);
        return tree[tree[root][0]].size;
    }

    T rankat(int rk) {
        rk += 1;
        int x = root;
        while (true) {
            int ls = tree[tree[x][0]].size;
            if (tree[x][0] && rk <= ls) {
                x = tree[x][0];
            } else if (rk > ls + tree[x].count) {
                rk -= ls + tree[x].count;
                x = tree[x][1];
            } else {
                return tree[x].key;
            }
        }
    }

    T previous(T key) {
        int x = previousImpl(key);
        return x == 0 ? std::numeric_limits<T>::min() : tree[x].key;
    }

    T next(T key) {
        int x = nextImpl(key);
        return x == 0 ? std::numeric_limits<T>::max() : tree[x].key;
    }

    void remove(T key) {
        int p = previousImpl(key), n = nextImpl(key);
        splay(p); splay(n, p);
        int x = tree[n][0];
        if (tree[x].count > 1) {
            --tree[x].count;
            splay(x);
        } else {
            tree[n][0] = 0;
        }
    }

    bool find(T key) {
        findImpl(key);
        return tree[root].key == key;
    }
private:
    struct Node {
        T key; int left, right, father, size, count;
        int &operator[](int x) { return x == 0 ? left : right; }
    } tree[size];
    int root, uuid;

    void pushup(int x) { tree[x].size = tree[tree[x][0]].size + tree[tree[x][1]].size + tree[x].count; }

    int which(int x) { return x == tree[tree[x].father][1]; }

    int &select(int now, int key) { return tree[now][tree[now].key < key]; }

    int create(T key) { tree[++uuid] = { key, 0, 0, 0, 1, 1 }; return uuid; }

    void rotate(int x) {
        int y = tree[x].father, z = tree[y].father, k = which(x), w = tree[x][k ^ 1];
        tree[y][k] = w;
        tree[w].father = y;
        tree[z][which(y)] = x;
        tree[x].father = z;
        tree[x][k ^ 1] = y;
        tree[y].father = x;
        pushup(y);
        pushup(x);
    }

    void splay(int x, int target = 0) {
        while (tree[x].father != target) {
            int y = tree[x].father, z = tree[y].father;
            if (z != target)
                which(x) == which(y) ? rotate(y) : rotate(x);
            rotate(x);
        }
        if (target == 0)
            root = x;
    }

    void findImpl(T key) {
        if (!root)
            return;
        int x = root;
        while (select(x, key) && tree[x].key != key)
            x = select(x, key);
        splay(x);
    }

    int previousImpl(T key) {
        findImpl(key);
        if (tree[root].key < key) return root;
        int x = tree[root][0];
        while (tree[x][1])
            x = tree[x][1];
        return x;
    }

    int nextImpl(T key) {
        findImpl(key);
        if (tree[root].key > key) return root;
        int x = tree[root][1];
        while (tree[x][0])
            x = tree[x][0];
        return x;
    }
};

} // namespace Splay

#endif