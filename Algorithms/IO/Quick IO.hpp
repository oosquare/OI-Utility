namespace IO
{
    char buf[1<<15],*fs,*ft;
    char out[1<<28],*fe=out;
    inline char getc(){
        return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++;
    }
    
    template <typename T>
    inline void read(T &x){
        x=0;
        bool f=false;
        char ch=getchar();
        while (!isdigit(ch) && ch^'-') ch=getchar();
        if (ch=='-') f=true, ch=getchar();
        while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
        if(f)
            x=-x;
        return;
    }

    
    inline void flush(){
        fwrite(out,1,fe-out,stdout);
        fe=out;
    }

    template <typename T>
    inline void writeln(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++='\n';
    }

    template <typename T>
    inline void writesp(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++=' ';
    }
}