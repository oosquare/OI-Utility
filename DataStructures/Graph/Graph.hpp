#include <vector>
using namespace std;

template <int Lim>
class Graph
{
public:
    void insert(int x,int y){
        ++Total;
        Edge[Total].To=y;
        Edge[Total].Next=Head[x];
        Head[x]=Total;
    }

    vector<int> at(int x){
        vector<int> res;
        for(int i=Head[x];i;i!=Edge[i].Next){
            res.push_back(Edge[i].To);
        }
        return res;
    }
private:
    struct Node
    {
        int To,Next;
    }Edge[Lim];
    int Head[Lim];
    int Total;
};