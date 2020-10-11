#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
#define pb(x) emplace_back(x)
#define mp(x, y) make_pair(x, y)

const int N = 100005;

int n;
vector<int> edge[N];
bool tag[N];
int f[N], g[N];

namespace LCA{
	int fa[N][25], dep[N], dfn[N], dfsClock;
	void dfs(int x, int f, int depth){
		dfn[x] = ++dfsClock;
		dep[x] = depth, fa[x][0] = f;
		for(auto &to : edge[x]){
			if(to == f)	continue;
			dfs(to, x, depth+1);
		}
	}
	void init(){
		for(int j = 1; (1 << j) <= n; j++)
			for(int i = 1; i <= n; i++)
				if(fa[i][j-1])
					fa[i][j] = fa[fa[i][j-1]][j-1];
	}
	int lca(int x, int y){
		if(dep[x] < dep[y])
			swap(x, y);
		for(int i = 20; i >= 0; i--)
			if(dep[x] - (1 << i) >= dep[y])
				x = fa[x][i];
		if(x == y)	return x;
		for(int i = 20; i >= 0; i--){
			if(fa[x][i] && fa[x][i] != fa[y][i]){
				x = fa[x][i];
				y = fa[y][i];
			}
		}
		return fa[x][0];
	}
}

namespace VT{ // Virtual Tree
	vector<int> edge[N];
	stack<int> stk;
	vector<int> ver; // vertices in the virtual tree
	void build(vector<pii> &sv){
		// sv stores (dfn[x], x) pairs
		// among which x are special vertices
		sort(sv.begin(), sv.end());
		ver.clear();
		stk.push(1), ver.pb(1);
		for(auto &v : sv){
			int x = v.second;
			if(x == 1)	continue;
			int z = LCA::lca(x, stk.top());
			if(z == stk.top())	stk.push(x), ver.pb(x);
			else{
				while(!stk.empty() && LCA::dep[stk.top()] > LCA::dep[z]){
					int t = stk.top(); stk.pop();
					if(!stk.empty()){
						if(LCA::dep[stk.top()] >= LCA::dep[z])
							edge[t].pb(stk.top()), edge[stk.top()].pb(t);
						else	edge[t].pb(z), edge[z].pb(t);
					}
				}
				if(stk.empty() || z != stk.top())	stk.push(z), ver.pb(z);
				stk.push(x), ver.pb(x);
			}
		}
		while(!stk.empty()){
			int t = stk.top(); stk.pop();
			if(!stk.empty())
				edge[t].pb(stk.top()), edge[stk.top()].pb(t);
		}
	}

	void DP(int x, int fa){
		f[x] = g[x] = 0;
		for(auto &to : edge[x]){
			if(to == fa)	continue;
			DP(to, x);
			f[x] += f[to], g[x] += g[to];
		}
		if(tag[x])	f[x] += g[x], g[x] = 1;
		else if(g[x] > 1)	f[x]++, g[x] = 0;
	}
	int solve(){
		DP(1, 0);
		return f[1];
	}

	void clear(){
		for(auto &v : ver){
			edge[v].clear();
			f[v] = g[v] = 0;
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v; scanf("%d%d", &u, &v);
		edge[u].pb(v), edge[v].pb(u);
	}
	LCA::dfs(1, 0, 1);
	LCA::init();
	int q; for(scanf("%d", &q); q; q--){
		int k; scanf("%d", &k);
		vector<pii> sv; // special vertices
		while(k--){
			int a; scanf("%d", &a);
			sv.pb(mp(LCA::dfn[a], a));
			tag[a] = true;
		}
		bool ok = true;
		for(auto &v : sv){
			if(tag[LCA::fa[v.second][0]] & tag[v.second]){
				ok = false;
				break;
			}
		}
		if(!ok)	puts("-1");
		else{
			VT::build(sv);
			printf("%d\n", VT::solve());
		}
		VT::clear();
		for(auto &v : sv)	tag[v.second] = false;
	}
	return 0;
}