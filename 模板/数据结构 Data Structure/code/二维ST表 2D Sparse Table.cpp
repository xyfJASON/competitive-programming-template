#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 305;

int n, m, a[N][N], q;
int lg[N], st[N][N][9][9];
void pre(){
	lg[1] = 0, lg[2] = 1;
	for(int i = 3; i <= max(n, m); i++) lg[i] = lg[i/2] + 1;
}
void init(){
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			st[i][j][0][0] = a[i][j];
	for(int ki = 0; (1 << ki) <= n; ki++){
		for(int kj = 0; (1 << kj) <= m; kj++){
			if(!ki && !kj)  continue;
			for(int i = 1; i + (1 << ki) - 1 <= n; i++){
				for(int j = 1; j + (1 << kj) - 1 <= m; j++){
					if(!ki) st[i][j][ki][kj] = max(st[i][j][ki][kj-1], st[i][j+(1<<(kj-1))][ki][kj-1]);
					else    st[i][j][ki][kj] = max(st[i][j][ki-1][kj], st[i+(1<<(ki-1))][j][ki-1][kj]);
				}
			}
		}
	}
}
int query(int u, int l, int d, int r){
	int k1 = lg[d - u + 1], k2 = lg[r - l + 1];
	return max(max(st[u][l][k1][k2], st[d-(1<<k1)+1][r-(1<<k2)+1][k1][k2]),
			   max(st[d-(1<<k1)+1][l][k1][k2], st[u][r-(1<<k2)+1][k1][k2]));
}

int main(){
	while(scanf("%d%d", &n, &m) != EOF){
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				scanf("%d", &a[i][j]);
		pre();
		init();
		scanf("%d", &q);
		while(q--){
			int u, l, d, r, res;
			scanf("%d%d%d%d", &u, &l, &d, &r);
			printf("%d ", res = query(u, l, d, r));
			if(res == a[u][l] || res == a[u][r] || res == a[d][l] || res == a[d][r])
				puts("yes");
			else    puts("no");
		}
	}
	return 0;
}
