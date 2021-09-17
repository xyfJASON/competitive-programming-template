#include<bits/stdc++.h>

using namespace std;

const int N = 100005;

int n, a[N], b[N], t[N];

int dp[N];
int LIS(int a[]){
	// 长度为 i 的上升子序列的最小末尾数值是 dp[i]
	int len = 0;
	for(int i = 1; i <= n; i++){
		int p = lower_bound(dp+1, dp+len+1, a[i]) - dp;
		if(p == len + 1)	len++;
		dp[p] = a[i];
	}
	return len;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)	scanf("%d", &a[i]), t[a[i]] = i;
	for(int i = 1; i <= n; i++)	scanf("%d", &b[i]), b[i] = t[b[i]];
	printf("%d\n", LIS(b));
	return 0;
}