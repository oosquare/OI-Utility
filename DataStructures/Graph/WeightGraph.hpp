#include <vector>
using namespace std;

template <typename T,int Lim>
class WeightGraph
{
public:
    void insert(int x,int y,T w){
        ++Total;
        Edge[Total].To=y;
        Edge[Total].Weight=w;
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
        T Weight;
    }Edge[Lim];
    int Head[Lim];
    int Total;
};