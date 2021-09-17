#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>

using namespace std;

const int N = 10005;

int n;
struct Edge{
	int nxt, to, dis;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to, int dis){
	edge[++edgeNum] = (Edge){head[from], to, dis};
	head[from] = edgeNum;
}

int dis[N];
void dfs(int x, int f, int d, int &p){
	dis[x] = d;
	if(!p || dis[p] < d)	p = x;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x, d + edge[i].dis, p);
	}
}

int main(){
	int u, v, w;
	while(scanf("%d%d%d", &u, &v, &w) != EOF){
		n++;
		addEdge(u, v, w), addEdge(v, u, w);
	}
	n++;
	int x = 0, y = 0;
	memset(dis, 0, sizeof dis); dfs(1, 0, 0, x);
	memset(dis, 0, sizeof dis); dfs(x, 0, 0, y);
	// now x, y are ends of the diameter
	printf("%d\n", dis[y]);
	return 0;
}