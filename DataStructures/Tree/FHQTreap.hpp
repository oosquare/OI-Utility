template <typename T, int MaxSize>
class FHQTreap 
{
public:
    FHQTreap() { Seed = (int)(MaxSize * 565463ll % 2147483647); }

    void insert(T key) {
        int x, y;
        split(Root, key - 1, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void remove(T key) {
        int x, y, z;
        split(Root, key, x, z);
        split(x, key - 1, x, y);
        if(y) {
            if(Top < (MaxSize << 8) - 5) Stack[++Top] = y;
            y = merge(Tree[y].Left, Tree[y].Right);
        }
        Root = merge(merge(x, y), z);
    }

    int rank(T key) {
        int x, y, ans;
        split(Root, key - 1, x, y);
        ans = Tree[x].Size + 1;
        Root = merge(x, y);
        return ans;
    }

    T at(int r) {
        int root = Root;
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

    T prev(T key) {
        int x, y, root;
        T ans;
        split(Root, key - 1, x, y);
        root = x;
        while (Tree[root].Right) root = Tree[root].Right;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    T next(T key) {
        int x, y, root;
        T ans;
        split(Root, key, x, y);
        root = y;
        while (Tree[root].Left) root = Tree[root].Left;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    int size() {
        return Tree[Root].Size;
    }
    
    bool find(T key) {
        int x, y, z;
        split(Root, key, x, z);
        split(x, key - 1, x, y);
        bool ans;
        if(Tree[y].Size) ans = true;
        else ans = false;
        Root = merge(merge(x, y), z);
        return ans;
    }

private:
    struct Node 
    {
        T Key;
        int Left, Right, Size, Priority;
    } Tree[MaxSize];
    int Seed, Total, Root, Top, Stack[MaxSize >> 8];

    int rad() { return Seed = int(Seed * 482711ll % 2147483647); }

    int create(T key) {
        int root = Top ? Stack[Top--] : ++Total;
        Tree[root].Key = key;
        Tree[root].Size = 1;
        Tree[root].Left = Tree[root].Right = 0;
        Tree[root].Priority = rad();
        return root;
    }

    void pushup(int root) {
        if(root != 0)
            Tree[root].Size = Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1; 
    }

    void split(int root, T key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (!(key < Tree[root].Key)) {
            x = root;
            split(Tree[root].Right, key, Tree[root].Right, y);
        } else {
            y = root;
            split(Tree[root].Left, key, x, Tree[root].Left);
        }
        pushup(root);
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0)
            return x + y;
        if (Tree[x].Priority > Tree[y].Priority) {
            Tree[x].Right = merge(Tree[x].Right, y);
            pushup(x);
            return x;
        } else {
            Tree[y].Left = merge(x, Tree[y].Left);
            pushup(y);
            return y;
        }
    }
};