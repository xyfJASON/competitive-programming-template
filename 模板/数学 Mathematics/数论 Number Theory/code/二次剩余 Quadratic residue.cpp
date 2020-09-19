#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define mp(x, y) make_pair(x, y)

mt19937 rnd(time(NULL));

namespace Quadratic_Residue{
	LL w; // w = omega^2 (i^2)
	struct Complex{
		LL r, i;
		Complex() {}
		Complex(LL rr, LL ii): r(rr), i(ii) {}
	};
	inline Complex mul(Complex a, Complex b, LL mod){
		Complex res;
		res.r = (a.r * b.r % mod + a.i * b.i % mod * w % mod) % mod;
		res.i = (a.r * b.i % mod + a.i * b.r % mod) % mod;
		return res;
	}
	inline Complex fpow(Complex bs, LL idx, LL mod){
		// fast pow for complex numbers
		Complex res(1, 0);
		while(idx){
			if(idx & 1)	res = mul(res, bs, mod);
			bs = mul(bs, bs, mod);
			idx >>= 1;
		}
		return res;
	}
	inline int isQR(LL n, LL p){
		// return the value of Legendre symbol
		// 1: n is quadratic residue; -1: n is quadratic non-residue; 0: n%p==0
		n %= p;
		if(n == 0)	return 0;
		if(fpow(Complex(n, 0), (p-1)>>1, p).r == 1)	return 1;
		else	return -1;
	}
	pair<LL, LL> solve(LL n, LL p){
		// solve x^2=n(mod p)
		if(isQR(n, p) == -1)	return mp(-1, -1);
		n %= p; if(n == 0) return mp(0, 0);
		LL a;
		while(1){
			a = uniform_int_distribution<LL>(1, p-1)(rnd);
			w = ((a * a % p - n) % p + p) % p;
			if(isQR(w, p) == -1)	break;
		}
		Complex x(a, 1);
		x = fpow(x, (p+1)>>1, p);
		if(x.r > p - x.r)	x.r = p - x.r;
		return mp(x.r, p - x.r);
	}
}

LL n, p;

int main(){
	int T; for(scanf("%d", &T); T; T--){
		scanf("%lld%lld", &n, &p);
		if(Quadratic_Residue::isQR(n, p) == -1)
			puts("Hola!");
		else{
			pair<LL, LL> ans = Quadratic_Residue::solve(n, p);
			if(ans.first == ans.second)	printf("%lld\n", ans.first);
			else	printf("%lld %lld\n", ans.first, ans.second);
		}
	}
	return 0;
}