template <typename T,int Lim>
class HashSet
{
public:
    void insert(T x){
        int h=(x%mod+mod)%mod;
        for(int i=Head[h];i;i=Set[i].Next){
            if(Set[i].Weight==x){
                return;
            }
        }
        ++Total;
        Set[Total].Next=Head[h];
        Head[h]=Total;
        Set[Total].Weight=x;
    }

    bool query(T x){
        int h=(x%mod+mod)%mod;
        for(int i=Head[h];i;i=Set[i].Next){
            if(Set[i].Weight==x){
                return true;
            }
        }
        return false;
    }
private:
    struct Node
    {
        T Weight;
        int Next;
    };
    Node Set[Lim];
    int Head[Lim];
    int Top;
    int Total;
};

