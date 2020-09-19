#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 100005;

int n, m, l, r, st[N][25], lg[N];

void pre(){
	lg[1] = 0;
	lg[2] = 1;
	for(int i = 3; i <= n; i++)
		lg[i] = lg[i/2] + 1;
}
void init(){
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}

int query(int l, int r){
	int k = lg[r - l + 1];
	return max(st[l][k], st[r-(1<<k)+1][k]);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &st[i][0]);
	pre();
	init();
	while(m--){
		scanf("%d%d", &l, &r);
		printf("%d\n", query(l, r));
	}
	return 0;
}
