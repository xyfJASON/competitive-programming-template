#include<algorithm>
#include<cstdio>
#include<queue>

using namespace std;

const int N = 5005;
const int M = 50005;
const int INF = 1e9;

int n, m, src, dst, u, v, w, f;

struct Edge{
	int nxt, to, flow, cost;
}edge[M<<1];
int head[N], edgeNum = 1;
void addEdge(int from, int to, int flow, int cost){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].flow = flow;
	edge[edgeNum].cost = cost;
	head[from] = edgeNum;
}

int minCost[N], minFlow[N], pre[N];
bool inq[N];
int spfa(){
	for(int i = 1; i <= n; i++){
		minCost[i] = minFlow[i] = INF;
		pre[i] = 0;
		inq[i] = 0;
	}
	queue<int> q;
	q.push(src);
	inq[src] = 1;
	minCost[src] = 0;
	while(!q.empty()){
		int cur = q.front(); q.pop();
		inq[cur] = 0;
		for(int i = head[cur]; i; i = edge[i].nxt){
			if(edge[i].flow && minCost[edge[i].to] > minCost[cur] + edge[i].cost){
				minCost[edge[i].to] = minCost[cur] + edge[i].cost;
				minFlow[edge[i].to] = min(minFlow[cur], edge[i].flow);
				pre[edge[i].to] = i;
				if(!inq[edge[i].to]){
					q.push(edge[i].to);
					inq[edge[i].to] = 1;
				}
			}
		}
	}
	if(pre[dst] == 0)	return -1;
	return minFlow[dst];
}

void EK(int &maxflow, int &mincost){
	maxflow = mincost = 0;
	int flow = 0;
	while((flow = spfa()) != -1){
		int t = dst;
		while(t != src){
			edge[pre[t]].flow -= flow;
			edge[pre[t]^1].flow += flow;
			t = edge[pre[t]^1].to;
		}
		maxflow += flow;
		mincost += flow * minCost[dst];
	}
}

int main(){
	scanf("%d%d%d%d", &n, &m, &src, &dst);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &w, &f);
		addEdge(u, v, w, f);
		addEdge(v, u, 0, -f);
	}
	int maxflow, mincost;
	EK(maxflow, mincost);
	printf("%d %d\n", maxflow, mincost);
	return 0;
}
