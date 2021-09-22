#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

namespace SegmentTree {

template <typename T, int size> class SegmentTree {
public:
    void init(int n) { length = n; }

    void build(T arr[]) { build(1, 1, length, arr); }

    void modify(int left, int right, T key) { modify(1, 1, length, left, right, key); }

    T query(int left, int right) { return query(1, 1, length, left, right); }

private:
    struct Node {
        T add, sum;
    } tree[size];
    int length;

    void pushup(int root) { tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum; }

    void update(int root, int left, int right, T key) {
        tree[root].add += key;
        tree[root].sum += key * (right - left + 1);
    }

    void pushdown(int root, int left, int right) {
        if (tree[root].add == 0)
            return;
        int mid = left + right >> 1;
        update(root << 1, left, mid, tree[root].add);
        update(root << 1 | 1, mid + 1, right, tree[root].add);
        tree[root].add = 0;
    }

    void build(int root, int left, int right, T arr[]) {
        if (left == right) {
            tree[root].sum = arr[left];
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
        if (mid < mright)
            modify(root << 1 | 1, mid + 1, right, mleft, mright, key);
        pushup(root);
    }

    T query(int root, int left, int right, int qleft, int qright) {
        if (qleft <= left && right <= qright)
            return tree[root].sum;
        int mid = left + right >> 1;
        pushdown(root, left, right);
        T res = 0;
        if (qleft <= mid)
            res += query(root << 1, left, mid, qleft, qright);
        if (mid < qright)
            res += query(root << 1 | 1, mid + 1, right, qleft, qright);
        return res;
    }
};

} // namespace SegmentTree

#endif