#include<algorithm>
#include<cstdio>

using namespace std;

template<typename T>void read(T&x){x=0;int fl=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')
fl=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}x*=fl;}
template<typename T,typename...Args>inline void read(T&t,Args&...args){read(t);read(args...);}

const int N = 50005;

int T, q, a[N], tot, ans[N];

#define LEFT 0
#define RIGHT 1
struct Node{
    int t, x, y, z, k;
    bool mark;
}node[N<<3];
bool cmpt(const Node &A, const Node &B){
    if(A.t == B.t) if(A.x == B.x) if(A.y == B.y) return A.z < B.z;
    else return A.y < B.y; else return A.x < B.x; else return A.t < B.t;
}

int t[N<<3];
void disc(){
    sort(t+1, t+t[0]+1);
    t[0] = unique(t+1, t+t[0]+1) - (t+1);
    for(int i = 1; i <= tot; i++)
        node[i].z = lower_bound(t+1, t+t[0]+1, node[i].z) - t;
}

int c[N<<3];
inline int lowbit(int x){ return x & -x; }
inline void add(int x, int val){ while(x <= q * 8){ c[x] += val; x += lowbit(x); } }
inline int sum(int x){ int res = 0; while(x){ res += c[x]; x -= lowbit(x); } return res; }

Node tmp[N<<3], tmp2[N<<3];
void cdq2(int l, int r){
    if(l == r)  return;
    int mid = (l + r) >> 1;
    cdq2(l, mid), cdq2(mid+1, r);
    int ptl = l, ptr = mid+1, tid = l-1, lastl;
    while(ptl <= mid && ptr <= r){
        if(tmp[ptl].y <= tmp[ptr].y){
            if(tmp[ptl].k == 0 && tmp[ptl].mark == LEFT)
                add(tmp[ptl].z, 1);
            tmp2[++tid] = tmp[ptl++];
        }
        else{
            if(tmp[ptr].k != 0 && tmp[ptr].mark == RIGHT)
                ans[tmp[ptr].t] += tmp[ptr].k * sum(tmp[ptr].z);
            tmp2[++tid] = tmp[ptr++];
        }
    }
    lastl = ptl - 1;
    while(ptl <= mid)   tmp2[++tid] = tmp[ptl++];
    while(ptr <= r){
        if(tmp[ptr].k != 0 && tmp[ptr].mark == RIGHT)
            ans[tmp[ptr].t] += tmp[ptr].k * sum(tmp[ptr].z);
        tmp2[++tid] = tmp[ptr++];
    }
    for(int i = l; i <= lastl; i++) // crucial for decreasing constant
        if(tmp[i].k == 0 && tmp[i].mark == LEFT)
            add(tmp[i].z, -1);
    for(int i = l; i <= r; i++) tmp[i] = tmp2[i];
}
void cdq1(int l, int r){
    if(l == r)  return;
    int mid = (l + r) >> 1;
    cdq1(l, mid), cdq1(mid+1, r);
    int ptl = l, ptr = mid+1, tid = l-1; // tid must be l-1 or it can't be used in cdq2
    while(ptl <= mid && ptr <= r){
        if(node[ptl].x <= node[ptr].x){
            node[ptl].mark = LEFT;
            tmp[++tid] = node[ptl++];
        }
        else{
            node[ptr].mark = RIGHT;
            tmp[++tid] = node[ptr++];
        }
    }
    while(ptl <= mid)   node[ptl].mark = LEFT, tmp[++tid] = node[ptl++];
    while(ptr <= r)     node[ptr].mark = RIGHT, tmp[++tid] = node[ptr++];
    for(int i = l; i <= r; i++)   node[i] = tmp[i];
    cdq2(l, r);
}

inline void init(){
    tot = t[0] = 0;
    for(int i = 1; i <= q; i++) ans[i] = 0;
}

int main(){
    read(T);
    while(T--){
        read(q);
        init();
        int _x1, _y1, _z1, _x2, _y2, _z2;
        for(int i = 1; i <= q; i++){
            read(a[i], _x1, _y1, _z1);
            if(a[i] == 1){
                node[++tot] = (Node){i, _x1, _y1, _z1, 0};
                t[++t[0]] = _z1;
            }
            else{
                read(_x2, _y2, _z2);
                node[++tot] = (Node){i, _x2, _y2, _z2, 1};
                node[++tot] = (Node){i, _x1-1, _y2, _z2, -1};
                node[++tot] = (Node){i, _x2, _y1-1, _z2, -1};
                node[++tot] = (Node){i, _x2, _y2, _z1-1, -1};
                node[++tot] = (Node){i, _x1-1, _y1-1, _z2, 1};
                node[++tot] = (Node){i, _x1-1, _y2, _z1-1, 1};
                node[++tot] = (Node){i, _x2, _y1-1, _z1-1, 1};
                node[++tot] = (Node){i, _x1-1, _y1-1, _z1-1, -1};
                t[++t[0]] = _z2, t[++t[0]] = _z1-1;
            }
        }
        disc();
        sort(node+1, node+tot+1, cmpt);
        cdq1(1, tot);
        for(int i = 1; i <= q; i++)
            if(a[i] == 2)
                printf("%d\n", ans[i]);
    }
    return 0;
}
