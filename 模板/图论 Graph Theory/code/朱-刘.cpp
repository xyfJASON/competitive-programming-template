#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 105;
const int M = 10005;

int n, m, rt;

struct Edge{
	int u, v, w; // from u to v
}edge[M];
int pre[N], ine[N], vis[N], id[N];
int Chu_Liu(){
	int res = 0;
	int tot = n;
	while(1){
		for(int i = 1; i <= tot; i++)	ine[i] = INF;
		for(int i = 1; i <= m; i++)
			if(edge[i].u != edge[i].v && ine[edge[i].v] > edge[i].w)
				ine[edge[i].v] = edge[i].w, pre[edge[i].v] = edge[i].u;
		for(int i = 1; i <= tot; i++) // check if no solution
			if(i != rt && ine[i] == INF)
				return -1;
		int cnt = 0;
		for(int i = 1; i <= tot; i++)	vis[i] = id[i] = 0;
		for(int i = 1; i <= tot; i++){
			if(i == rt)	continue;
			res += ine[i];
			int now = i;
			while(vis[now] != i && !id[now] && now != rt) // find loops
				vis[now] = i, now = pre[now];
			if(vis[now] == i){ // find a loop, mark it
				id[now] = ++cnt;
				for(int p = pre[now]; p != now; p = pre[p])
					id[p] = cnt;
			}
		}
		if(cnt == 0)	return res; // no loop -> find a solution
		for(int i = 1; i <= tot; i++)
			if(!id[i])	id[i] = ++cnt;
		for(int i = 1; i <= m; i++){ // rebuild the graph
			if(id[edge[i].u] != id[edge[i].v])	edge[i].w -= ine[edge[i].v];
			edge[i].u = id[edge[i].u], edge[i].v = id[edge[i].v];
		}
		rt = id[rt];
		tot = cnt;
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &rt);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
	printf("%d\n", Chu_Liu());
	return 0;
}