#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 20005;
const int M = 100005;

struct Edge{
	int nxt, to;
}edge[M<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	head[from] = edgeNum;
}

int n, m, x, y;

int cnt;
bool iscut[N];
int dfn[N], low[N], dfsClock;
void tarjan(int x, int f){
	int son = 0;
	dfn[x] = low[x] = ++dfsClock;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(!dfn[edge[i].to]){
			son++;
			tarjan(edge[i].to, x);
			low[x] = min(low[x], low[edge[i].to]);
			if(f == 0 && son > 1)
				iscut[x] = 1;
			if(f != 0 && low[edge[i].to] >= dfn[x])
				iscut[x] = 1;
		}
		else if(edge[i].to != f)
			low[x] = min(low[x], dfn[edge[i].to]);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &x, &y);
		addEdge(x, y);
		addEdge(y, x);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			tarjan(i, 0);
	for(int i = 1; i <= n; i++)
		cnt += iscut[i];
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if(iscut[i])
			printf("%d ", i);
	return 0;
}
