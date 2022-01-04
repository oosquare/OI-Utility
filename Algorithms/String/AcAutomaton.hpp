#ifndef ACAUTOMATION_HPP
#define ACAUTOMATION_HPP

namespace AcAutomaton {

#include <queue>
#include <cstring>
using namespace std;

template <int size> class AcAutomaton {
public:
    AcAutomaton() {
        this->clear();
    }

    int insert(char s[]) {
        int len = strlen(s), u = 1;
        for (register int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            if (!trie[u].next[c]) {
                trie[u].next[c] = ++total;
            }
            u = trie[u].next[c];
        }
        trie[u].end++;
        return u;
    }

    void process() {
        queue<int> q;
        for (register int i = 0; i < 26; i++) {
            trie[0].next[i] = 1;
        }
        q.push(1);
        trie[1].fail = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (!trie[u].next[i]) {
                    trie[u].next[i] = trie[trie[u].fail].next[i];
                } else {
                    q.push(trie[u].next[i]);
                    int v = trie[u].fail;
                    trie[trie[u].next[i]].fail = trie[v].next[i];
                }
            }
        }
    }

    int match(char s[]) {
        int len = strlen(s), u = 1, ans = 0;
        for (register int i = 0; i <= len; i++) {
            int c = s[i] - 'a';
            int k = trie[u].next[c];
            while (k > 1 && trie[k].end) {
                ans += trie[k].end;
                trie[k].end = 0;
                k = trie[k].fail;
            }
            u = trie[u].next[c];
        }
        return ans;
    }

    void clear() {
        memset(trie, 0, sizeof(trie));
        for (register int i = 0; i < 26; i++) {
            trie[0].next[i] = 1;
            trie[1].next[i] = 0;
        }
        total = 1;
    }
private:
    struct Node {
        int end;
        int fail;
        int next[26];
    };
    Node trie[size];
    int total;
};

} // namespace AcAutomation

#endif