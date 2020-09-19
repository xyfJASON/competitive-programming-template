#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const long long INF = 1e16;
const int N = 10005;
const int M = 100005;

int n, m, s, t;

struct Edge{
	int nxt, to;
	long long flow;
}edge[M<<1];
int head[N], edgeNum = 1;
void addEdge(int from, int to, long long flow){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].flow = flow;
	head[from] = edgeNum;
}

bool inq[N];
int dep[N], curArc[N];
bool bfs(){
	for(int i = 1; i <= n; i++)
		dep[i] = 1e9, inq[i] = 0, curArc[i] = head[i];
	queue<int> q;
	q.push(s);
	inq[s] = 1;
	dep[s] = 0;
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
	if(dep[t] != 1e9)	return 1;
	return 0;
}
long long dfs(int x, long long minFlow){
	long long flow = 0;
	if(x == t)	return minFlow;
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
long long Dinic(){
	long long maxFlow = 0, flow = 0;
	while(bfs()){
		while(flow = dfs(s, INF))
			maxFlow += flow;
	}
	return maxFlow;
}

int main(){
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++){
		int u, v; long long w;
		scanf("%d%d%lld", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, 0);
	}
	printf("%lld\n", Dinic());
	return 0;
}