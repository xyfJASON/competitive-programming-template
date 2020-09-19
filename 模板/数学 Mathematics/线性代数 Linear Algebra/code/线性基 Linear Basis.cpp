#include<algorithm>
#include<cstdio>

using namespace std;

typedef long long LL;

int n;
LL a;

LL p[70];
inline bool insert(LL x){
    for(int i = 62; i >= 0; i--){
        if((x >> i) == 0)   continue;
        if(!p[i]){ p[i] = x; return true; }
        else    x ^= p[i];
    }
    return false;
}
inline void norm(){
    for(int i = 62; i >= 0; i--)
        if(p[i])
            for(int j = 62; j > i; j--)
                if((p[j] >> i) & 1)
                    p[j] ^= p[i];
}
inline bool exist(LL x){
    for(int i = 62; i >= 0; i--){
        if((x >> i) == 0)   continue;
        if(!p[i])   return false;
        else    x ^= p[i];
    }
    return true;
}
inline LL xorMax(){
    LL res = 0;
    for(int i = 62; i >= 0; i--)
        res = max(res, res ^ p[i]);
    return res;
}
inline LL xorMin(){
    for(int i = 0; i <= 62; i++)
        if(p[i])    return p[i];
    return 0;
}
inline LL kthMin(LL k){ // kth minimum number (excluding 0)
    LL res = 0;
    vector<LL> tmp;
    for(int i = 0; i <= 62; i++)
        if(p[i])    tmp.push_back(p[i]);
    if(k >= (1ll << tmp.size()))    return -1;
    for(int i = tmp.size() - 1; i >= 0; i--)
        if((k >> i) & 1)    res ^= tmp[i];
    return res;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a);
        insert(a);
    }
    printf("%lld\n", xorMax());
    return 0;
}