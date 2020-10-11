#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const LL MOD = 998244353;
const LL G = 3;
const LL invG = 332748118;

inline LL fpow(LL bs, LL idx){
	LL res = 1;
	while(idx){
		if(idx & 1)	(res *= bs) %= MOD;
		(bs *= bs) %= MOD;
		idx >>= 1;
	}
	return res;
}

namespace NTT{
	int n;
	vector<int> rev;
	inline void preprocess(int _n, int _m){
		int cntBit = 0;
		for(n = 1; n <= _n + _m; n <<= 1, cntBit++);
		// n == 2^cntBit is a upper bound of _n+_m
		rev.resize(n);
		for(int i = 0; i < n; i++)
			rev[i] = (rev[i>>1]>>1) | ((i&1) << (cntBit-1));
			// rev[k] is bit-reversal permutation of k
	}
	inline void ntt(vector<LL> &A, int flag){
		// flag == 1: NTT; flag == -1: INTT
		A.resize(n);
		for(int i = 0; i < n; i++) if(i < rev[i]) swap(A[i], A[rev[i]]);
		for(int m = 2; m <= n; m <<= 1){
			LL wm = flag == 1 ? fpow(G, (MOD-1)/m) : fpow(invG, (MOD-1)/m);
			for(int k = 0; k < n; k += m){
				LL w = 1;
				for(int j = 0; j < m / 2; j++){
					LL t = w * A[k+j+m/2] % MOD, u = A[k+j];
					A[k+j] = (u + t) % MOD;
					A[k+j+m/2] = (u - t + MOD) % MOD;
					w = w * wm % MOD;
				}
			}
		}
		if(flag == -1){
			LL inv = fpow(n, MOD-2);
			for(int i = 0; i < n; i++)
				(A[i] *= inv) %= MOD;
		}
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	vector<LL> f(n+1), g(m+1);
	for(int i = 0; i <= n; i++)	scanf("%lld", &f[i]);
	for(int i = 0; i <= m; i++)	scanf("%lld", &g[i]);
	NTT::preprocess(n, m);
	NTT::ntt(f, 1); // f used to be coefficients, now they're point-values
	NTT::ntt(g, 1); // g used to be coefficients, now they're point-values
	for(int i = 0; i < NTT::n; i++)	f[i] = f[i] * g[i];
	NTT::ntt(f, -1); // f used to be point-values, now they're coefficients
	for(int i = 0; i < n + m + 1; i++)
		printf("%lld ", f[i]);
	return 0;
}