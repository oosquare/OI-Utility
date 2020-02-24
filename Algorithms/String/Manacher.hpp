#include <cstring>
using namespace std;

template <int Lim>
class Manacher
{
public:
	Manacher(){Length=0;}

	void insert(char c[]){
		int len=strlen(c);
    	Str[0]='~';
    	Str[++Length]='|';
    	for(int i=0;i<len;i++){ Str[++Length]=c; Str[++Length]='|'; }
	}

	int length(){
		int ans=0,rb=0,mid=0;
    	for(int i=1;i<=n;i++){
        	if(i<rb) p[i]=min(p[(mid<<1)-i],rb-i);
        	else p[i]=1;
        	while(s[i-p[i]]==s[i+p[i]]) p[i]++;
        	if(p[i]+i>rb){
            	rb=p[i]+i;
            	mid=i;
        	}
        	ans=max(ans,p[i]);
    	}
    	return ans-1;
	}

	int count(){
		int ans=0;
    	for(int i=0;i<n;i++) ans+=p[i]/2;
    	return ans;
	}
private:
	int Length;
	char Str[Lim<<1];
	int Radius[Lim<<1];
};