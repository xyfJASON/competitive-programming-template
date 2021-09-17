#include<queue>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1005;

int n1, n2, m;
struct Edge{
	int nxt, to;
}edge[N*N];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

bool vis[N];
int match[N]; // match[x] is the one 
bool dfs(int x){
	for(int i = head[x]; i; i = edge[i].nxt){
		if(vis[edge[i].to])	continue;
		vis[edge[i].to] = true;
		if(!match[edge[i].to] || dfs(match[edge[i].to])){
			match[edge[i].to] = x;
			return true;
		}
	}
	return false;
}

int Hungarian(){
	int cnt = 0;
	for(int i = 1; i <= n1; i++){
		for(int j = 1; j <= n2; j++)
			vis[j] = false;
		if(dfs(i))	cnt++;
	}
	return cnt;
}

int main(){
	scanf("%d%d%d", &n1, &n2, &m);
	for(int i = 1; i <= m; i++){
		int u, v; scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	printf("%d\n", Hungarian());
	return 0;
}