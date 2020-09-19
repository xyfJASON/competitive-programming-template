#include<cstdio>

using namespace std;

typedef long long LL;
LL b, p, k;

LL fpow(LL base, LL idx){
	LL res = 1;
	base %= k;
	while(idx){
		if(idx & 1)	(res *= base) %= k;
		idx >>= 1;
		(base *= base) %= k;
	}
	return res % k;
}

int main(){
	scanf("%lld%lld%lld", &b, &p, &k);
	printf("%lld^%lld mod %lld=%lld\n", b, p, k, fpow(b, p));
	return 0;
}
