#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

typedef long long LL;

const LL INF = 1e16;
const int N = 10005;
const int M = 100005;

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
	FLOW::n = n, FLOW::S = s, FLOW::T = t;
	for(int i = 1; i <= m; i++){
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		FLOW::addEdge(u, v, w);
		FLOW::addEdge(v, u, 0);
	}
	printf("%lld\n", FLOW::Dinic());
	return 0;
}