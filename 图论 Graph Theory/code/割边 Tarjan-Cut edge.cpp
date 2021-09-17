#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 1005;
const int M = 1000005;
const int INF = 1e9;

struct Edge{
	int nxt, to, dis;
}edge[M<<1];
int head[N], edgeNum = 1;
void addEdge(int from, int to, int dis){
	edge[++edgeNum] = (Edge){head[from], to, dis};
	head[from] = edgeNum;
}

int n, m, x, y, z, ans, cntEdge[N][N];

bool iscut[M<<1]; // iscut[i]==1 if edge i is a cut edge
int dfn[N], low[N], dfsClock;
void tarjan(int x, int f){
	dfn[x] = low[x] = ++dfsClock;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to, x);
			low[x] = min(low[x], low[edge[i].to]);
			if(low[edge[i].to] > dfn[x])
				iscut[i] = iscut[i^1] = 1;
		}
		else if(edge[i].to != f)
			low[x] = min(low[x], dfn[edge[i].to]);
	}
}

void init(){
	memset(edge, 0, sizeof edge);
	memset(head, 0, sizeof head);
	edgeNum = 1;
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	dfsClock = 0;
	memset(iscut, 0, sizeof iscut);
	memset(cntEdge, 0, sizeof cntEdge);
	ans = INF;
}

int main(){
	while(scanf("%d%d", &n, &m)){
		if(n == 0 && m == 0)	break;
		init();
		for(int i = 1; i <= m; i++){
			scanf("%d%d%d", &x, &y, &z);
			addEdge(x, y, z);
			addEdge(y, x, z);
			cntEdge[x][y]++;
			cntEdge[y][x]++;
		}
		tarjan(1, 0);
		bool b = 0;
		for(int i = 2; i <= n; i++){
			if(!dfn[i]){
				puts("0");
				b = 1;
				break;
			}
		}
		if(b)	continue;
		for(int i = 1; i <= edgeNum; i++)
			if(iscut[i] && cntEdge[edge[i].to][edge[i^1].to] == 1)
				ans = min(ans, edge[i].dis);
		if(ans == INF)	puts("-1");
		else if(ans == 0)	puts("1");
		else	printf("%d\n", ans);
	}
	return 0;
}
