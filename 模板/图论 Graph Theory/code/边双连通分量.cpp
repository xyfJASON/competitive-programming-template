#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>

using namespace std;

const int N = 100005;
const int M = 200005;

int n, m, q;

struct Edge{
	int nxt, to;
}edge[M<<1];
int head[N], edgeNum = 1;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

bool iscut[M<<1]; // iscut[i]==1 if edge i is a cut edge
int dfn[N], low[N], dfsClock;
void tarjan(int x, int f){
	dfn[x] = low[x] = ++dfsClock;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to, x);
			low[x] = min(low[x], low[edge[i].to]);
			if(low[edge[i].to] > dfn[x])
				iscut[i] = iscut[i^1] = 1;
		}
		else if(edge[i].to != f)
			low[x] = min(low[x], dfn[edge[i].to]);
	}
}

int belong[N], tot;
void dfs(int x, int now){
	belong[x] = now;
	for(int i = head[x]; i; i = edge[i].nxt)
		if(!belong[edge[i].to] && !iscut[i])
			dfs(edge[i].to, now);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v), addEdge(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			tarjan(i, 0);
	for(int i = 1; i <= n; i++)
		if(!belong[i])
			dfs(i, ++tot);
	for(int i = 1; i <= n; i++){
		for(int j = head[i]; j; j = edge[j].nxt){
			int to = edge[j].to;
			if(belong[i] != belong[to])
				vec[belong[i]].push_back(belong[to]);
		}
	}
	return 0;
}