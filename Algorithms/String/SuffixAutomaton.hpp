#ifndef SUFFIXAUTOMATON_HPP
#define SUFFIXAUTOMATON_HPP

namespace SuffixAutomaton {

template <int maxSize> class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, len, pos;
        bool clone;

        Node() : link(0), len(0), pos(0), clone(false) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() : uuid(1), last(1) {}

    int size() {
        return uuid;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char c, int pos) {
        int x = create(), p = last, w = c - 'a';
        last = x;
        nodes[x].len = nodes[p].len + 1;
        nodes[x].pos = pos;

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].clone = true;
                nodes[nq].len = nodes[p].len + 1;
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i], i);
    }

private:
    Node nodes[maxSize * 2];
    int uuid, last;

    int create(int id = -1) {
        nodes[++uuid] = (id == -1 ? Node() : nodes[id]);
        return uuid;
    }
};

} // namespace SuffixAutomaton

#endif