#ifndef PERSISTENTFHQTREAP_HPP
#define PERSISTENTFHQTREAP_HPP

namespace PersistentFhqTreap {

template <typename T, int size> class PersistentFhqTreap 
{
public:
    PersistentFhqTreap() { seed = (int)(size * 565463ll % 2147483647); }

    void insert(T key, int present, int past) {
        root[present] = root[past];
        int x, y, z;
        split(root[present], key - 1, x, y);
        root[present] = merge(merge(x, create(key)), y);
    }

    void remove(T key, int present, int past) {
        root[present] = root[past];
        int x, y, z;
        split(root[present], key, x, z);
        split(x, key - 1, x, y);
        if(y) {
            y = merge(tree[y].left, tree[y].right);
        }
        root[present] = merge(merge(x, y), z);
    }

    int rank(T key, int present, int past) {
        root[present] = root[past];
        int x, y, ans;
        split(root[present], key - 1, x, y);
        ans = tree[x].size + 1;
        root[present] = merge(x, y);
        return ans;
    }

    T at(int r, int present, int past) {
        root[present] = root[past];
        int root = root[present];
        while (true) {
            if (tree[tree[root].left].size + 1 == r) {
                break;
            } else if (tree[tree[root].left].size + 1 > r) {
                root = tree[root].left;
            } else {
                r -= tree[tree[root].left].size + 1;
                root = tree[root].right;
            }
        }
        return tree[root].key;
    }

    T lower(T key, int present, int past) {
        root[present] = root[past];
        int x, y, root;
        T ans;
        split(root[present], key - 1, x, y);
        root = x;
        while (tree[root].right) root = tree[root].right;
        ans = tree[root].key;
        root[present] = merge(x, y);
        return ans;
    }

    T upper(T key, int present, int past) {
        root[present] = root[past];
        int x, y, root;
        T ans;
        split(root[present], key, x, y);
        root = y;
        while (tree[root].left) root = tree[root].left;
        ans = tree[root].key;
        root[present] = merge(x, y);
        return ans;
    }

    bool find(T key, int present) {
        int x, y, z;
        split(root[present], key, x, z);
        split(x, key - 1, x, y);
        bool ans;
        if(tree[y].size) ans = true;
        else ans = false;
        root[present] = merge(merge(x, y), z);
        return ans;
    }

private:
    struct Node {
        T key;
        int left, right, size, priority;
    } tree[size * 50 + 10];
    int seed, total, root[size];

    int rad() { return seed = int(seed * 482711ll % 2147483647); }

    int create(int key) {
        int root = ++total;
        tree[root].key = key;
        tree[root].size = 1;
        tree[root].left = tree[root].right = 0;
        tree[root].priority = rad();
        return root;
    }

    int copy(int root) {
        int newroot = ++total;
        tree[newroot] = tree[root];
        return newroot;
    }

    void pushup(int root) {
        if(root != 0)
            tree[root].size = tree[tree[root].left].size + tree[tree[root].right].size + 1; 
    }

    void split(int root, int key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (tree[root].key <= key) {
            x = copy(root);
            split(tree[x].right, key, tree[x].right, y);
            pushup(x);
        } else {
            y = copy(root);
            split(tree[y].left, key, x, tree[y].left);
            pushup(y);
        }
        
        
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0)
            return x + y;
        if (tree[x].priority > tree[y].priority) {
            int z = copy(x);
            tree[z].right = merge(tree[z].right, y);
            pushup(z);
            return z;
        } else {
            int z = copy(y);
            tree[z].left = merge(x, tree[z].left);
            pushup(z);
            return z;
        }
    }
};

} // namespace PersistentFhqTreap

#endif