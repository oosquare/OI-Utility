#include <string>
#include <queue>
#include <cstring>
using namespace std;

class ACAutomaton
{
public:
    void insert(string s){
        int len=s.length(),u=1;
        for(int i=0;i<len;i++){
            int c=s[i]-'a';
            if(!Trie[u].Next[c]){
                Trie[u].Next[c]=++Total;
            }
            u=Trie[u].Next[c];
        }
        Trie[u].End=true;
    }

    void process(){
        queue<int> q;
        for(int i=0;i<26;i++){
            Trie[0].Next[i]=1;
        }
        q.push(1);
        Trie[1].Fail=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(!Trie[u].Next[i]){
                    Trie[u].Next[i]=Trie[Trie[u].Fail].Next[i];
                }else{
                    q.push(Trie[u].Next[i]);
                    int v=Trie[u].Fail;
                    Trie[Trie[u].Next[i]].Fail=Trie[v].Next[i];
                }
            }
        }
    }

    int match(string s){
        int len=s.length(),u=1,ans=0;
        for(int i=0;i<=len;i++){
            int c=s[i]-'a';
            int k=Trie[u].Next[c];
            while(k>1){
                ans+=Trie[k].End;
                Trie[k].End=false;
                
                k=Trie[k].Fail;
            }
            u=Trie[u].Next[c];
        }
        return ans;
    }

    void clear(){
        memset(Trie,0,sizeof(Trie));
        for(int i=0;i<26;i++){
            Trie[0].Next[i]=1;
            Trie[1].Next[i]=0;
        }
        Total=1;
    }
private:
    const int Lim=1e6;
    struct Node
    {
        bool End;
        int Fail;
        int Next[26];
    };
    Node Trie[Lim];
    int Total;
};
