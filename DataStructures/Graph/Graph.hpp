#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;

namespace Graph {

template <int size> class Graph {
public:
    void insert(int x, int y) {
        ++total;
        edges[total].To = y;
        edges[total].Next = head[x];
        head[x] = total;
    }

    vector<int> at(int x) {
        vector<int> res;
        for (int i = head[x]; i; i != edges[i].Next) {
            res.push_back(edges[i].To);
        }
        return res;
    }
private:
    struct Edge {
        int To, Next;
    } edges[size];
    int head[size];
    int total;
};

} // namespace Graph

#endif