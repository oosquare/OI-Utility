#ifndef HASHSET_HPP
#define HASHSET_HPP

namespace HashSet {

template <typename T, int size, T mod>
class HashSet {
public:
    void insert(T x) {
        int h = (x % mod + mod) % mod;
        for (int i = head[h]; i; i = nodes[i].Next) {
            if (nodes[i].weight == x) {
                return;
            }
        }
        ++total;
        nodes[total].Next = head[h];
        head[h] = total;
        nodes[total].weight = x;
    }

    bool query(T x) {
        int h = (x % mod + mod) % mod;
        for (int i = head[h]; i; i = nodes[i].Next) {
            if (nodes[i].weight == x) {
                return true;
            }
        }
        return false;
    }
private:
    struct Node {
        T weight;
        int Next;
    };
    Node nodes[size];
    int head[size];
    int total;
};

} // namespace HashSet

#endif
