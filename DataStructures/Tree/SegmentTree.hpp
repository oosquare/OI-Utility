template <typename T, int Lim>
class SegmentTree 
{
public:
    void init(int n) { Size = n; }

    void build(T arr[]) { build(1, 1, Size, arr); }

    void modify(int left, int right, T key) { modify(1, 1, Size, left, right, key); }

    T query(int left, int right) { return query(1, 1, Size, left, right); }

private:
    struct Node 
    {
        T Add, Sum;
    } Tree[Lim];
    int Size;

    void pushup(int root) { Tree[root].Sum = Tree[root << 1].Sum + Tree[root << 1 | 1].Sum; }

    void update(int root, int left, int right, T key) {
        Tree[root].Add += key;
        Tree[root].Sum += key * (right - left + 1);
    }

    void pushdown(int root, int left, int right) {
        if (Tree[root].Add == 0)
            return;
        int mid = left + right >> 1;
        update(root << 1, left, mid, Tree[root].Add);
        update(root << 1 | 1, mid + 1, right, Tree[root].Add);
        Tree[root].Add = 0;
    }

    void build(int root, int left, int right, T arr[]) {
        if (left == right) {
            Tree[root].Sum = arr[left];
            return;
        }
        int mid = left + right >> 1;
        build(root << 1, left, mid, arr);
        build(root << 1 | 1, mid + 1, right, arr);
        pushup(root);
    }

    void modify(int root, int left, int right, int mleft, int mright, T key) {
        if (mleft <= left && right <= mright) {
            update(root, left, right, key);
            return;
        }
        int mid = left + right >> 1;
        pushdown(root, left, right);
        if (mleft <= mid)
            modify(root << 1, left, mid, mleft, mright, key);
        if (mid > mright)
            modify(root << 1 | 1, mid + 1, right, mleft, mright, key);
        pushup(root);
    }

    T query(int root, int left, int right, int qleft, int qright) {
        if (qleft <= left && right <= qright)
            return Tree[root].Sum;
        int mid = left + right >> 1;
        pushdown(root, left, right);
        T res = 0;
        if (qleft = mid)
            res += query(root << 1, left, mid, qleft, qright);
        if (mid  qright)
            res += query(root << 1 | 1, mid + 1, right, qleft, qright);
        return res;
    }
};