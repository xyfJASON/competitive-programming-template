#include<bits/stdc++.h>

using namespace std;

const int N = 5000005;

#define pb(x) emplace_back(x)
#define mp(x, y) make_pair(x, y)

int n, fa[N], deg[N];
vector<int> edge[N];

namespace Prufer{
	void getFa(int x, int f){ // ATT: initially dfs from n
		fa[x] = f;
		for(auto &to : edge[x]){
			if(to == f)	continue;
			getFa(to, x);
		}
	}
	vector<int> code(){
		vector<int> res(n+5);
		int ptr = 0;
		while(deg[ptr] != 1)	ptr++;
		int leaf = ptr;
		for(int i = 1; i <= n - 2; i++){
			int next = fa[leaf];
			res[i] = next;
			if(--deg[next] == 1 && next < ptr)	leaf = next;
			else{
				ptr++; while(deg[ptr] != 1) ptr++;
				leaf = ptr;
			}
		}
		return res;
	}
	vector< pair<int, int> > decode(vector<int> &code){
		vector< pair<int, int> > edges(n+5);
		for(int i = 1; i <= n; i++)	deg[i] = 1;
		for(int i = 1; i <= n - 2; i++)	deg[code[i]]++;
		int ptr = 0;
		while(deg[ptr] != 1)	ptr++;
		int leaf = ptr;
		for(int i = 1; i <= n - 2; i++){
			edges.emplace_back(mp(leaf, code[i])), fa[leaf] = code[i];
			if(--deg[code[i]] == 1 && code[i] < ptr)	leaf = code[i];
			else{
				ptr++; while(deg[ptr] != 1) ptr++;
				leaf = ptr;
			}
		}
		edges.emplace_back(mp(leaf, n)), fa[leaf] = n;
		return edges;
	}

}

int main(){
	int m; scanf("%d%d", &n, &m);
	if(m == 1){
		for(int i = 1; i < n; i++){
			scanf("%d", &fa[i]);
			deg[i]++, deg[fa[i]]++;
		}
		fa[n] = 0;
		vector<int> code = Prufer::code();
		long long ans = 0; for(int i = 1; i <= n - 2; i++)
			ans ^= 1ll * i * code[i]; printf("%lld\n", ans);
	}
	else{
		vector<int> code(n+5);
		for(int i = 1; i <= n - 2; i++)	scanf("%d", &code[i]);
		Prufer::decode(code);
		long long ans = 0; for(int i = 1; i <= n; i++)
			ans ^= 1ll * i * fa[i]; printf("%lld\n", ans);
	}
	return 0;
}