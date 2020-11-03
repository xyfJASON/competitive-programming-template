#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1205;
const int M = 120005;
const LL INF = 1e14;

namespace FLOW{
	
	int n, S, T;
	struct Edge{
		int nxt, to;
		LL flow;
	}edge[M<<1];
	int head[N], edgeNum = 1;
	void addEdge(int from, int to, LL flow){
		edge[++edgeNum] = (Edge){head[from], to, flow};
		head[from] = edgeNum;
	}

	int dep[N], gap[N], curArc[N];
	void bfs(){
		for(int i = 1; i <= n; i++)	dep[i] = -1, gap[i] = 0;
		dep[T] = 0, gap[0] = 1;
		queue<int> q;
		q.push(T);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(int i = head[cur]; i; i = edge[i].nxt){
				if(dep[edge[i].to] != -1)	continue;
				dep[edge[i].to] = dep[cur] + 1;
				gap[dep[edge[i].to]]++;
				q.push(edge[i].to);
			}
		}
	}
	LL dfs(int x, LL minFlow){
		if(x == T)	return minFlow;
		LL outFlow = 0;
		for(int i = curArc[x]; i; i = edge[i].nxt){
			curArc[x] = i;
			if(dep[edge[i].to] + 1 == dep[x] && edge[i].flow){
				LL flow = dfs(edge[i].to, min(minFlow - outFlow, edge[i].flow));
				if(flow){
					edge[i].flow -= flow;
					edge[i^1].flow += flow;
					outFlow += flow;
				}
				if(outFlow == minFlow)	return minFlow;
			}
		}
		if(--gap[dep[x]] == 0)	dep[S] = n + 1;
		gap[++dep[x]]++;
		return outFlow;
	}
	inline LL ISAP(){
		LL maxFlow = 0;
		bfs();
		while(dep[S] < n){
			for(int i = 1; i <= n; i++)	curArc[i] = head[i];
			maxFlow += dfs(S, INF);
		}
		return maxFlow;
	}
}

int main(){
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	FLOW::n = n, FLOW::S = s, FLOW::T = t;
	for(int i = 1; i <= m; i++){
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		FLOW::addEdge(u, v, w);
		FLOW::addEdge(v, u, 0);
	}
	printf("%lld\n", FLOW::ISAP());
	return 0;
}