#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 100005;

LL n, m, p, fac[N], inv[N];

LL C(LL n, LL m, LL p){
	if(m > n)	return 0;
	return fac[n] * inv[fac[m]] % p * inv[fac[n-m]] % p;
}

LL lucas(LL n, LL m, LL p){
	if(m == 0)	return 1;
	return C(n%p, m%p, p) * lucas(n/p, m/p, p) % p;
}

int main(){
	scanf("%lld%lld%lld", &n, &m, &p);
	fac[0] = 1;
	for(int i = 1; i <= p; i++)
		fac[i] = fac[i-1] * i % p;
	inv[1] = 1;
	for(int i = 2; i <= p; i++){
		inv[i] = -(p / i) * inv[p % i];
		((inv[i] %= p) += p) %= p;
	}
	printf("%lld\n", lucas(n, m, p));
	return 0;
}
