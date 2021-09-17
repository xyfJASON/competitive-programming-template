#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const LL INF = 1e14;
const int N = 505;

namespace KM{
	int n;
	LL w[N][N];
	int matchx[N], matchy[N];
	LL lx[N], ly[N];
	LL slack[N];
	bool visx[N], visy[N];

	queue<int> q;
	int pre[N];

	bool check(int cur){
		visy[cur] = true;
		if(matchy[cur]){
			if(!visx[matchy[cur]]){
				q.push(matchy[cur]);
				visx[matchy[cur]] = true;
			}
			return false;
		}
		while(cur)	swap(cur, matchx[matchy[cur] = pre[cur]]);
		return true;
	}
	void bfs(int s){
		fill(visx, visx+n+1, false);
		fill(visy, visy+n+1, false);
		fill(slack, slack+n+1, INF);
		while(!q.empty())	q.pop();
		q.push(s), visx[s] = true;
		while(1){
			while(!q.empty()){
				int cur = q.front(); q.pop();
				for(int i = 1; i <= n; i++){
					LL diff = lx[cur] + ly[i] - w[cur][i];
					if(!visy[i] && diff <= slack[i]){
						slack[i] = diff;
						pre[i] = cur;
						if(diff == 0)
							if(check(i))	return;
					}
				}
			}
			LL delta = INF;
			for(int i = 1; i <= n; i++)
				if(!visy[i] && slack[i])
					delta = min(delta, slack[i]);
			for(int i = 1; i <= n; i++){
				if(visx[i])	lx[i] -= delta;
				if(visy[i])	ly[i] += delta;
				else	slack[i] -= delta;
			}
			while(!q.empty())	q.pop();
			for(int i = 1; i <= n; i++)
				if(!visy[i] && !slack[i] && check(i))
					return;
		}
	}
	void solve(){
		fill(matchx, matchx+n+1, 0);
		fill(matchy, matchy+n+1, 0);
		fill(ly, ly+n+1, 0);
		for(int i = 1; i <= n; i++){
			lx[i] = 0;
			for(int j = 1; j <= n; j++)
				lx[i] = max(lx[i], w[i][j]);
		}
		for(int i = 1; i <= n; i++)	bfs(i);
	}
}

int n, m;

int main(){
	scanf("%d%d", &n, &m);
	KM::n = n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			KM::w[i][j] = -INF;
	for(int i = 1; i <= m; i++){
		int y, c, h; scanf("%d%d%d", &y, &c, &h);
		KM::w[y][c] = h;
	}
	KM::solve();
	LL ans = 0;
	for(int i = 1; i <= n; i++)	ans += KM::w[i][KM::matchx[i]];
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++)	printf("%d ", KM::matchy[i]);
	return 0;
}