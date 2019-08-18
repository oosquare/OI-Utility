class IrrotationalTreap 
{
public:
    IrrotationalTreap() {
        Root = 0;
        create(0x3f3f3f3f);
        Tree[1].Size = 0;
        Total = 1;
        Root = 1;
    }

    void insert(int key) { insert(Root, key); }

    void remove(int key) { remove(Root, key); }

    int rank(int key) { return rank(Root, key); }

    int at(int k) { return at(Root, k); }

    int lower(int key) { return lower(Root, key); }

    int upper(int key) { return upper(Root, key); }

private:
    struct Node {
        int Key, Size, Count, Left, Right, Priority;
    } Tree[1000001];
    int Total;
    int Root;
    int create(int key) {
        ++Total;
        Tree[Total].Key = key;
        Tree[Total].Size = 1;
        Tree[Total].Left = Tree[Total].Right = 0;
        Tree[Total].Priority = rad();
        return Total;
    }

    int rad() { return Seed = int(Seed * 482711ll % 2147483647); }

    void update(int root) {
        int l = Tree[root].Left, r = Tree[root].Right;
        Tree[root].Size = 1 + Tree[l].Size + Tree[r].Size;
    }

    void split(int root, int& a, int& b, int key) {
        if (root == 0) {
            a = b = 0;
            return;
        }
        if (Tree[root].Key <= key) {
            a = root;
            split(Tree[root].Right, Tree[a].Right, b, key);
        } else {
            b = root;
            split(Tree[root].Left, a, Tree[b].Left, key);
        }
        update(root);
    }

    void merge(int& root, int a, int b) {
        if (a == 0 || b == 0) {
            root = a + b;
            return;
        }
        if (Tree[a].Priority < Tree[b].Priority) {
            root = a;
            merge(Tree[root].Right, Tree[a].Right, b);
        } else {
            root = b;
            merge(Tree[root].Left, a, Tree[b].Left);
        }
        update(root);
    }

    void insert(int& root, int key) {
        int x = 0, y = 0, nnode = create(key);
        split(root, x, y, key);
        merge(x, x, nnode);
        merge(root, x, y);
    }

    void remove(int& root, int key) {
        int x = 0, y = 0, z = 0;
        split(root, x, y, key);
        split(x, x, z, key - 1);
        merge(z, Tree[z].Left, Tree[z].Right);
        merge(x, x, z);
        merge(root, x, y);
    }

    int rank(int& root, int key) {
        int x = 0, y = 0;
        split(root, x, y, key - 1);
        int tmp = Tree[x].Size + 1;
        merge(root, x, y);
        return tmp;
    }

    int at(int root, int k) {
        while (Tree[Tree[root].Left].Size + 1 != k) {
            if (Tree[Tree[root].Left].Size >= k)
                root = Tree[root].Left;
            else {
                k -= Tree[Tree[root].Left].Size + 1;
                root = Tree[root].Right;
            }
        }
        return Tree[root].Key;
    }

    int lower(int& root, int key) {
        int x = 0, y = 0;
        split(root, x, y, key - 1);
        int tmp = at(x, Tree[x].Size);
        merge(root, x, y);
        return tmp;
    }

    int upper(int& root, int key) {
        int x = 0, y = 0;
        split(root, x, y, key);
        int tmp = at(y, 1);
        merge(root, x, y);
        return tmp;
    }
};
