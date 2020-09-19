#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 100005;

int n, m, root, opt, u, v;
LL z, a[N], MOD;

struct Edge{
	int nxt, to;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

int fa[N], dep[N], son[N], sz[N];
void dfs(int x, int f, int depth){
	fa[x] = f; dep[x] = depth; sz[x] = 1; son[x] = 0;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x, depth + 1);
		sz[x] += sz[edge[i].to];
		if(!son[x] || sz[edge[i].to] > sz[son[x]])
			son[x] = edge[i].to;
	}
}
int top[N], st[N], ed[N], dfsClock, func[N];
void dfs(int x, int tp){
	st[x] = ++dfsClock; func[dfsClock] = x; top[x] = tp;
	if(son[x])	dfs(son[x], tp);
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == fa[x] || edge[i].to == son[x])	continue;
		dfs(edge[i].to, edge[i].to);
	}
	ed[x] = dfsClock;
}

#define lid id<<1
#define rid id<<1|1
#define mid ((tr[id].l + tr[id].r) >> 1)
#define len(id) (tr[id].r - tr[id].l + 1)
struct segTree{
	int l, r;
	LL sum, lazyAdd;
}tr[N<<2];
void pushup(int id){
	tr[id].sum = (tr[lid].sum + tr[rid].sum) % MOD;
}
void pushdown(int id){
	if(tr[id].lazyAdd && tr[id].l != tr[id].r){
		(tr[lid].lazyAdd += tr[id].lazyAdd) %= MOD;
		(tr[lid].sum += tr[id].lazyAdd * len(lid) % MOD) %= MOD;
		(tr[rid].lazyAdd += tr[id].lazyAdd) %= MOD;
		(tr[rid].sum += tr[id].lazyAdd * len(rid) % MOD) %= MOD;
		tr[id].lazyAdd = 0;
	}
}
void build(int id, int l, int r){
	tr[id].l = l; tr[id].r = r;
	tr[id].sum = tr[id].lazyAdd = 0;
	if(tr[id].l == tr[id].r){
		tr[id].sum = a[func[l]];
		return;
	}
	build(lid, l, mid);
	build(rid, mid+1, r);
	pushup(id);
}
void add(int id, int l, int r, LL val){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r){
		(tr[id].lazyAdd += val) %= MOD;
		(tr[id].sum += val * len(id) % MOD) %= MOD;
		return;
	}
	if(r <= mid)	add(lid, l, r, val);
	else if(l > mid)	add(rid, l, r, val);
	else{
		add(lid, l, mid, val);
		add(rid, mid+1, r, val);
	}
	pushup(id);
}
LL query(int id, int l, int r){
	pushdown(id);
	if(tr[id].l == l && tr[id].r == r)
		return tr[id].sum % MOD;
	if(r <= mid)	return query(lid, l, r);
	else if(l > mid)	return query(rid, l, r);
	else	return (query(lid, l, mid) + query(rid, mid+1, r)) % MOD;
}

void addPath(int u, int v, LL val){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]])	swap(u, v);
		add(1, st[top[u]], st[u], val);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v])	swap(u, v);
	add(1, st[v], st[u], val);
}
LL queryPath(int u, int v){
	LL res = 0;
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]])	swap(u, v);
		(res += query(1, st[top[u]], st[u])) %= MOD;
		u = fa[top[u]];
	}
	if(dep[u] < dep[v])	swap(u, v);
	(res += query(1, st[v], st[u])) %= MOD;
	return res;
}
void addSubtree(int u, LL val){
	add(1, st[u], ed[u], val);
}
LL querySubtree(int u){
	return query(1, st[u], ed[u]);
}

int main(){
	scanf("%d%d%d%lld", &n, &m, &root, &MOD);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		a[i] %= MOD;
	}
	for(int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(root, 0, 1);
	dfs(root, root);
	build(1, 1, n);
	for(int i = 1; i <= m; i++){
		scanf("%d", &opt);
		switch(opt){
			case 1:{
				scanf("%d%d%lld", &u, &v, &z);
				addPath(u, v, z % MOD);
				break;
			}
			case 2:{
				scanf("%d%d", &u, &v);
				printf("%lld\n", queryPath(u, v));
				break;
			}
			case 3:{
				scanf("%d%lld", &u, &z);
				addSubtree(u, z % MOD);
				break;
			}
			case 4:{
				scanf("%d", &u);
				printf("%lld\n", querySubtree(u));
				break;
			}
			default: ;
		}
	}
	return 0;
}
