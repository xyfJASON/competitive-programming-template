#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int N = 1000005;

int n, a[N], fact[N], ans;

int c[N];
inline int lowbit(int x){ return x & -x; }
inline void add(int x, int val){
	while(x <= n){
		c[x] += val;
		x += lowbit(x);
	}
}
inline int sum(int x){
	int res = 0;
	while(x){
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}

int main(){
	fact[0] = 1; for(int i = 1; i <= 1000000; i++) fact[i] = 1ll * fact[i-1] * i % MOD;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		ans = (ans + 1ll * (a[i] - sum(a[i]) - 1) * fact[n-i] % MOD) % MOD;
		add(a[i], 1);
	}
	printf("%d\n", ans + 1);
	return 0;
}