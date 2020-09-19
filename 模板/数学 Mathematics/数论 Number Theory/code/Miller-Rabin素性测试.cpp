#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

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
		while(u % 2 == 0)	u >>= 1, t++;
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

int main(){
	LL n; scanf("%lld", &n);
	if(Miller_Rabin::test(n))	puts("YES");
	else	puts("NO");
	return 0;
}