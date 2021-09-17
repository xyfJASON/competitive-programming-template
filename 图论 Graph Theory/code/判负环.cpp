#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
#define mp(x, y) make_pair(x, y)
#define pb(x) emplace_back(x)

const LL INF = 1e14;
const int N = 2005;

int n, m;
vector<pii> edge[N];

LL dis[N];
bool inq[N];
int cnt[N];
bool SPFA(int s){
	for(int i = 1; i <= n; i++)
		dis[i] = INF, cnt[i] = 0, inq[i] = false;
	queue<int> q;
	dis[s] = 0, q.push(s), inq[s] = 1, cnt[s]++;
	while(!q.empty()){
		int cur = q.front(); q.pop();
		inq[cur] = 0;
		for(auto &to : edge[cur]){
			if(dis[to.first] > dis[cur] + to.second){
				dis[to.first] = dis[cur] + to.second;
				if(!inq[to.first]){
					q.push(to.first);
					inq[to.first] = 1;
					if(++cnt[to.first] > n)	return false;
				}
			}
		}
	}
	return true;
}

int main(){
	int T; for(scanf("%d", &T); T; T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++)	edge[i].clear();
		for(int i = 1; i <= m; i++){
			int u, v, w; scanf("%d%d%d", &u, &v, &w);
			edge[u].pb(mp(v, w));
			if(w >= 0)	edge[v].pb(mp(u, w));
		}
		puts(SPFA(1) ? "NO" : "YES");
	}
	return 0;
}