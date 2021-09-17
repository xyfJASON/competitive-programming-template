#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 100005;
const int K = 200005;

int n, k, tot, ans[N];
struct Node{
    int a, b, c, dc;    // dc is c after discretization
    int newid, cnt, num; // num is the number of elements which are less than this node
}node[N];
bool cmpa(const Node &A, const Node &B){
    return A.a == B.a ? (A.b == B.b ? A.c < B.c : A.b < B.b) : A.a < B.a;
}
bool cmpb(const Node &A, const Node &B){
    return A.b == B.b ? (A.c == B.c ? A.a < B.a : A.c < B.c) : A.b < B.b;
}

int tc[N];
void disc(){
    sort(tc+1, tc+tc[0]+1);
    tc[0] = unique(tc+1, tc+tc[0]+1) - (tc+1);
    for(int i = 1; i <= n; i++)
        node[i].dc = lower_bound(tc+1, tc+tc[0]+1, node[i].c) - tc;
}

int c[N];
inline int lowbit(int x){ return x & -x; }
void add(int x, int val){ while(x <= n){ c[x] += val; x += lowbit(x); } }
int sum(int x){
    int res = 0;
    while(x){ res += c[x]; x -= lowbit(x); }
    return res;
}

void cdq(int l, int r){
    if(l == r)  return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid+1, r);
    sort(node+l, node+r+1, cmpb);
    for(int i = l; i <= r; i++){
        if(node[i].newid <= mid)    add(node[i].dc, node[i].cnt);
        else    node[i].num += sum(node[i].dc);
    }
    for(int i = l; i <= r; i++)         // clear BIT
        if(node[i].newid <= mid)
            add(node[i].dc, -node[i].cnt);
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d%d%d", &node[i].a, &node[i].b, &node[i].c);
        tc[++tc[0]] = node[i].c;
    }
    disc();
    sort(node+1, node+n+1, cmpa);
    for(int i = 1; i <= n; i++){ // unique
        if(node[i-1].a != node[i].a || node[i-1].b != node[i].b || node[i-1].c != node[i].c)
            node[++tot] = node[i], node[tot].newid = tot, node[tot].cnt = 1;
        else    node[tot].cnt++;
    }
    cdq(1, tot);
    for(int i = 1; i <= tot; i++)   ans[node[i].num + node[i].cnt - 1] += node[i].cnt;
    for(int i = 0; i < n; i++)  printf("%d\n", ans[i]);
    return 0;
}
