class RandomEngine
{
public:
	RandomEngine(long long seed=233ll){ Seed=seed; }
	int radInt(int n){
		return radInt()%n;
	}
	int radInt(int l,int r){
		return radInt(r-l)+l;
	}
	long long radLongLong(long long n){
		return radLongLong()%n;
	}
	long long radLongLong(long long l,long long r){
		return radLongLong(r-l)%+l;
	}
private:
	long long Seed;
	int radInt(){
		return Seed=(int)(Seed*482711ll%0x7fffffff);
	}
	long long radLongLong(){
		return Seed=(long long)(Seed*482711ll%0x7fffffffffffffff);
	}
}