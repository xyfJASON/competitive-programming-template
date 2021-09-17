#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL fpow(LL bs, LL idx, LL mod){
	LL res = 1;
	while(idx){
		if(idx & 1)	(res *= bs) %= mod;
		idx >>= 1;
		(bs *= bs) %= mod;
	}
	return res;
}

LL exgcd(LL a, LL b, LL &x, LL &y){ // solve ax+by=gcd(a,b)
	if(b == 0){ x = 1, y = 0; return a; }
	LL d = exgcd(b, a % b, x, y);
	LL t = x; x = y; y = t - a / b * y;
	return d;
}

inline LL inv(LL x, LL mod){
	LL res, y;
	exgcd(x, mod, res, y);
	((res %= mod) += mod) %= mod;
	return res;
}

LL F(LL n, LL p, LL pk){
	if(n == 0)	return 1;
	LL res = 1;
	for(LL i = 1; i <= pk; i++){
		if(i % p == 0)	continue;
		(res *= i) %= pk;
	}
	res = fpow(res, n / pk, pk);
	for(LL i = 1; i <= n % pk; i++){
		if(i % p == 0)	continue;
		(res *= i) %= pk;
	}
	return res * F(n / p, p, pk) % pk;
}

inline LL calc(LL n, LL m, LL p, LL pk){
	// calculate C(n,m) % pi^k
	LL res = 0;
	for(LL i = n; i; i /= p)	res += i / p;
	for(LL i = m; i; i /= p)	res -= i / p;
	for(LL i = n - m; i; i /= p)	res -= i / p;
	res = fpow(p, res, pk);
	res = F(n, p, pk) * inv(F(m, p, pk), pk) % pk * inv(F(n-m, p, pk), pk) % pk * res % pk;
	return res;
}

inline LL exLucas(LL n, LL m, LL p){
	// calculate C(n,m) % p
	LL P = p, res = 0;
	for(LL i = 2; i * i <= p; i++){
		if(p % i)	continue;
		LL pk = 1;
		while(p % i == 0)	p /= i, pk *= i;
		(res += calc(n, m, i, pk) * (P / pk) % P * inv(P / pk, pk) % P) %= P;
	}
	if(p > 1)
		(res += calc(n, m, p, p) * (P / p) % P * inv(P / p, p) % P) %= P;
	return res;
}

int main(){
	LL n, m, p; scanf("%lld%lld%lld", &n, &m, &p);
	printf("%lld\n", exLucas(n, m, p));
	return 0;
}