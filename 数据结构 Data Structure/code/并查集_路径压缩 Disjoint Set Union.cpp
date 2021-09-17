#include<cstdio>

using namespace std;

const int N = 10005;
int n, m, x, y, z;

int fa[N];
int findfa(int x){ return x == fa[x] ? x : fa[x] = findfa(fa[x]); }
inline void unionn(int x, int y){ fa[findfa(y)] = findfa(x); }

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	while(m--){
		scanf("%d%d%d", &z, &x, &y);
		if(z == 1)
			unionn(x, y);
		else if(z == 2)
			puts(findfa(x) == findfa(y) ? "Y" : "N");
	}
	return 0;
}
