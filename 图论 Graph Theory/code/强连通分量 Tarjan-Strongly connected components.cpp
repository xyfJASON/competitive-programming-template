#include<cstdio>
#include<stack>
#include<queue>

using namespace std;

const int N = 10005;
const int M = 100005;

int n, m, u, v;

struct Edge{
	int nxt, to;
}edge[M], nedge[M];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	head[from] = edgeNum;
}
int nhead[N], nedgeNum;
void naddEdge(int from, int to){
	nedge[++nedgeNum].nxt = nhead[from];
	nedge[nedgeNum].to = to;
	nhead[from] = nedgeNum;
}


stack<int> sta;
bool insta[N];
int scc, belong[N], dfn[N], low[N], dfsClock;
void tarjan(int x){
	dfn[x] = low[x] = ++dfsClock;
	sta.push(x);
	insta[x] = 1;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[x] = min(low[x], low[edge[i].to]);
		}
		else if(insta[edge[i].to])
			low[x] = min(low[x], dfn[edge[i].to]);
	}
	if(dfn[x] == low[x]){
		scc++;
		while(1){
			int cur = sta.top();
			sta.pop();
			insta[cur] = 0;
			belong[cur] = scc;
			if(cur == x)
				break;
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			tarjan(i);
	for(int i = 1; i <= n; i++)
		for(int j = head[i]; j; j = edge[j].nxt)
			if(belong[i] != belong[edge[j].to])
				naddEdge(belong[i], belong[edge[j].to]);

	return 0;
}
