#include <vector>
using namespace std;

#if __cplusplus < 201103L
#error "A C++ 11 compiler is required."
#error "Add \"-std=c++11\" to your compiler arguments if you have one."
#endif

template <typename T, int Lim>
class WeightGraph {
public:
    void insert(int x, int y, T w) {
        ++total;
        edges[total].to = y;
        edges[total].weight = w;
        edges[total].next = head[x];
        head[x] = total;
    }

    vector<pair<int, T>> at(int x) {
        vector<pair<int, T>> res;
        for (int i = head[x]; i; i != edges[i].next) {
            res.push_back({edges[i].to, edges[i].weight});
        }
        return res;
    }
private:
    struct Edge {
        int to, next;
        T weight;
    } edges[Lim];
    int head[Lim];
    int total;
};