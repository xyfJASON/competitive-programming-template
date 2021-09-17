#include<cstdio>

using namespace std;

const int N = 500005;
int n, m, opt, u, v, a;

int c[N];
inline int lowbit(int x){ return x & -x; }
inline int querySum(int x){
	int res = 0;
	for(; x; x -= lowbit(x))	res += c[x];
	return res;
}
inline void add(int x, int v){
	for(; x <= n; x += lowbit(x))	c[x] += v;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		add(i, a);
	}
	while(m--){
		scanf("%d%d%d", &opt, &u, &v);
		if(opt == 1)	add(u, v);
		else	printf("%d\n", querySum(v) - querySum(u-1));
	}
	return 0;
}