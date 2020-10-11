#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
#define mp(x, y) make_pair(x, y)
#define pb(x) emplace_back(x)

const int INF = 1e9;
const int N = 5005;

int n, m;
vector<pii> edge[N];

bool inq[N];
int dis[N], cnt[N];
bool SPFA(int s){
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
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		edge[b].pb(mp(a, c));
	}
	for(int i = 1; i <= n; i++)	dis[i] = INF;
	bool ok = true;
	for(int i = 1; i <= n && ok; i++)
		if(!cnt[i])	ok &= SPFA(i);
	if(!ok)	puts("NO");
	else{
		for(int i = 1; i <= n; i++)	printf("%d ", dis[i]);
		puts("");
	}
	return 0;
}