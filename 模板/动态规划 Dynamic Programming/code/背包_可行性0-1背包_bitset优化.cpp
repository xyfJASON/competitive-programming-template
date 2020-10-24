#include<bits/stdc++.h>

using namespace std;

const int N = 5005;
const int M = 50005;

int V, n, v[N];
bitset<M> dp;

int main(){
	scanf("%d%d", &V, &n);
	for(int i = 1; i <= n; i++)	scanf("%d", &v[i]);
	dp.set(0);
	for(int i = 1; i <= n; i++)	dp |= dp << v[i];
	for(int i = V; i >= 0; i--){
		if(dp[i]){
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}