#include <algorithm>
using namespace std;

template <typename T,int Lim>
class PersistentSegmentTree
{
public:
    void init(int size,T * arr){
        Size=size;
        Total=0;
        Root[0]=build(1,Size);
        for(int i=1;i<=Size;i++) Mapping[i]=arr[i];
        sort(Mapping+1,Mapping+1+Size);
        int len=unique(Mapping+1,Mapping+1+Size)-Mapping-1;
        for(int i=1;i<=Size;++i){
            int d=lower_bound(Mapping+1,Mapping+1+len,arr[i])-Mapping;
            Root[i]=modify(1,len,d,Root[i-1]);
        }
        Size=len;
    }

    T query(int left,int right,int history){
        return Mapping[query(1,Size,Root[left-1],Root[right],history)];
    }

private:
    struct Node
    {
        int Sum,Left,Right;
    }Tree[(Lim<<5)+10];
    int Root[Lim+10];
    int Mapping[Lim+10];
    int Total;
    int Size;

    int build(int left,int right){
        int root=++Total;
        if(left==right) return root;
        int mid=(left+right)>>1;
        Tree[root].Left=build(left,mid);
        Tree[root].Right=build(mid+1,right);
        return root;
    }   

    int modify(int left,int right,int pos,int root){
        int dir=++Total;
        Tree[dir]=Tree[root]; Tree[dir].Sum++;
        if(left==right) return dir;
        int mid=(left+right)>>1;
        if(pos<=mid){
            Tree[dir].Left=modify(left,mid,pos,Tree[dir].Left);
        }else{
            Tree[dir].Right=modify(mid+1,right,pos,Tree[dir].Right);
        }
        return dir;
    }

    int query(int left,int right,int qleft,int qright,int k){
        int mid=(left+right)>>1,x=Tree[Tree[qright].Left].Sum-Tree[Tree[qleft].Left].Sum;
        if(left==right) return left;
        if(k<=x){
            return query(left,mid,Tree[qleft].Left,Tree[qright].Left,k);
        }else{
            return query(mid+1,right,Tree[qleft].Right,Tree[qright].Right,k-x);
        }
    }
};