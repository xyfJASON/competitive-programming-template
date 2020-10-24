#include<algorithm>
#include<cstdio>

using namespace std;

const int MAXT = 100005;
const int N = 10005;
int T, M, v[N], w[N], dp[MAXT];

int main(){
	scanf("%d%d", &T, &M);
	for(int i = 1; i <= M; i++)	scanf("%d%d", &v[i], &w[i]);
	for(int i = 1; i <= M; i++)
		for(int j = v[i]; j <= T; j++)
			dp[j] = max(dp[j-v[i]]+w[i], dp[j]);
	printf("%d", dp[T]);
	return 0;
}