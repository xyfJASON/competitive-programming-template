#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 101;
int T, M;
int t[N], w[N];
int dp[1005] = {0};

int main(){
	scanf("%d%d", &T, &M);
	for(int i = 1; i <= M; i++)	scanf("%d%d", &t[i], &w[i]);
	for(int i = 1; i <= M; i++)
		for(int j = T; j >= t[i]; j--)
			dp[j] = max(dp[j], dp[j-t[i]] + w[i]);
	printf("%d", dp[T]);
	return 0;
}