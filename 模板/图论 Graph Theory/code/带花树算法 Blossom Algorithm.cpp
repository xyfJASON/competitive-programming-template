#include<algorithm>
#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

const int N = 1005;
const int M = 50005;

int n, m, ans;
struct Edge{
	int nxt, to;
}edge[M<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

int fa[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }

int match[N];
int vis[N], pre[N], dfn[N], cnt;
queue<int> q;
int lca(int x, int y){
	for(++cnt, x = findfa(x), y = findfa(y); dfn[x] != cnt;){
		dfn[x] = cnt;
		x = findfa(pre[match[x]]);
		if(y)	swap(x, y);
	}
	return x;
}
void blossom(int x, int y, int w){
	while(findfa(x) != w){
		pre[x] = y, y = match[x];
		if(vis[y] == 2)	vis[y] = 1, q.push(y);
		if(findfa(x) == x)	fa[x] = w;
		if(findfa(y) == y)	fa[y] = w;
		x = pre[y];
	}
}
bool bfs(int s){
	for(int i = 1; i <= n; i++)	vis[i] = pre[i] = 0, fa[i] = i;
	while(!q.empty())	q.pop();
	q.push(s); vis[s] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = edge[i].nxt){
			int v = edge[i].to;
			if(findfa(u) == findfa(v) || vis[v] == 2)	continue;
			if(!vis[v]){
				vis[v] = 2, pre[v] = u;
				if(!match[v]){
					for(int x = v, lst; x; x = lst)
						lst = match[pre[x]], match[x] = pre[x], match[pre[x]] = x;
					return true;
				}
				vis[match[v]] = 1;
				q.push(match[v]);
			}
			else{
				int l = lca(u, v);
				blossom(u, v, l);
				blossom(v, u, l);
			}
		}
	}
	return false;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v), addEdge(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!match[i])
			ans += bfs(i);
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++)
		printf("%d ", match[i]);
	return 0;
}