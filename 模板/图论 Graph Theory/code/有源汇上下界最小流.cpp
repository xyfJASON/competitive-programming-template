#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 55005;
const int M = 200005;
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

	bool inq[N];
	int dep[N], curArc[N];
	inline bool bfs(){
		for(int i = 1; i <= n; i++)
			dep[i] = 1e9, inq[i] = 0, curArc[i] = head[i];
		queue<int> q;
		q.push(S);
		inq[S] = 1;
		dep[S] = 0;
		while(!q.empty()){
			int cur = q.front(); q.pop();
			inq[cur] = 0;
			for(int i = head[cur]; i; i = edge[i].nxt){
				if(dep[edge[i].to] > dep[cur] + 1 && edge[i].flow){
					dep[edge[i].to] = dep[cur] + 1;
					if(!inq[edge[i].to]){
						q.push(edge[i].to);
						inq[edge[i].to] = 1;
					}
				}
			}
		}
		if(dep[T] != 1e9)	return 1;
		return 0;
	}
	LL dfs(int x, LL minFlow){
		LL flow = 0;
		if(x == T)	return minFlow;
		for(int i = curArc[x]; i; i = edge[i].nxt){
			curArc[x] = i;
			if(dep[edge[i].to] == dep[x] + 1 && edge[i].flow){
				flow = dfs(edge[i].to, min(minFlow, edge[i].flow));
				if(flow){
					edge[i].flow -= flow;
					edge[i^1].flow += flow;
					return flow;
				}
			}
		}
		return 0;
	}
	inline LL Dinic(){
		LL maxFlow = 0, flow = 0;
		while(bfs()){
			while(flow = dfs(S, INF))
				maxFlow += flow;
		}
		return maxFlow;
	}
}

int main(){
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	FLOW::S = ++n, FLOW::T = ++n, FLOW::n = n;
	vector<LL> lb(m+1), ub(m+1), M(n+1);
	for(int i = 1; i <= m; i++){
		int u, v; scanf("%d%d%lld%lld", &u, &v, &lb[i], &ub[i]);
		FLOW::addEdge(u, v, ub[i] - lb[i]), FLOW::addEdge(v, u, 0);
		M[u] -= lb[i], M[v] += lb[i];
	}
	LL sum = 0;
	for(int i = 1; i <= n - 2; i++){
		if(M[i] > 0)	FLOW::addEdge(FLOW::S, i, M[i]), FLOW::addEdge(i, FLOW::S, 0), sum += M[i];
		if(M[i] < 0)	FLOW::addEdge(i, FLOW::T, -M[i]), FLOW::addEdge(FLOW::T, i, 0);
	}
	FLOW::addEdge(t, s, INF), FLOW::addEdge(s, t, 0);
	if(sum != FLOW::Dinic()){ puts("please go home to sleep"); return 0; }

	sum = FLOW::edge[FLOW::edgeNum].flow;
	FLOW::edge[FLOW::edgeNum].flow = FLOW::edge[FLOW::edgeNum^1].flow = 0;
	FLOW::S = t, FLOW::T = s;
	printf("%lld\n", sum - FLOW::Dinic());
	return 0;
}