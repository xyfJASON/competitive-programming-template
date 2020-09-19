#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 100005;

int n, m, opt, x, y;
LL c[N];

#define lid id<<1
#define rid id<<1|1
#define len(id) (tr[id].r - tr[id].l + 1)

struct segTree{
	int l, r;
	LL sum, lazy;
}tr[N<<2];

inline void pushup(int id){
	tr[id].sum = tr[lid].sum + tr[rid].sum;
}
inline void pushdown(int id){
	if(tr[id].lazy && tr[id].l != tr[id].r){
		tr[lid].lazy += tr[id].lazy;
		tr[lid].sum += len(lid) * tr[id].lazy;
		tr[rid].lazy += tr[id].lazy;
		tr[rid].sum += len(rid) * tr[id].lazy;
		tr[id].lazy = 0;
	}
}
void build(int id, int l, int r){
	tr[id].l = l, tr[id].r = r;
	if(tr[id].l == tr[id].r){
		tr[id].sum = c[l];
		tr[id].lazy = 0;
		return;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	build(lid, l, mid);
	build(rid, mid+1, r);
	pushup(id);
}
void add(int id, int l, int r, LL v){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r){
		tr[id].lazy += v;
		tr[id].sum += v * len(id);
		return;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(r <= mid)
		add(lid, l, r, v);
	else if(l > mid)
		add(rid, l, r, v);
	else{
		add(lid, l, mid, v);
		add(rid, mid+1, r, v);
	}
	pushup(id);
}
LL querySum(int id, int l, int r){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r)
		return tr[id].sum;
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(r <= mid)
		return querySum(lid, l, r);
	else if(l > mid)
		return querySum(rid, l, r);
	else
		return querySum(lid, l, mid) + querySum(rid, mid+1, r);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &c[i]);
	build(1, 1, n);
	while(m--){
		scanf("%d%d%d", &opt, &x, &y);
		if(opt == 1){
			scanf("%lld", &c[0]);
			add(1, x, y, c[0]);
		}
		else
			printf("%lld\n", querySum(1, x, y));
	}
	return 0;
}
