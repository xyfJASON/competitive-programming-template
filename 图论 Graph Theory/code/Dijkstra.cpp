#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 100005;
const int M = 200005;
const LL INF = 1e16;

int n, m, u, v, d, s;

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

LL dis[N];
void dijkstra(int s){
	vector<bool> vis(n+5, false);
	for(int i = 1; i <= n; i++)	dis[i] = INF;
	priority_queue< pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>> > q;
	dis[s] = 0;
	q.push(make_pair(dis[s], s));
	while(!q.empty()){
		auto cur = q.top(); q.pop();
		if(vis[cur.second])	continue;
		vis[cur.second] = true;
		for(int i = head[cur.second]; i; i = edge[i].nxt){
			if(dis[edge[i].to] > dis[cur.second] + edge[i].dis){
				dis[edge[i].to] = dis[cur.second] + edge[i].dis;
				q.push(make_pair(dis[edge[i].to], edge[i].to));
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &d);
		addEdge(u, v, d);
	}
	dijkstra(s);
	for(int i = 1; i <= n; i++)
		printf("%lld ", dis[i]);
	return 0;
}