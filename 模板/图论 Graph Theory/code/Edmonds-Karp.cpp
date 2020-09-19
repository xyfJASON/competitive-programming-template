#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;

const int N = 205;
const int M = 205;
const int INF = 2e9+10;

int n, m, u, v, w, src, dst;

struct Edge{
	int nxt, to, flow;
}edge[M<<1];
int head[N], edgeNum = 1;
void addEdge(int from, int to, int flow){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].flow = flow;
	head[from] = edgeNum;
}

int pre[N], minFlow[N];
int bfs(){
	queue<int> q;
	for(int i = 1; i <= n; i++){
		pre[i] = 0;
		minFlow[i] = INF;
	}
	q.push(src);
	while(!q.empty()){
		int cur = q.front(); q.pop();
		for(int i = head[cur]; i; i = edge[i].nxt){
			if(edge[i].flow && !pre[edge[i].to]){
				pre[edge[i].to] = i;
				minFlow[edge[i].to] = min(minFlow[cur], edge[i].flow);
				q.push(edge[i].to);
			}
		}
	}
	if(pre[dst] == 0)	return -1;
	return minFlow[dst];
}

int EK(){
	int flow = 0, maxflow = 0;
	while((flow = bfs()) != -1){
		int t = dst;
		while(t != src){
			edge[pre[t]].flow -= flow;
			edge[pre[t]^1].flow += flow;
			t = edge[pre[t]^1].to;
		}
		maxflow += flow;
	}
	return maxflow;
}

void init(){
	memset(edge, 0, sizeof edge);
	memset(head, 0, sizeof head);
	edgeNum = 1;
	memset(minFlow, 0, sizeof minFlow);
	memset(pre, 0, sizeof pre);
}

int main(){
	while(scanf("%d%d", &m, &n) != EOF){
		init();
		src = 1; dst = n;
		for(int i = 1; i <= m; i++){
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, 0);
		}
		printf("%d\n", EK());
	}
	return 0;
}
