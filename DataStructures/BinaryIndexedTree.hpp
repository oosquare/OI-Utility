const int Lim=10000;

template<typename T>
class BinaryIndexedTree
{
public:
	BinaryIndexedTree(int n):N(n){}
	int size(){
		return N;
	}
	void modify(int pos,T val){
		for(;pos<=N;pos+=lowbit(pos)){
			Array[pos]+=val;
		}
	}
	T query(int pos){
		T ans=T(0);
		for(;pos;pos-=lowbit(pos)){
			ans+=Array[pos];
		}
		return ans;
	}
	T query(int left,int right){
		return query(right)-query(left-1);
	}
private:
	T Array[Lim];
	int N;
	T lowbit(T x){
		return x&-x;
	}
};
