#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 500005;
const int M = 500005;

int n, m, s, u, v;

struct Edge{
	int nxt, to;
}edge[M<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	head[from] = edgeNum;
}

int fa[N][25], dep[N];
void dfs(int x, int f, int depth){
	dep[x] = depth;
	fa[x][0] = f;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x, depth+1);
	}
}
void init(){
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i <= n; i++)
			if(fa[i][j-1])
				fa[i][j] = fa[fa[i][j-1]][j-1];
}
int lca(int x, int y){
	if(dep[x] < dep[y])
		swap(x, y);
	for(int i = 20; i >= 0; i--)
		if(dep[x] - (1 << i) >= dep[y])
			x = fa[x][i];
	if(x == y)	return x;
	for(int i = 20; i >= 0; i--){
		if(fa[x][i] && fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main(){
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(s, 0, 1);
	init();
	while(m--){
		scanf("%d%d", &u, &v);
		printf("%d\n", lca(u, v));
	}
	return 0;
}
