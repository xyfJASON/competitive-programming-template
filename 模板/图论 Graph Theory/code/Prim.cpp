#include<cstdio>
#include<queue>

using namespace std;

typedef long long LL;

const int N = 5005;
const int M = 200005;
const LL INF = 1e15;

int n, m, x, y;
LL z, ans;

struct Edge{
	int nxt, to;
	LL len;
}edge[M<<1];
int head[N], edgeNum;
void addEdge(int from, int to, LL len){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].len = len;
	head[from] = edgeNum;
}

struct Node{
	LL dis;
	int num;
	bool operator < (const Node &a) const{
		return a.dis < dis;
	}
};

LL dis[N];
bool inS[N];
void prim(){
	for(int i = 1; i <= n; i++){
		dis[i] = INF;
		inS[i] = 0;
	}
	priority_queue<Node> q;
	dis[1] = 0;
	q.push( (Node){0, 1} );
	while(!q.empty()){
		Node cur = q.top();
		q.pop();
		if(inS[cur.num])    continue;
		inS[cur.num] = 1;
		ans += cur.dis;
		for(int i = head[cur.num]; i; i = edge[i].nxt){
			if(dis[edge[i].to] > edge[i].len){
				dis[edge[i].to] = edge[i].len;
				q.push( (Node){dis[edge[i].to], edge[i].to} );
			}
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%lld", &x, &y, &z);
		addEdge(x, y, z);
		addEdge(y, x, z);
	}
	prim();
	printf("%lld\n", ans);
	return 0;
}
