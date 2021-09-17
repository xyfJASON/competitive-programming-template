#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 500005;

int n, a[N], t[N], id;
LL cnt;

void mergesort(int l, int r){
    if(l >= r)	return;
    int mid = (l + r) >> 1;
    mergesort(l, mid);
    mergesort(mid+1, r);
    id = 0;
    int lpt = l, rpt = mid+1;
    while(lpt <= mid && rpt <= r){
        if(a[lpt] <= a[rpt])
            t[++id] = a[lpt++];
        else{
            t[++id] = a[rpt++];
            cnt += 1ll * mid - lpt + 1;
        }
    }
    while(lpt <= mid)
        t[++id] = a[lpt++];
    while(rpt <= r)
        t[++id] = a[rpt++];
    for(int i = l; i <= r; i++)
        a[i] = t[i - l + 1];
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    mergesort(1, n);
    printf("%lld\n", cnt);
    return 0;
}
