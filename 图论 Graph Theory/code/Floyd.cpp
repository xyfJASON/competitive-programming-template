#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 205;
const int INF = 1e9;

int n, m, dis[N][N];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(i ^ j)	dis[i][j] = INF;
			else	dis[i][j] = 0;
	for(int i = 1; i <= m; i++){
		int u, v, d; scanf("%d%d%d", &u, &v, &d);
		dis[u][v] = dis[v][u] = d;
	}
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ", dis[i][j]);
		puts("");
	}
	return 0;
}