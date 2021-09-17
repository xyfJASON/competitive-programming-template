#include<cstdio>

using namespace std;

int fpow(int base, int idx, int MOD){
	int res = 1;
	base %= MOD;
	while(idx){
		if(idx & 1)	(res *= base) %= MOD;
		idx >>= 1;
		(base *= base) %= MOD;
	}
	return res % MOD;
}

int n, p;

int main(){
	scanf("%d%d", &n, &p);
	printf("%d\n", fpow(n, p-2, p));
	return 0;
}
