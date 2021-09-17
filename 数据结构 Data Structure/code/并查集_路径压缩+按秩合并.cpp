#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 10005;

int n, m;

int fa[N], sz[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
inline void unionn(int x, int y){
	x = findfa(x), y = findfa(y);
	if(x == y)  return;
	if(sz[x] < sz[y])   swap(x, y);
	fa[y] = x, sz[x] += sz[y];
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	while(m--){
		int x, y, z; scanf("%d%d%d", &z, &x, &y);
		if(z == 1)  unionn(x, y);
		else if(z == 2) puts(findfa(x) == findfa(y) ? "Y" : "N");
	}
	return 0;
}
