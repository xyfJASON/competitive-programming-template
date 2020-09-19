#include<algorithm>
#include<vector>
#include<cstdio>

using namespace std;

const int N = 200005;
const int M = 100005;

int n, m, rt; // rt is the root of 'Kruskal Tree'

int val[N]; // points' value of 'Kruskal Tree'
struct Edge{
	int nxt, to;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to){
	edge[++edgeNum] = (Edge){head[from], to};
	head[from] = edgeNum;
}

namespace MST{
	int fa[N];
	int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
	inline void unionn(int x, int y){ fa[findfa(y)] = findfa(x); }

	struct Edge{
		int u, v, dis;
		bool operator < (const Edge &A) const{ return dis < A.dis; }
	}edge[M];
	void Kruskal(){
		rt = n;
		for(int i = 1; i <= n * 2; i++)	fa[i] = i; // pay attention to *2
		sort(edge+1, edge+m+1);
		int cnt = 0;
		for(int i = 1; i <= m; i++){
			if(findfa(edge[i].u) == findfa(edge[i].v))	continue;

			// build the tree:
			++rt;
			addEdge(rt, findfa(edge[i].u)), addEdge(findfa(edge[i].u), rt);
			addEdge(rt, findfa(edge[i].v)), addEdge(findfa(edge[i].v), rt);
			unionn(rt, edge[i].u), unionn(rt, edge[i].v);
			val[rt] = edge[i].dis;

			cnt++;
			if(cnt == n - 1)	break;
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &MST::edge[i].u, &MST::edge[i].v, &MST::edge[i].dis);
	MST::Kruskal();
	
	// now the Kruskal tree is rooted at rt (rt == 2n-1)
	// do something...

	return 0;
}