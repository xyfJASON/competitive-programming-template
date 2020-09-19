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

int Euler[N<<1], dfn[N], dfntot;
void dfs(int x, int f){
	Euler[dfn[x] = ++dfntot] = x;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x);
		Euler[++dfntot] = x;
	}
}

namespace RMQ{
	int rmq[N<<1][25], lg[N<<1];
	void pre(){
		lg[1] = 0, lg[2] = 1;
		for(int i = 3; i <= dfntot; i++)	lg[i] = lg[i/2] + 1;
	}
	void init(){
		for(int j = 1; (1 << j) <= dfntot; j++)
			for(int i = 1; i + (1 << j) - 1 <= dfntot; i++)
				rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
	}
	int query(int l, int r){
		int k = lg[r - l + 1];
		return min(rmq[l][k], rmq[r-(1<<k)+1][k]);
	}
};

inline int lca(int x, int y){
	int l = min(dfn[x], dfn[y]), r = max(dfn[x], dfn[y]);
	return Euler[RMQ::query(l, r)];
}

int main(){
	scanf("%d%d%d", &n, &q, &rt);
	for(int i = 1; i < n; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v), addEdge(v, u);
	}
	dfs(rt, 0);
	
	RMQ::pre();
	for(int i = 1; i <= dfntot; i++)	RMQ::rmq[i][0] = dfn[Euler[i]];
	RMQ::init();
	
	while(q--){
		int u, v; scanf("%d%d", &u, &v);
		printf("%d\n", lca(u, v));
	}
	return 0;
}