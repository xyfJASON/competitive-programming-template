#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 5000005;

int mu[N], pList[N], pID;
bool notP[N];
void Euler(int n){
	notP[0] = notP[1] = 1;
	mu[1] = 1;
	for(int i = 1; i <= n; i++){
		if(notP[i] == 0){
			pList[++pID] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0){
				mu[i * pList[j]] = 0;
				break;
			}
			else	mu[i * pList[j]] = -mu[i];
		}
	}
}

unordered_map<LL, LL> muS;
LL preS[N];
LL apiadu_mu(LL n){
	if(n <= 5000000)	return preS[n];
	if(muS.find(n) != muS.end())	return muS[n];
	LL res = 1;
	for(LL l = 2, r; l <= n; l = r + 1){
		r = n / (n / l);
		res -= apiadu_mu(n / l) * (r - l + 1);
	}
	return muS[n] = res;
}
LL apiadu_phi(LL n){
	LL res = 0;
	for(LL l = 1, r; l <= n; l = r + 1){
		r = n / (n / l);
		res += (__int128)(n/l)*(n/l+1)/2 * (apiadu_mu(r) - apiadu_mu(l-1));
	}
	return res;
}

int main(){
	Euler(5000000);
	for(int i = 1; i <= 5000000; i++)
		preS[i] = preS[i-1] + mu[i];
	int T; for(scanf("%d", &T); T; T--){
		LL n;
		scanf("%lld", &n);
		printf("%lld %lld\n", apiadu_phi(n), apiadu_mu(n));
	}
	return 0;
}