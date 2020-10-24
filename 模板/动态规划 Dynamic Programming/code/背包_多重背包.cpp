#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 105;
const int M = 40005;
int n, V, v[N], w[N], c[N];
int dp[M];

int main(){
	scanf("%d%d", &n, &V);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%d", &w[i], &v[i], &c[i]);
	for(int i = 1; i <= n; i++){
		for(int p = 1; p <= c[i]; c[i] -= p, p <<= 1)
			for(int j = V; j >= p * v[i]; j--)
				dp[j] = max(dp[j], dp[j-p*v[i]] + p * w[i]);
		for(int j = V; j >= c[i] * v[i]; j--)
			dp[j] = max(dp[j], dp[j-c[i]*v[i]] + c[i] * w[i]);
	}
	printf("%d\n", dp[V]);
	return 0;
}