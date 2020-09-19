#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 100005;
const int M = 300005;

int n, m, rt;
LL sum, ans = 1e16;

struct LCA{
	struct Edge{
		int nxt, to, dis;
	}edge[M<<1];
	int head[N], edgeNum;
	void addEdge(int from, int to, int dis){
		edge[++edgeNum] = (Edge){head[from], to, dis};
		head[from] = edgeNum;
	}

	int fa[N][25], dep[N];
	LL mx1[N][25], mx2[N][25];
	void dfs(int x, int f, int depth){
		dep[x] = depth, fa[x][0] = f;
		for(int i = head[x]; i; i = edge[i].nxt){
			if(edge[i].to == f)	continue;
			dfs(edge[i].to, x, depth+1);
			mx1[edge[i].to][0] = edge[i].dis;
			mx2[edge[i].to][0] = 0;
		}
	}
	void init(){
		for(int j = 1; (1 << j) <= n; j++){
			for(int i = 1; i <= n; i++){
				if(fa[i][j-1]){
					fa[i][j] = fa[fa[i][j-1]][j-1];
					mx1[i][j] = max(mx1[i][j-1], mx1[fa[i][j-1]][j-1]);
					mx2[i][j] = max(mx2[i][j-1], mx2[fa[i][j-1]][j-1]);
					if(mx1[i][j-1] != mx1[fa[i][j-1]][j-1])
						mx2[i][j] = max(mx2[i][j], min(mx1[i][j-1], mx1[fa[i][j-1]][j-1]));
				}
			}
		}
	}
	inline void update(LL mx1, LL mx2, LL &res1, LL &res2){
		if(res1 < mx1)	res2 = max(res1, mx2), res1 = mx1;
		else if(res1 == mx1)	res2 = max(res2, mx2);
		else	res2 = max(res2, mx1);
	}
	int lca(int x, int y, LL &max1, LL &max2){
		if(dep[x] < dep[y])	swap(x, y);
		for(int i = 20; i >= 0; i--){
			if(dep[x] - (1 << i) >= dep[y]){
				update(mx1[x][i], mx2[x][i], max1, max2);
				x = fa[x][i];
			}
		}
		if(x == y)	return x;
		for(int i = 20; i >= 0; i--){
			if(fa[x][i] && fa[x][i] != fa[y][i]){
				update(mx1[x][i], mx2[x][i], max1, max2);
				update(mx1[y][i], mx2[y][i], max1, max2);
				x = fa[x][i], y = fa[y][i];
			}
		}
		update(mx1[x][0], mx2[x][0], max1, max2);
		update(mx1[y][0], mx2[y][0], max1, max2);
		return fa[x][0];
	}
}lca;

struct Edge{
	int u, v, dis;
	bool inMST;
	bool operator < (const Edge &A) const{ return dis < A.dis; }
}edge[M];

int fa[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
inline void unionn(int x, int y){ fa[findfa(y)] = findfa(x); }

void Kruskal(){
	for(int i = 1; i <= n; i++)	fa[i] = i;
	sort(edge+1, edge+m+1);
	int cnt = 0;
	for(int i = 1; i <= m; i++){
		if(findfa(edge[i].u) == findfa(edge[i].v))	continue;
		unionn(edge[i].u, edge[i].v);
		
		lca.addEdge(edge[i].u, edge[i].v, edge[i].dis);
		lca.addEdge(edge[i].v, edge[i].u, edge[i].dis);
		edge[i].inMST = true;
		if(!rt)	rt = edge[i].u;
		
		sum += edge[i].dis;
		cnt++;
		if(cnt == n - 1)	break;
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].dis);
	Kruskal();

	lca.dfs(rt, 0, 1);
	lca.init();

	for(int i = 1; i <= m; i++){
		if(edge[i].inMST)	continue;
		LL mx1 = 0, mx2 = 0;
		lca.lca(edge[i].u, edge[i].v, mx1, mx2);
		if(edge[i].dis > mx1)	ans = min(ans, sum - mx1 + edge[i].dis);
		else	ans = min(ans, sum - mx2 + edge[i].dis);
	}
	printf("%lld\n", ans);
	return 0;
}
