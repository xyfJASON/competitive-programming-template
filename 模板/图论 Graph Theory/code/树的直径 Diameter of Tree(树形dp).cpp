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

int dp[N], ans;
void dfs(int x, int f){
	int mx1 = 0, mx2 = 0;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f)	continue;
		dfs(edge[i].to, x);
		if(mx1 < dp[edge[i].to] + edge[i].dis)
			mx2 = mx1, mx1 = dp[edge[i].to] + edge[i].dis;
		else if(mx2 < dp[edge[i].to] + edge[i].dis)
			mx2 = dp[edge[i].to] + edge[i].dis;
	}
	dp[x] = mx1;
	ans = max(ans, mx1 + mx2);
}

int main(){
	int u, v, w;
	while(scanf("%d%d%d", &u, &v, &w) != EOF){
		n++;
		addEdge(u, v, w), addEdge(v, u, w);
	}
	n++;
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}