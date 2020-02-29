#include <limits>

template <typename T, int MaxSize>
class Splay {
public:
    Splay() {
        insert(std::numeric_limits<T>::max());
        insert(std::numeric_limits<T>::min());
    }

    void insert(T key) {
        int x = Root, f = 0;
        while (x != 0 && Tree[x].Key != key) {
            f = x;
            x = select(x, key);
        }
        if (x != 0) {
            ++Tree[x].Count;
        } else {
            x = create(key);
            if (f)
                select(f, key) = x;
            Tree[x].Father = f;    
        }
        splay(x);
    }

    int rank(T key) {
        findImpl(key);
        return Tree[Tree[Root][0]].Size;
    }

    T rankat(int rk) {
        rk += 1;
        int x = Root;
        while (true) {
            int ls = Tree[Tree[x][0]].Size;
            if (Tree[x][0] && rk <= ls) {
                x = Tree[x][0];
            } else if (rk > ls + Tree[x].Count) {
                rk -= ls + Tree[x].Count;
                x = Tree[x][1];
            } else {
                return Tree[x].Key;
            }
        }
    }

    T previous(T key) {
        int x = previousImpl(key);
        return x == 0 ? std::numeric_limits<T>::min() : Tree[x].Key;
    }

    T next(T key) {
        int x = nextImpl(key);
        return x == 0 ? std::numeric_limits<T>::max() : Tree[x].Key;
    }

    void remove(T key) {
        int p = previousImpl(key), n = nextImpl(key);
        splay(p); splay(n, p);
        int x = Tree[n][0];
        if (Tree[x].Count > 1) {
            --Tree[x].Count;
            splay(x);
        } else {
            Tree[n][0] = 0;
        }
    }

    bool find(T key) {
        findImpl(key);
        return Tree[Root].Key == key;
    }
private:
    struct Node {
        T Key; int Left, Right, Father, Size, Count;
        int &operator[](int x) { return x == 0 ? Left : Right; }
    } Tree[MaxSize];
    int Root, UUID;

    void pushup(int x) { Tree[x].Size = Tree[Tree[x][0]].Size + Tree[Tree[x][1]].Size + Tree[x].Count; }

    int which(int x) { return x == Tree[Tree[x].Father][1]; }

    int &select(int now, int key) { return Tree[now][Tree[now].Key < key]; }

    int create(T key) { Tree[++UUID] = { key, 0, 0, 0, 1, 1 }; return UUID; }

    void rotate(int x) {
        int y = Tree[x].Father, z = Tree[y].Father, k = which(x), w = Tree[x][k ^ 1];
        Tree[y][k] = w;
        Tree[w].Father = y;
        Tree[z][which(y)] = x;
        Tree[x].Father = z;
        Tree[x][k ^ 1] = y;
        Tree[y].Father = x;
        pushup(y);
        pushup(x);
    }

    void splay(int x, int target = 0) {
        while (Tree[x].Father != target) {
            int y = Tree[x].Father, z = Tree[y].Father;
            if (z != target)
                which(x) == which(y) ? rotate(y) : rotate(x);
            rotate(x);
        }
        if (target == 0)
            Root = x;
    }

    void findImpl(T key) {
        if (!Root)
            return;
        int x = Root;
        while (select(x, key) && Tree[x].Key != key)
            x = select(x, key);
        splay(x);
    }

    

    int previousImpl(T key) {
        findImpl(key);
        if (Tree[Root].Key < key) return Root;
        int x = Tree[Root][0];
        while (Tree[x][1])
            x = Tree[x][1];
        return x;
    }

    int nextImpl(T key) {
        findImpl(key);
        if (Tree[Root].Key > key) return Root;
        int x = Tree[Root][1];
        while (Tree[x][0])
            x = Tree[x][0];
        return x;
    }
};
