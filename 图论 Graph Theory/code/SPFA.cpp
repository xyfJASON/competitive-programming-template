#include<cstdio>
#include<queue>

using namespace std;

typedef long long LL;

const int N = 100005;
const int M = 200005;
const LL INF = 2147483647;

int n, m, s, u, v, p;

struct Edge{
	int nxt, to;
	LL dis;
}edge[M];
int head[N], edgeNum;
void addEdge(int from, int to, LL dis){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].dis = dis;
	head[from] = edgeNum;
}

LL dis[N];
bool inq[N];
void SPFA(int s){
	for(int i = 1; i <= n; i++)
		dis[i] = INF;
	queue<int> q;
	dis[s] = 0;
	q.push(s);
	inq[s] = 1;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		inq[cur] = 0;
		for(int i = head[cur]; i; i = edge[i].nxt){
			if(dis[edge[i].to] > dis[cur] + edge[i].dis){
				dis[edge[i].to] = dis[cur] + edge[i].dis;
				if(!inq[edge[i].to]){
					q.push(edge[i].to);
					inq[edge[i].to] = 1;
				}
			}
		}
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &p);
		addEdge(u, v, p);
	}
	SPFA(s);
	for(int i = 1; i <= n; i++)
		printf("%lld ", dis[i]);
	return 0;
}
