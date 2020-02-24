template <typename T>
class FHQTreap {
public:
    FHQTreap() { Root = nullptr; }

    ~FHQTreap() {
        if (Root)
            delete Root;
    }

    void insert(T key) {
        Node *x, *y;
        split1(Root, key, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void remove(T key) {
        Node *x, *y, *z;
        split2(Root, key, x, z);
        split1(x, key, x, y);
        if (y) {
            y = merge(y->Left, y->Right);
        }
        Root = merge(merge(x, y), z);
    }

    int rank(T key) {
        Node *x, *y;
        int ans;
        split1(Root, key, x, y);
        ans = (x ? x->Size : 0) + 1;
        Root = merge(x, y);
        return ans;
    }

    T at(int r) {
        if (Root == nullptr || r > Root->Size)
            return T();
        Node *root = Root;
        while (root) {
            int ls = root->Left ? root->Left->Size : 0;
            if (ls + 1 == r) {
                break;
            } else if (ls + 1 > r) {
                root = root->Left;
            } else {
                r -= ls + 1;
                root = root->Right;
            }
        }
        return root->Key;
    }

    T previous(T key) {
        Node *x, *y, *root;
        T ans;
        split1(Root, key, x, y);
        root = x;
        if (root == nullptr)
            return -0x7fffffff;
        while (root->Right) root = root->Right;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    T next(T key) {
        Node *x, *y, *root;
        T ans;
        split2(Root, key, x, y);
        root = y;
        if (root == nullptr)
            return 0x7fffffff;
        while (root->Left) root = root->Left;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    int size() { return (Root ? Root->Size : 0); }

    bool find(T key) {
        Node *x, *y, *z;
        split2(Root, key, x, z);
        split1(x, key, x, y);
        bool ans;
        if (y)
            ans = true;
        else
            ans = false;
        Root = merge(merge(x, y), z);
        return ans;
    }

private:
    struct Node {
        T Key;
        Node *Left, *Right;
        int Size, Priority;

        Node(T key, int pri) : Key(key), Left(nullptr), Right(nullptr), Size(1), Priority(pri) {}
        ~Node() {
            if (Left)
                delete Left;
            if (Right)
                delete Right;
        }
    } * Root;
    int Seed;

    int random() { return Seed = int((Seed + 3) * 482711ll % 2147483647); }

    Node *create(T key) {
        Node *root = new Node(key, random());
        return root;
    }

    void pushup(Node *root) {
        if (root)
            root->Size = (root->Left ? root->Left->Size : 0) + (root->Right ? root->Right->Size : 0) + 1;
    }

    void split1(Node *root, T key, Node *&x, Node *&y) {
        if (root == nullptr) {
            x = y = nullptr;
            return;
        }
        if (root->Key < key) {
            x = root;
            split1(root->Right, key, root->Right, y);
        } else {
            y = root;
            split1(root->Left, key, x, root->Left);
        }
        pushup(root);
    }

    void split2(Node *root, T key, Node *&x, Node *&y) {
        if (root == nullptr) {
            x = y = nullptr;
            return;
        }
        if (!(key < root->Key)) {
            x = root;
            split2(root->Right, key, root->Right, y);
        } else {
            y = root;
            split2(root->Left, key, x, root->Left);
        }
        pushup(root);
    }

    Node *merge(Node *x, Node *y) {
        if (x == nullptr)
            return y;
        if (y == nullptr)
            return x;
        if (x->Priority > y->Priority) {
            x->Right = merge(x->Right, y);
            pushup(x);
            return x;
        } else {
            y->Left = merge(x, y->Left);
            pushup(y);
            return y;
        }
    }
};