template <int Lim>
class UnionFindSet
{
public:
	void clear(int n){
		for(int i=0;i<=n;i++){
			Father[i]=i;
		}
	}

	void query(int x){
		if(x==Father[x]){
			return x;
		}else{
			return Father[x]=query(Father[x]);
		}
	}

	void merge(int x,int y){
		x=query(x);
		y=query(y);
		if(x!=y){
			Father[y]=x;
		}
	}
private:
	int Father[Lim];
}