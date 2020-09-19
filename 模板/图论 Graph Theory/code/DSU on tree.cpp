#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100005;

int n, c[N];

struct Edge{
	int nxt, to;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

int fa[N], sz[N], son[N];
void dfs(int x, int f){
	fa[x] = f, sz[x] = 1, son[x] = 0;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x);
		sz[x] += sz[edge[i].to];
		if(!son[x] || sz[edge[i].to] > sz[son[x]])
			son[x] = edge[i].to;
	}
}

LL ans[N], mx, sum, cnt[N]; // GLOBAL variants to store the answer
int mark; // mark the heavy son which needs to be ignored
void getData(int x, int val){ // get data with brute-force

	cnt[c[x]] += val;
	if(mx < cnt[c[x]])	mx = cnt[c[x]], sum = c[x];
	else if(mx == cnt[c[x]])	sum += c[x];
	
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == fa[x])	continue;
		if(edge[i].to == mark)	continue; // ignore the marked subtree
		getData(edge[i].to, val);
	}
}
void dsu(int x, bool opt){ // opt == true: answer needs to be erased
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == fa[x] || edge[i].to == son[x])	continue;
		dsu(edge[i].to, true); // solve for light sons first
	}
	if(son[x])	dsu(son[x], false), mark = son[x]; // solve for heavy son
	// now the global variants have already stored heavy son's answer
	getData(x, 1);
	mark = 0;
	
	// now the global variants store the answer for vertex x
	ans[x] = sum;
	
	if(opt){ // erase the answer
		getData(x, -1);
		mx = 0, sum = 0;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	for(int i = 1; i < n; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v), addEdge(v, u);
	}
	dfs(1, 0);
	dsu(1, true);
	for(int i = 1; i <= n; i++)
		printf("%lld ", ans[i]);
	return 0;
}