#include<algorithm>
#include<cstdio>

using namespace std;

long long n, k, ans;

int main(){
	scanf("%lld%lld", &n, &k);
	ans = 1ll * n * k;
	for(long long l = 1, r; l <= n; l = r + 1){
		if(k / l == 0)	r = n;
		else	r = min(n, k / (k / l));
		ans -= (k / l) * (l + r) * (r - l + 1) / 2;
	}
	printf("%lld\n", ans);
	return 0;
}