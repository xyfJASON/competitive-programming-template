#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 1005;

int n, m;
char a[N], b[N];

int dp[N][N];
int LCS(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp[i][j] = 0;
			if(a[i] == b[j])	dp[i][j] = dp[i-1][j-1] + 1;
			else	dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[n][m];
}

int main(){
	freopen("data.in", "r", stdin);
	freopen("nm.out", "w", stdout);
	while(scanf("%s%s", a+1, b+1) != EOF){
		n = strlen(a+1), m = strlen(b+1);
		printf("%d\n", LCS());
	}
	return 0;
}