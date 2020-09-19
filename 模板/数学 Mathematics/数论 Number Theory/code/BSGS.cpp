#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

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

int main(){
	int m, a, b; scanf("%d%d%d", &m, &a, &b);
	int ans = BSGS(a, b, m);
	if(ans == -1)	puts("no solution");
	else	printf("%d\n", ans);
	return 0;
}