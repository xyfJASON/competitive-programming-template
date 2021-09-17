#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 105;
const int M = 505;
const LL INF = 1e16;

int n, m, k, keys[N];

struct Edge{
	int nxt, to, dis;
}edge[M<<1];
int head[N], edgeNum;
void addEdge(int from, int to, int dis){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].dis = dis;
	head[from] = edgeNum;
}

LL dp[N][2005];
priority_queue< pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>> > q;
void dijkstra(int S){
	vector<bool> vis(n+5);
	while(!q.empty()){
		auto cur = q.top(); q.pop();
		if(vis[cur.second])	continue;
		vis[cur.second] = true;
		for(int i = head[cur.second]; i; i = edge[i].nxt){
			if(dp[edge[i].to][S] > dp[cur.second][S] + edge[i].dis){
				dp[edge[i].to][S] = dp[cur.second][S] + edge[i].dis;
				q.push(make_pair(dp[edge[i].to][S], edge[i].to));
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++){
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w), addEdge(v, u, w);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < (1 << k); j++)
			dp[i][j] = INF;
	for(int i = 1; i <= k; i++){
		scanf("%d", &keys[i]);
		dp[keys[i]][1<<(i-1)] = 0;
	}
	for(int S = 1; S < (1 << k); S++){
		for(int i = 1; i <= n; i++){
			for(int T = S; T; T = (T - 1) & S)
				dp[i][S] = min(dp[i][S], dp[i][T] + dp[i][S ^ T]);
			if(dp[i][S] != INF)	q.push(make_pair(dp[i][S], i));	
		}
		dijkstra(S);
	}
	printf("%lld\n", dp[keys[1]][(1<<k)-1]);
	return 0;
}