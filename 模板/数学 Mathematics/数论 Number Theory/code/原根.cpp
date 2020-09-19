#include<algorithm>
#include<cstdio>
#include<vector>

using namespace std;

const int N = 1000005;

int gcd(int a, int b){ return b == 0 ? a : gcd(b, a % b); }

int phi[N], pList[N], pID;
bool notP[N];
bool existRoot[N];
void Euler(int n){
	notP[0] = notP[1] = 1, phi[1] = 1;
	existRoot[1] = existRoot[2] = existRoot[4] = true;
	for(int i = 1; i <= n; i++){
		if(notP[i] == 0){
			pList[++pID] = i, phi[i] = i - 1;
			if(i != 2){
				for(long long j = i; j <= n; j *= i){
					existRoot[j] = true;
					if(j * 2 <= n)	existRoot[j*2] = true;
				}
			}
		}
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0){
				phi[i * pList[j]] = phi[i] * pList[j];
				break;
			}
			else	phi[i * pList[j]] = phi[i] * (pList[j] - 1);
		}
	}
}

inline int fpow(int bs, int idx, int m){
	int res = 1;
	while(idx){
		if(idx & 1)	res = 1ll * res * bs % m;
		bs = 1ll * bs * bs % m;
		idx >>= 1;
	}
	return res;
}

vector<int> getPrimitiveRoot(int m){
	vector<int> res;
	if(!existRoot[m])	return res;

	vector<int> factors; // get PRIME factors of phi(m)
	int phim = phi[m];
	for(int i = 2; i * i <= phim; i++){
		if(phim % i)	continue;
		factors.emplace_back(i);
		while(phim % i == 0)	phim /= i;
	} if(phim > 1)	factors.emplace_back(phim);

	int g = 0; // smallest primitive root
	for(g = 2; g <= m; g++){
		if(gcd(g, m) != 1)	continue;
		bool ok = true;
		for(auto &factor : factors){
			if(fpow(g, phi[m] / factor, m) == 1){
				ok = false; break;
			}
		}
		if(ok)	break;
	}
	for(int s = 1, cur = 1; s <= phi[m]; s++){
		cur = 1ll * cur * g % m;
		if(gcd(s, phi[m]) == 1)
			res.emplace_back(cur);
	}
	sort(res.begin(), res.end());
	return res;
}

int main(){
	Euler(1000000);
	int T; for(scanf("%d", &T); T; T--){
		int n, d; scanf("%d%d", &n, &d);
		if(!existRoot[n]){ puts("0"), puts(""); continue; }
		vector<int> ans = getPrimitiveRoot(n);
		int sz = ans.size();
		printf("%d\n", sz);
		for(int i = d; i <= sz; i += d)
			printf("%d ", ans[i-1]);
		puts("");
	}
	return 0;
}