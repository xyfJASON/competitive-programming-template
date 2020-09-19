#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

int gcd(int a, int b){ return b == 0 ? a : gcd(b, a % b); }

int exBSGS(int a, int b, int m){
	// solve a^x = b (mod m)
	int A = 1, k = 0, d;
	while((d = gcd(a, m)) > 1){
		if(b == A)	return k;
		if(b % d)	return -1;
		A = 1ll * A * (a / d) % m;
		b /= d, m /= d, k++;
	}

	unordered_map<int, int> val;
	int sq = sqrt(m) + 1;
	LL an = 1;
	for(int i = 1; i <= sq; i++)	an = an * a % m;
	for(LL q = 0, cur = b; q <= sq; cur = cur * a % m, q++)
		val[cur] = q;
	for(LL p = 1, cur = an * A % m; p <= sq; cur = cur * an % m, p++)
		if(val.count(cur))
			return sq * p - val[cur] + k;
	return -1;
}

int main(){
	int a, b, m;
	while(1){
		scanf("%d%d%d", &a, &m, &b);
		if(a + m + b == 0)	break;
		int ans = exBSGS(a, b, m);
		if(ans == -1)	puts("No Solution");
		else	printf("%d\n", ans);
	}
	return 0;
}