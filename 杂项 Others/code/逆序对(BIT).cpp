#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 500005;

int n, a[N], t[N], c[N];
LL cnt;

inline int lowbit(int x){
    return x & -x;
}
void add(int x, int v){
    while(x <= n){
        c[x] += v;
        x += lowbit(x);
    }
}
LL querySum(int x){
    LL res = 0;
    while(x){
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        t[i] = a[i];
    }
    sort(t+1, t+n+1);
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(t+1, t+n+1, a[i]) - t;
    for(int i = n; i >= 1; i--){
        cnt += querySum(a[i]-1);
        add(a[i], 1);
    }
    printf("%lld\n", cnt);
    return 0;
}
