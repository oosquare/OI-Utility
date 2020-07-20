#include <limits>

template <typename T, int MaxSize>
class ScapegoatTree {
public:
    void insert(T key) {
        int o = Root;
        insert(Root, key);
        check(o, key);
    }

    int rank(T key) {
        int x = Root, res = 1;
        while (x) {
            if (!(Tree[x].Key < key)) { // Tree[x].Key >= key
                x = Tree[x][0];
            } else {
                res += Tree[Tree[x][0]].Fact + Tree[x].Exist;
                x = Tree[x][1];
            }
        }
        return res;
    }

    T rankat(int rk) {
        if (rk < 1 || rk > Tree[Root].Size)
            return T();
        int x = Root;
        while (x) {
            if (Tree[x].Exist && Tree[Tree[x][0]].Fact + 1 == rk) {
                return Tree[x].Key;
            } else if (Tree[Tree[x][0]].Fact >= rk) {
                x = Tree[x][0];
            } else {
                rk -= Tree[Tree[x][0]].Fact + Tree[x].Exist;
                x = Tree[x][1];
            }
        }
        return T();
    }

    void remove(T key) {
        remove(Root, rank(key));
        if (Tree[Root].Size * Alpha > Tree[Root].Fact)
            rebuild(Root);
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
        if (rk > Tree[Root].Size)
            return std::numeric_limits<T>::max();
        else
            return rankat(rk);
    }

private:
    static constexpr double Alpha = 0.718;
    struct Node {
        T Key;
        int Left, Right, Size, Fact;
        bool Exist;
        int &operator[](int x) { return x == 0 ? Left : Right; }
    } Tree[MaxSize];
    int Root, UUID, Trash[MaxSize], Top, Temp[MaxSize], Length;

    int create(T key) {
        int root = Top ? Trash[Top--] : ++UUID;
        Tree[root] = { key, 0, 0, 1, 1, true };
        return root;
    }

    void pushup(int x) {
        Tree[x].Size = Tree[Tree[x][0]].Size + Tree[Tree[x][1]].Size + 1;
        Tree[x].Fact = Tree[Tree[x][0]].Fact + Tree[Tree[x][1]].Fact + Tree[x].Exist;
    }

    void enumerate(int x) {
        if (!x)
            return;
        enumerate(Tree[x][0]);
        if (Tree[x].Exist)
            Temp[++Length] = x;
        else
            Trash[++Top] = x;
        enumerate(Tree[x][1]);
    }

    void make(int &x, int l, int r) {
        int mid = (l + r) >> 1;
        x = Temp[mid];
        if (l == r) {
            T k = Tree[x].Key;
            Tree[x] = { k, 0, 0, 1, 1, true };
            return;
        }
        if (l < mid)
            make(Tree[x][0], l, mid - 1);
        else
            Tree[x][0] = 0;
        make(Tree[x][1], mid + 1, r);
        pushup(x);
    }

    void rebuild(int &x) {
        Length = 0;
        enumerate(x);
        if (Length)
            make(x, 1, Length);
        else
            x = 0;
    }

    bool imblanced(int x) {
        return Tree[x].Fact * Alpha <= max(Tree[Tree[x][0]].Fact, Tree[Tree[x][1]].Fact);
    }

    void check(int x, T key) {
        int s = !(Tree[x].Key < key) ? 0 : 1; // key <= Tree[x].Key
        while (Tree[x][s]) {
            if (imblanced(Tree[x][s])) {
                rebuild(Tree[x][s]);
                return;
            }
            x = Tree[x][s];
            s = !(Tree[x].Key < key) ? 0 : 1; // key <= Tree[x].Key
        }
    }

    void insert(int &x, T key) {
        if (!x) {
            x = create(key);
            return;
        }
        if (!(Tree[x].Key < key)) // key <= Tree[x].Key
            insert(Tree[x][0], key);
        else
            insert(Tree[x][1], key);
        pushup(x);
    }

    void remove(int &x, int rk) {
        if (Tree[x].Exist && Tree[Tree[x][0]].Fact + 1 == rk) {
            Tree[x].Exist = 0;
            pushup(x);
            return;
        }
        if (Tree[Tree[x][0]].Fact + Tree[x].Exist >= rk)
            remove(Tree[x][0], rk);
        else
            remove(Tree[x][1], rk - Tree[Tree[x][0]].Fact - Tree[x].Exist);
        pushup(x);
    }
};