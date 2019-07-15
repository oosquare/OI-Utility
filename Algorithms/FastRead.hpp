#include <cstdio>
using namespace std;

template<typename T>
T read(){
	T x=0,f=1;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-f;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return x*f;
}
