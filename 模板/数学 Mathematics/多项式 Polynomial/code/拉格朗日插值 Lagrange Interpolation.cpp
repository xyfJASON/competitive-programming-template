#include<bits/stdc++.h>

using namespace std;

const int N = 2005;
const int MOD = 998244353;

inline int fpow(int bs, int idx){
	int res = 1;
	while(idx){
		if(idx & 1)	res = 1ll * res * bs % MOD;
		bs = 1ll * bs * bs % MOD;
		idx >>= 1;
	}
	return res;
}

int n, k;
pair<int, int> p[N];

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].first, &p[i].second);
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int up = p[i].second, dn = 1;
		for(int j = 1; j <= n; j++){
			if(j == i)	continue;
			up = 1ll * up * (k - p[j].first) % MOD;
			dn = 1ll * dn * (p[i].first - p[j].first) % MOD;
		}
		if(up < 0)	up += MOD;
		if(dn < 0)	dn += MOD;
		ans = (ans + 1ll * up * fpow(dn, MOD-2) % MOD) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}