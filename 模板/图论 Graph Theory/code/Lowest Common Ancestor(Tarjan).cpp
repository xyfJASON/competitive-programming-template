#include<algorithm>
#include<vector>
#include<cstdio>

using namespace std;

const int N = 500005;

int n, q, rt;

struct Edge{
	int nxt, to;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

int fa[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
inline void unionn(int x, int y){ fa[findfa(y)] = findfa(x); }

struct Query{
	int id, ver;
};
vector<Query> query[N];
int ans[N];

bool vis[N];
void dfs(int x, int f){
	vis[x] = true;
	for(auto k: query[x]){
		if(ans[k.id])	continue;
		if(!vis[k.ver])	continue;
		ans[k.id] = findfa(k.ver);
	}
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x);
		unionn(x, edge[i].to);
	}
}

int main(){
	scanf("%d%d%d", &n, &q, &rt);
	for(int i = 1; i < n; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v), addEdge(v, u);
	}
	for(int i = 1; i <= q; i++){
		int u, v; scanf("%d%d", &u, &v);
		query[u].emplace_back((Query){i, v});
		query[v].emplace_back((Query){i, u});
	}
	for(int i = 1; i <= n; i++)	fa[i] = i;
	dfs(rt, 0);
	for(int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}