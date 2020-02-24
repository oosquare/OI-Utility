template <typename T, int MaxSize>
class PersistentFHQTreap 
{
public:
    PersistentFHQTreap() { Seed = (int)(MaxSize * 565463ll % 2147483647); }

    void insert(T key, int present, int past) {
        Root[present] = Root[past];
        int x, y, z;
        split(Root[present], key - 1, x, y);
        Root[present] = merge(merge(x, create(key)), y);
    }

    void remove(T key, int present, int past) {
        Root[present] = Root[past];
        int x, y, z;
        split(Root[present], key, x, z);
        split(x, key - 1, x, y);
        if(y) {
            y = merge(Tree[y].Left, Tree[y].Right);
        }
        Root[present] = merge(merge(x, y), z);
    }

    int rank(T key, int present, int past) {
        Root[present] = Root[past];
        int x, y, ans;
        split(Root[present], key - 1, x, y);
        ans = Tree[x].Size + 1;
        Root[present] = merge(x, y);
        return ans;
    }

    T at(int r, int present, int past) {
        Root[present] = Root[past];
        int root = Root[present];
        while (true) {
            if (Tree[Tree[root].Left].Size + 1 == r) {
                break;
            } else if (Tree[Tree[root].Left].Size + 1 > r) {
                root = Tree[root].Left;
            } else {
                r -= Tree[Tree[root].Left].Size + 1;
                root = Tree[root].Right;
            }
        }
        return Tree[root].Key;
    }

    T lower(T key, int present, int past) {
        Root[present] = Root[past];
        int x, y, root;
        T ans;
        split(Root[present], key - 1, x, y);
        root = x;
        while (Tree[root].Right) root = Tree[root].Right;
        ans = Tree[root].Key;
        Root[present] = merge(x, y);
        return ans;
    }

    T upper(T key, int present, int past) {
        Root[present] = Root[past];
        int x, y, root;
        T ans;
        split(Root[present], key, x, y);
        root = y;
        while (Tree[root].Left) root = Tree[root].Left;
        ans = Tree[root].Key;
        Root[present] = merge(x, y);
        return ans;
    }

    bool find(T key, int present) {
        int x, y, z;
        split(Root[present], key, x, z);
        split(x, key - 1, x, y);
        bool ans;
        if(Tree[y].Size) ans = true;
        else ans = false;
        Root[present] = merge(merge(x, y), z);
        return ans;
    }

private:
    struct Node {
        T Key;
        int Left, Right, Size, Priority;
    } Tree[MaxSize * 50 + 10];
    int Seed, Total, Root[MaxSize];

    int rad() { return Seed = int(Seed * 482711ll % 2147483647); }

    int create(int key) {
        int root = ++Total;
        Tree[root].Key = key;
        Tree[root].Size = 1;
        Tree[root].Left = Tree[root].Right = 0;
        Tree[root].Priority = rad();
        return root;
    }

    int copy(int root) {
        int newroot = ++Total;
        Tree[newroot] = Tree[root];
        return newroot;
    }

    void pushup(int root) {
        if(root != 0)
            Tree[root].Size = Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1; 
    }

    void split(int root, int key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (Tree[root].Key <= key) {
            x = copy(root);
            split(Tree[x].Right, key, Tree[x].Right, y);
            pushup(x);
        } else {
            y = copy(root);
            split(Tree[y].Left, key, x, Tree[y].Left);
            pushup(y);
        }
        
        
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0)
            return x + y;
        if (Tree[x].Priority > Tree[y].Priority) {
            int z = copy(x);
            Tree[z].Right = merge(Tree[z].Right, y);
            pushup(z);
            return z;
        } else {
            int z = copy(y);
            Tree[z].Left = merge(x, Tree[z].Left);
            pushup(z);
            return z;
        }
    }
};