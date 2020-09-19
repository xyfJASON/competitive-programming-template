#include<cstdio>

using namespace std;

typedef long long LL;

LL x, y, m;

LL fmul(LL x, LL y, LL MOD){
	x %= MOD;
	y %= MOD;
	LL res = 0;
	while(y){
		if(y & 1)	(res += x) %= MOD;
		y >>= 1;
		(x <<= 1) %= MOD;
	}
	return res;
}

int main(){
	scanf("%lld%lld%lld", &x, &y, &m);
	printf("%lld\n", fmul(x, y, m));
	return 0;
}
