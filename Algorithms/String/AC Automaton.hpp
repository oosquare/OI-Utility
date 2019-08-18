#include <cstdio>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

const int Lim=1e6+10;

class ACAutomaton
{
public:
    ACAutomaton(){
        this->clear();
    }
    
    int insert(char s[]){
        int len=strlen(s),u=1;
        for(register int i=0;i<len;i++){
            int c=s[i]-'a';
            if(!Trie[u].Next[c]){
                Trie[u].Next[c]=++Total;
            }
            u=Trie[u].Next[c];
        }
        Trie[u].End++;
        return u;
    }

    void process(){
        queue<int> q;
        for(register int i=0;i<26;i++){
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

    int match(char s[]){
        int len=strlen(s),u=1,ans=0;
        for(register int i=0;i<=len;i++){
            int c=s[i]-'a';
            int k=Trie[u].Next[c];
            while(k>1&&Trie[k].End){
                ans+=Trie[k].End;
                Trie[k].End=0;
                k=Trie[k].Fail;
            }
            u=Trie[u].Next[c];
        }
        return ans;
    }

    void clear(){
        memset(Trie,0,sizeof(Trie));
        for(register int i=0;i<26;i++){
            Trie[0].Next[i]=1;
            Trie[1].Next[i]=0;
        }
        Total=1;
    }
private:
    struct Node
    {
        int End;
        int Fail;
        int Next[26];
    };
    Node Trie[Lim];
    int Total;
};