#include<bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m;
double a[N][N];

int RowEchelon(double a[][N]){
	// change a to row-echelon from and return the rank of a
	int cnt = 0;
	for(int r = 1, c = 1; r <= n && c <= m; c++){
		if(a[r][c] == 0){
			int t = r;
			while(t+1 <= n && a[t+1][c] == 0)	t++;
			t++;
			if(t == n+1)	continue;
			swap(a[r], a[t]);
		}
		for(int i = r+1; i <= n; i++){
			double div = a[i][c] / a[r][c];
			for(int k = c; k <= m; k++)
				a[i][k] -= div * a[r][k];
		}
		r++, cnt++;
	}
	return cnt;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lf", &a[i][j]);

	int rnk = RowEchelon(a);

	printf("%d\n", rnk);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			printf("%lf ", a[i][j]);
		puts("");
	}
	return 0;
}