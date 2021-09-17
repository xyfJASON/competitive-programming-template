#include<bits/stdc++.h>

using namespace std;

template<typename T>void read(T&x){x=0;int fl=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')
fl=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}x*=fl;}
template<typename T,typename...Args>inline void read(T&t,Args&...args){read(t);read(args...);}

typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define mp(x, y) make_pair(x, y)
#define pb(x) emplace_back(x)

const int N = 100005;
const int M = 500005;

int n, m;
vector<pii> edge[N];
// edge[i].first is the vertex;
// edge[i].second is the id of this edge

bool vis[M];
stack<int> sta;
void dfs(int x){
	while(!edge[x].empty()){
		pii to = edge[x].back(); edge[x].pop_back();
		if(vis[to.second])	continue;
		vis[to.second] = true; // mark the edge
		dfs(to.first);
	}
	sta.push(x);
}

int main(){
	read(n, m);
	for(int i = 1; i <= m; i++){
		int u, v; read(u, v);
		edge[u].pb(mp(v, i));
		edge[v].pb(mp(u, i));
	}
	int st = 1;
	for(int i = 1; i <= n; i++){
		if(edge[i].size() & 1){
			st = i;
			break;
		}
	}
	dfs(st);
	while(!sta.empty()){
		printf("%d\n", sta.top());
		sta.pop();
	}
	return 0;
}
