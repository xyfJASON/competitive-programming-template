#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 1005;

int n, m;
char a[N], b[N];

int dp[N][N], nxt[N][30], pre[30];
int LCS(){
	memset(nxt, 0x3f, sizeof nxt);
	memset(pre, 0, sizeof pre);
	for(int i = 1; i <= n; i++){
		for(int k = pre[a[i]-'a']; k < i; k++)
			nxt[k][a[i]-'a'] = i;
		pre[a[i]-'a'] = i;
	}
	for(int i = 0; i <= m; i++)
		for(int j = 0; j <= m; j++)
			dp[i][j] = j == 0 ? 0 : n + 1;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= i; j++)
			dp[i][j] = min(nxt[dp[i-1][j-1]][b[i]-'a'], dp[i-1][j]);
	int res = 0;
	for(int i = 1; i <= m; i++)
		if(dp[m][i] <= n)	res = i;
	return res;
}

int main(){
	while(scanf("%s%s", a+1, b+1) != EOF){
		n = strlen(a+1), m = strlen(b+1);
		if(n < m)	swap(n, m), swap(a, b);
		printf("%d\n", LCS());
	}
	return 0;
}