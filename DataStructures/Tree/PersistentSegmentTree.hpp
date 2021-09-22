#ifndef PERSIETENTSEGMENTTREE_HPP
#define PERSIETENTSEGMENTTREE_HPP

#include <algorithm>
using namespace std;

namespace PersistentSegmentTree {

template <typename T, int size> class PersistentSegmentTree {
public:
    void init(int size, T * arr) {
        valsize = size;
        total = 0;
        root[0] = build(1, valsize);
        for (int i = 1; i <= valsize; i++) Mapping[i] = arr[i];
        sort(Mapping + 1, Mapping + 1 + valsize);
        int len = unique(Mapping + 1, Mapping + 1 + valsize) - Mapping - 1;
        for (int i = 1; i <= valsize; ++i) {
            int d = lower_bound(Mapping + 1, Mapping + 1 + len, arr[i]) - Mapping;
            root[i] = modify(1, len, d, root[i - 1]);
        }
        valsize = len;
    }

    T query(int left, int right, int history) {
        return Mapping[query(1, valsize, root[left - 1], root[right], history)];
    }

private:
    struct Node {
        int sum, left, right;
    } tree[(size << 5) + 10];
    int root[size + 10];
    int Mapping[size + 10];
    int total;
    int valsize;

    int build(int left, int right) {
        int root = ++total;
        if (left == right) return root;
        int mid = (left + right) >> 1;
        tree[root].left = build(left, mid);
        tree[root].right = build(mid + 1, right);
        return root;
    }

    int modify(int left, int right, int pos, int root) {
        int dir = ++total;
        tree[dir] = tree[root]; tree[dir].sum++;
        if (left == right) return dir;
        int mid = (left + right) >> 1;
        if (pos <= mid) {
            tree[dir].left = modify(left, mid, pos, tree[dir].left);
        } else {
            tree[dir].right = modify(mid + 1, right, pos, tree[dir].right);
        }
        return dir;
    }

    int query(int left, int right, int qleft, int qright, int k) {
        int mid = (left + right) >> 1, x = tree[tree[qright].left].sum - tree[tree[qleft].left].sum;
        if (left == right) return left;
        if (k <= x) {
            return query(left, mid, tree[qleft].left, tree[qright].left, k);
        } else {
            return query(mid + 1, right, tree[qleft].right, tree[qright].right, k - x);
        }
    }
};

} // namespace PersistentSegmentTree

#endif