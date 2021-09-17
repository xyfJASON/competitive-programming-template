#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
#define pb(x) emplace_back(x)

const int N = 40005;

int n, m, color[N], t[N];
vi edge[N];

int belong[N<<1], sq;
struct Query{
	int id, l, r, lca;
	int ans;
	bool operator < (const Query &A) const{
		return (belong[l] == belong[A.l] ? r < A.r : belong[l] < belong[A.l]);
	}
}q[100005];

inline void disc(int a[]){
	for(int i = 1; i <= n; i++)	t[i] = a[i];
	sort(t+1, t+n+1);
	int len = unique(t+1, t+n+1) - (t+1);
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(t+1, t+len+1, a[i]) - t;
}

int st[N], ed[N], tot, fa[N][25], dep[N], euler[N<<1];
void dfs(int x, int f, int depth){
	euler[++tot] = x, st[x] = tot;
	fa[x][0] = f, dep[x] = depth;
	for(auto &to : edge[x]){
		if(to == f)	continue;
		dfs(to, x, depth+1);
	}
	euler[++tot] = x, ed[x] = tot;
}
inline void init(){
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i <= n; i++)
			if(fa[i][j-1])
				fa[i][j] = fa[fa[i][j-1]][j-1];
}
inline int lca(int x, int y){
	if(dep[x] < dep[y])	swap(x, y);
	for(int i = 20; i >= 0; i--)
		if(dep[x] - (1 << i) >= dep[y])
			x = fa[x][i];
	if(x == y)	return x;
	for(int i = 20; i >= 0; i--)
		if(fa[x][i] && fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int nowAnswer, cnt[N];
bool vis[N];
inline void update(int x){
	cnt[color[x]] += !vis[x] ? 1 : -1;
	if(vis[x] && cnt[color[x]] == 0)	nowAnswer--;
	if(!vis[x] && cnt[color[x]] == 1)	nowAnswer++;
	vis[x] = !vis[x];
}

int main(){
	scanf("%d%d", &n, &m);
	sq = (n << 1) / sqrt(m);
	for(int i = 1; i <= (n << 1); i++)	belong[i] = (i - 1) / sq + 1;

	for(int i = 1; i <= n; i++)	scanf("%d", &color[i]);
	disc(color);
	for(int i = 1; i < n; i++){
		int u, v; scanf("%d%d", &u, &v);
		edge[u].pb(v), edge[v].pb(u);
	}
	dfs(1, 0, 1);
	init();
	for(int i = 1; i <= m; i++){
		int u, v, l; scanf("%d%d", &u, &v); l = lca(u, v);
		if(st[u] > st[v])	swap(u, v);
		q[i] = {i, l == u ? st[u] : ed[u], st[v], l == u ? 0 : l};
	}
	sort(q+1, q+m+1);
	for(int i = 1, l = 1, r = 0; i <= m; i++){
		for(; l > q[i].l; l--)	update(euler[l-1]);
		for(; r < q[i].r; r++)	update(euler[r+1]);
		for(; l < q[i].l; l++)	update(euler[l]);
		for(; r > q[i].r; r--)	update(euler[r]);
		if(q[i].lca)	update(q[i].lca);
		q[i].ans = nowAnswer;
		if(q[i].lca)	update(q[i].lca);
	}
	sort(q+1, q+m+1, [&](const Query &A, const Query &B){ return A.id < B.id; } );
	for(int i = 1; i <= m; i++)	printf("%d\n", q[i].ans);
	return 0;
}