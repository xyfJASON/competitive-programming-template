#include<map>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 10005;
const int INF = 1e9;

int n, m, k[105], u, v, w;

struct Edge{
	int nxt, to, dis;
}edge[N<<1];
int head[N], edgeNum;
void addEdge(int from, int to, int dis){
	edge[++edgeNum].nxt = head[from];
	edge[edgeNum].to = to;
	edge[edgeNum].dis = dis;
	head[from] = edgeNum;
}

int root, sum, mxson[N], size[N];
bool vis[N];
void getRoot(int x, int f){
	mxson[x] = 0, size[x] = 1;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == f || vis[edge[i].to])	continue;
		getRoot(edge[i].to, x);
		size[x] += size[edge[i].to];
		mxson[x] = max(mxson[x], size[edge[i].to]);
	}
	mxson[x] = max(mxson[x], sum - size[x]);
	if(mxson[root] > mxson[x])	root = x;
}


int dis[N];
void getDis(int x, int fa, int d){
	dis[++dis[0]] = d;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(edge[i].to == fa || vis[edge[i].to])	continue;
		getDis(edge[i].to, x, d + edge[i].dis);
	}
}

map<int, int> cnt;
void calc(int x, int d, int fl){
	dis[0] = 0;
	getDis(x, 0, d);
	sort(dis+1, dis+dis[0]+1);
	for(int i = 1; i <= dis[0]; i++){
		for(int j = 1; j <= m; j++){
			if(k[j] - dis[i] * 2 < 0)	continue;
			int l = lower_bound(dis+i, dis+dis[0]+1, k[j] - dis[i]) - dis;
			if(dis[l] != k[j] - dis[i])	continue;
			int r = upper_bound(dis+i, dis+dis[0]+1, k[j] - dis[i]) - dis;
			cnt[k[j]] += fl * (r - l);
		}
	}
}

void solve(int x){
	calc(x, 0, 1);
	vis[x] = 1;
	for(int i = head[x]; i; i = edge[i].nxt){
		if(vis[edge[i].to])	continue;
		calc(edge[i].to, edge[i].dis, -1); // Inclusion-Exclusion Principle
		root = 0, sum = size[edge[i].to], mxson[0] = INF;
		getRoot(edge[i].to, 0);
		solve(root);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++){
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	for(int i = 1; i <= m; i++)
		scanf("%d", &k[i]);
	root = 0, sum = n, mxson[0] = INF;
	getRoot(1, 0);
	solve(root);
	for(int i = 1; i <= m; i++)
		puts(cnt[k[i]] ? "AYE" : "NAY");
	return 0;
}
