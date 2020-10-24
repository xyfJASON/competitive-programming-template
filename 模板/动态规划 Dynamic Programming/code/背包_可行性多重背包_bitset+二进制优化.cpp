#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>

using namespace std;

template<typename T>void read(T&x){x=0;int fl=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')
fl=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}x*=fl;}
template<typename T,typename...Args>inline void read(T&t,Args&...args){read(t);read(args...);}

typedef long long LL;

const int N = 105;
const int M = 100005;

int n, m, a[N], c[N];
bitset<M> dp;
bitset<M> mask;

int main(){
    while(1){
        read(n, m);
        if(!n && !m)    break;
        for(int i = 1; i <= n; i++) read(a[i]);
        for(int i = 1; i <= n; i++) read(c[i]);
        dp.reset(), dp.set(0);
        for(int i = 1; i <= n; i++){
            for(int p = 1; p <= c[i]; c[i] -= p, p <<= 1)
                dp |= dp << (p * a[i]);
            dp |= dp << (c[i] * a[i]);
        }
        mask.reset();
        for(int i = 0; i <= m; i++) mask.set(i);
        dp &= mask;
        printf("%d\n", (int)dp.count() - 1);
    }
    return 0;
}