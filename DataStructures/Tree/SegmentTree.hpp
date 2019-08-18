#include <vector>
using namespace std;

template<typename T>
class SegmentTree
{
public:
    SegmentTree(){}
    SegmentTree(int size):Tree(size){}
    SegmentTree(const vector<T>& container){
        build(container);
    }
    ~SegmentTree(){};

public:
    void build(const vector<T>& container){
        Tree.clear();
        Size=container.size();
        Tree.assign(Node(),Size+1);
        build(container,1,0,Size-1);
    }

    T at(int key){
        return query(1,1,Size,key,key);
    }

    T sum(int lkey,int r,key){
        return query(1,1,Size,lkey,rkey);
    }

    void insert(int key,T val){
        modifyPlus(-at(key)+val);
    }

    void plus(int key,T val){
        modifyPlus(key,val);
    }

    void minus(int key,T val){
        modifyPlus(key,-val);
    }

    void multi(int key,T val){
        modifyMult(key,val);
    }

    void divide(int key,T val){
        modifyMult(key,1/val);
    }
private:
    struct Node
    {
        T Value,Plus,Mult;
    };
    vector<Node> Tree;
    int Size;

private:
    void pushUp(int k){
        Tree[k].Value=Tree[k<<1].Value+Tree[k<<1|1].Value;
    }

    void pushDown(int k,int l,int r){
        if(Tree[k].Mult!=1){
            Tree[k<<1].Plus=Tree[k<<1].Plus*Tree[k].Mult;
            Tree[k<<1|1].Plus=Tree[k<<1|1].Plus*Tree[k].Mult;
            Tree[k<<1].Mult=Tree[k].Mult*Tree[k<<1].Mult;
            Tree[k<<1|1].Mult=Tree[k].Mult*Tree[k<<1|1].Mult;
            Tree[k<<1].Value=Tree[k<<1].Value*Tree[k].Mult;
            Tree[k<<1|1].Value=Tree[k<<1|1].Value*Tree[k].Mult;
        }
        if(Tree[k].Plus!=0){
            int mid=(l+r)>>1;
            int llen=mid-l+1;
            int rlen=r-mid;
            Tree[k<<1].Plus=Tree[k<<1].Plus+Tree[k].Plus;
            Tree[k<<1|1].Plus=Tree[k<<1|1].Plus+Tree[k].Plus;
            Tree[k<<1].Value=Tree[k<<1].Value+Tree[k].Plus*llen;
            Tree[k<<1|1].Value=Tree[k<<1|1].Value+Tree[k].Plus*rlen;
        }
        Tree[k].Plus=0;
        Tree[k].Mult=1;
    }

    void build(const vector<T>& a,int k,int l,int r){
        Tree[k].Plus=0;
        Tree[k].Mult=1;
        if(l==r){
            Tree[k].Value=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        pushUp(k);
    }

    void modifyPlus(int k,int l,int r,int x,int y,T v){
        if(x<=l&&r<=y){
            Tree[k].Value+=v*(r-l+1);
            Tree[k].Plus+=v;
            return;
        }
        int mid=(l+r)>>1;
        pushDown(k,l,r);
        if(x<=mid)modifyPlus(k<<1,l,mid,x,y,v);
        if(mid<y)modifyPlus(k<<1|1,mid+1,r,x,y,v);
        pushUp(k);
    }

    void modifyMult(int k,int l,int r,int x,int y,T v){
        if(x<=l&&r<=y){
            Tree[k].Value*=v;
            Tree[k].Plus*=v;
            Tree[k].Mult*=v;
            return;
        }
        int mid=(l+r)>>1;
        pushDown(k,l,r);
        if(x<=mid)modifyMult(k<<1,l,mid,x,y,v);
        if(mid<y)modifyMult(k<<1|1,mid+1,r,x,y,v);
        pushUp(k);
    }

    T query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y)return Tree[k].v;
        int mid=(l+r)>>1;
        pushDown(k,l,r);
        T res=0;
        if(x<=mid)res+=query(k<<1,l,mid,x,y;
        if(mid<y)res+=query(k<<1|1,mid+1,r,x,y);
        return res;
    }
};
