#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 205;
const int M = 40005;
const LL INF = 1e14;

namespace FLOW{

	int n, S, T;
	struct Edge{
		int nxt, to;
		LL flow; int id;
	}edge[M<<1];
	int head[N], edgeNum = 1;
	void addEdge(int from, int to, LL flow, int id){
		edge[++edgeNum] = (Edge){head[from], to, flow, id};
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
	int n, m;
	scanf("%d%d", &n, &m);
	FLOW::S = ++n, FLOW::T = ++n, FLOW::n = n;
	vector<int> u(m+1), v(m+1);
	vector<LL> lb(m+1), ub(m+1), M(n+1);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%lld%lld", &u[i], &v[i], &lb[i], &ub[i]);
		FLOW::addEdge(u[i], v[i], ub[i] - lb[i], i);
		FLOW::addEdge(v[i], u[i], 0, -1);
		M[u[i]] -= lb[i], M[v[i]] += lb[i];
	}
	LL sum = 0;
	for(int i = 1; i <= n - 2; i++){
		if(M[i] > 0)	FLOW::addEdge(FLOW::S, i, M[i], -1), FLOW::addEdge(i, FLOW::S, 0, -1), sum += M[i];
		if(M[i] < 0)	FLOW::addEdge(i, FLOW::T, -M[i], -1), FLOW::addEdge(FLOW::T, i, 0, -1);
	}
	LL maxFlow = FLOW::Dinic();
	if(sum != maxFlow){ puts("NO"); return 0; }
	puts("YES");
	vector<LL> ans(m+1);
	for(int i = 2; i <= FLOW::edgeNum; i += 2){
		if(FLOW::edge[i].id == -1)	continue;
		ans[FLOW::edge[i].id] = ub[FLOW::edge[i].id] - FLOW::edge[i].flow;
	}
	for(int i = 1; i <= m; i++)	printf("%lld\n", ans[i]);
	return 0;
}