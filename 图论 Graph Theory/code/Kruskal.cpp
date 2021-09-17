#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 5005;
const int M = 200005;

struct Edge{
	int u, v, dis;
	bool operator < (const Edge &a) const{
		return dis < a.dis;
	}
}edge[M<<1];

int n, m, x, y, z, fa[N], ans;

int findfa(int x){
	if(x != fa[x])	fa[x] = findfa(fa[x]);
	return fa[x];
}
void unionn(int x, int y){
	fa[findfa(y)] = findfa(x);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].dis);
	sort(edge + 1, edge + m + 1);
	int cnt = 0;
	for(int i = 1; i <= m; i++){
		if(findfa(edge[i].u) != findfa(edge[i].v)){
			unionn(edge[i].u, edge[i].v);
			cnt++;
			ans += edge[i].dis;
			if(cnt == n - 1)
				break;
		}
	}
	if(cnt != n - 1)
		return puts("orz"), 0;
	printf("%d\n", ans);
	return 0;
}
