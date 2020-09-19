#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 100005;
int n, m, opt, x, y;
LL c[N], k, p;

#define lid id<<1
#define rid id<<1|1
#define len(id) (tr[id].r - tr[id].l + 1)
#define mid ((tr[id].l + tr[id].r) >> 1)
struct segTree{
	int l, r;
	LL sum, add, mul;
}tr[N<<2];
inline void pushup(int id){
	tr[id].sum = tr[lid].sum + tr[rid].sum;
}
inline void pushdown(int id){
	if(tr[id].mul != 1 && tr[id].l != tr[id].r){
		(tr[lid].mul *= tr[id].mul) %= p;
		(tr[lid].add *= tr[id].mul) %= p;
		(tr[lid].sum *= tr[id].mul) %= p;
		(tr[rid].mul *= tr[id].mul) %= p;
		(tr[rid].add *= tr[id].mul) %= p;
		(tr[rid].sum *= tr[id].mul) %= p;
		tr[id].mul = 1;
	}
	if(tr[id].add != 0 && tr[id].l != tr[id].r){
		(tr[lid].add += tr[id].add) %= p;
		(tr[lid].sum += len(lid) * tr[id].add % p) %= p;
		(tr[rid].add += tr[id].add) %= p;
		(tr[rid].sum += len(rid) * tr[id].add % p) %= p;
		tr[id].add = 0;
	}
}
void build(int id, int l, int r){
	tr[id].l = l; tr[id].r = r;
	tr[id].sum = tr[id].add = 0;
	tr[id].mul = 1;
	if(tr[id].l == tr[id].r){
		tr[id].sum = c[l] % p;
		return;
	}
	build(lid, l, mid);
	build(rid, mid+1, r);
	pushup(id);
}
void add(int id, int l, int r, LL v){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r){
		(tr[id].add += v) %= p;
		(tr[id].sum += len(id) * v % p) %= p;
		return;
	}
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
void mul(int id, int l, int r, LL v){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r){
		(tr[id].mul *= v) %= p;
		(tr[id].add *= v) %= p;
		(tr[id].sum *= v) %= p;
		return;
	}
	if(r <= mid)
		mul(lid, l, r, v);
	else if(l > mid)
		mul(rid, l, r, v);
	else{
		mul(lid, l, mid, v);
		mul(rid, mid+1, r, v);
	}
	pushup(id);
}
LL querySum(int id, int l, int r){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r)
		return tr[id].sum % p;
	if(r <= mid)
		return querySum(lid, l, r) % p;
	else if(l > mid)
		return querySum(rid, l, r) % p;
	else
		return (querySum(lid, l, mid) + querySum(rid, mid+1, r)) % p;
}

int main(){
	scanf("%d%d%lld", &n, &m, &p);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &c[i]);
	build(1, 1, n);
	while(m--){
		scanf("%d%d%d", &opt, &x, &y);
		if(opt == 1){
			scanf("%lld", &k);
			mul(1, x, y, k % p);
		}
		else if(opt == 2){
			scanf("%lld", &k);
			add(1, x, y, k % p);
		}
		else if(opt == 3)
			printf("%lld\n", querySum(1, x, y));
	}
	return 0;
}
