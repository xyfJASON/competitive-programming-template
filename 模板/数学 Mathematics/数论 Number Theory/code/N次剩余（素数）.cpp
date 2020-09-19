#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

int gcd(int a, int b){ return b == 0 ? a : gcd(b, a % b); }

inline int fpow(int bs, int idx, int m){
	int res = 1;
	while(idx){
		if(idx & 1)	res = 1ll * res * bs % m;
		bs = 1ll * bs * bs % m;
		idx >>= 1;
	}
	return res;
}

int getSPR(int p){
	// get the smallest primitive root of PRIME p
	vector<int> factors; // PRIME factors of phi(p)=p-1
	int phip = p - 1;
	for(int i = 2; i * i <= phip; i++){
		if(phip % i)	continue;
		factors.emplace_back(i);
		while(phip % i == 0)	phip /= i;
	} if(phip > 1)	factors.emplace_back(phip);

	int g = 0; // smallest primitive root
	for(g = 2; g <= p; g++){
		bool ok = true;
		for(auto &factor : factors){
			if(fpow(g, (p - 1) / factor, p) == 1){
				ok = false; break;
			}
		}
		if(ok)	break;
	}
	return g;
}

int BSGS(int a, int b, int m){
	// solve a^x = b (mod m)
	unordered_map<int, int> val;
	int sq = sqrt(m) + 1;
	LL an = 1;
	for(int i = 1; i <= sq; i++)	an = an * a % m;
	for(LL q = 0, cur = b; q <= sq; cur = cur * a % m, q++)
		val[cur] = q;
	for(LL p = 1, cur = an; p <= sq; cur = cur * an % m, p++)
		if(val.count(cur))
			return sq * p - val[cur];
	return -1;
}

vector<int> DiscreteRoot(int a, int b, int p){
	// solve x^a = b (mod p)
	vector<int> res;
	if(b == 0){ res.emplace_back(0); return res; }
	int g = getSPR(p);
	int c = BSGS(fpow(g, a, p), b, p);
	if(c == -1)	return res;
	int d = gcd(a, p-1);
	int delta = (p - 1) / d;
	for(int i = 0; i < d; i++){
		int cur = (c + 1ll * i * delta % (p-1)) % (p-1);
		res.emplace_back(fpow(g, cur, p));
	}
	sort(res.begin(), res.end());
	return res;
}

int main(){
	int p, a, b; scanf("%d%d%d", &p, &a, &b);
	vector<int> ans = DiscreteRoot(a, b, p);
	printf("%d\n", (int)ans.size());
	for(auto &k : ans)	printf("%d ", k);
	return 0;
}