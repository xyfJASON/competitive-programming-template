#include<algorithm>
#include<cstdio>
#include<vector>

using namespace std;

#define pb(x) push_back(x)

const int INF = 1e9;
const int N = 5005;
const int M = 200005;

int n, m;
struct Edge{
	int u, v, dis;
}edge[M<<1];

int fa[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
void unionn(int x, int y){ fa[findfa(y)] = findfa(x); }

int mndis[N], mark[N];
vector<int> ans;
void Boruvka(){
	for(int i = 1; i <= n; i++)	fa[i] = i;
	while(1){
		vector<bool> vis(m+5);
		for(int i = 1; i <= n; i++)	mndis[i] = INF, mark[i] = 0;
		for(int i = 1; i <= m; i++){
			if(findfa(edge[i].u) == findfa(edge[i].v))	continue;
			if(mndis[findfa(edge[i].u)] > edge[i].dis){
				mndis[findfa(edge[i].u)] = edge[i].dis;
				mark[findfa(edge[i].u)] = i;
			}
			if(mndis[findfa(edge[i].v)] > edge[i].dis){
				mndis[findfa(edge[i].v)] = edge[i].dis;
				mark[findfa(edge[i].v)] = i;
			}
		}
		bool ok = true;
		for(int i = 1; i <= n; i++){
			if(findfa(i) != i)	continue;
			if(mark[i] && !vis[mark[i]]){
				ok = false;
				ans.pb(mark[i]);
				unionn(edge[mark[i]].u, edge[mark[i]].v);
				vis[mark[i]] = true;
			}
		}
		if(ok)	break;
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].dis);
	Boruvka();
	if(ans.size() != n - 1)	return puts("orz"), 0;
	int sum = 0;
	for(auto &e : ans)	sum += edge[e].dis;
	printf("%d\n", sum);
	return 0;
}
