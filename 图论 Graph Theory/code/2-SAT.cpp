#include<bits/stdc++.h>

using namespace std;

const int N = 2000005;

#define pb(x) emplace_back(x)

int n, m;
vector<int> edge[N];

stack<int> sta;
bool insta[N];
int scc, belong[N], dfn[N], low[N], dfsClock;
void tarjan(int x){
	dfn[x] = low[x] = ++dfsClock;
	sta.push(x);
	insta[x] = 1;
	for(auto &to : edge[x]){
		if(!dfn[to]){
			tarjan(to);
			low[x] = min(low[x], low[to]);
		}
		else if(insta[to])
			low[x] = min(low[x], dfn[to]);
	}
	if(dfn[x] == low[x]){
		scc++;
		while(1){
			int cur = sta.top(); sta.pop();
			insta[cur] = 0, belong[cur] = scc;
			if(cur == x)	break;
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int k = 1; k <= m; k++){
		int i, a, j, b;
		scanf("%d%d%d%d", &i, &a, &j, &b);
		// i is a OR j is b
		if(a && b)	edge[i<<1].pb(j<<1|1), edge[j<<1].pb(i<<1|1);
		else if(a)	edge[i<<1].pb(j<<1), edge[j<<1|1].pb(i<<1|1);
		else if(b)	edge[j<<1].pb(i<<1), edge[i<<1|1].pb(j<<1|1);
		else		edge[i<<1|1].pb(j<<1), edge[j<<1|1].pb(i<<1);
	}
	for(int i = 2; i <= (n<<1|1); i++)
		if(!dfn[i])	tarjan(i);
	for(int i = 1; i <= n; i++){
		if(belong[i<<1] == belong[i<<1|1]){
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts("POSSIBLE");
	for(int i = 1; i <= n; i++)
		printf("%d ", belong[i<<1] < belong[i<<1|1] ? 0 : 1);
	return 0;
}