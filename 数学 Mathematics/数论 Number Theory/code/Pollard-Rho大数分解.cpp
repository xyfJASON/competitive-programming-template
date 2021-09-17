#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

LL gcd(LL a, LL b){ return b == 0 ? a : gcd(b, a % b); }

mt19937 rnd(time(NULL));
namespace Miller_Rabin{
	inline LL fpow(LL bs, LL idx, LL mod){
		bs %= mod;
		LL res = 1;
		while(idx){
			if(idx & 1)	res = (__int128)res * bs % mod;
			bs = (__int128)bs * bs % mod;
			idx >>= 1;
		}
		return res;
	}
	bool test(LL n){
		if(n < 3)	return n == 2;
		if(!(n & 1))	return false;
		LL u = n - 1, t = 0;
		while(u % 2 == 0)	u /= 2, t++;
		int testTime = 10;
		while(testTime--){
			LL v = rnd() % (n - 2) + 2;
			v = fpow(v, u, n);
			if(v == 1 || v == n - 1)	continue;
			int j; for(j = 0; j < t; j++, v = (__int128)v * v % n)
				if(v == n - 1)	break;
			if(j >= t)	return false;
		}
		return true;
	}
}

namespace Pollard_Rho{
	vector<LL> factors;
	// LL mxfactor = 0;
	inline LL solve(LL n){
		LL c = rnd() % (n - 1) + 1;
		LL x = 0, y = 0, val = 1;
		for(LL k = 1; ; k <<= 1, y = x, val = 1){
			for(int i = 1; i <= k; i++){
				x = ((__int128)x * x + c) % n;
				val = (__int128)val * abs(x - y) % n;
				if(val == 0)	return n;
				if(i % 127 == 0){
					LL g = gcd(val, n);
					if(g > 1)	return g;
				}
			}
			LL g = gcd(val, n);
			if(g > 1)	return g;
		}
	}
	void factorize(LL n){
		if(n < 2)	return;
		// if(n <= mxfactor)	return;
		if(Miller_Rabin::test(n)){
			factors.emplace_back(n);
			// mxfactor = max(mxfactor, n);
			return;
		}
		LL p = n;
		while(p == n)	p = solve(n);
		while(n % p == 0)	n /= p;
		factorize(p), factorize(n);
	}
}

int main(){
	int T; for(scanf("%d", &T); T; T--){
		LL n; scanf("%lld", &n);
		// Pollard_Rho::mxfactor = 0;
		Pollard_Rho::factors.clear();
		Pollard_Rho::factorize(n);
		for(auto &k : Pollard_Rho::factors)
			printf("%lld ", k); puts("");
		// LL mxfactor = Pollard_Rho::mxfactor;
		// if(mxfactor == n)	puts("Prime");
		// else	printf("%lld\n", mxfactor);
	}
	return 0;
}