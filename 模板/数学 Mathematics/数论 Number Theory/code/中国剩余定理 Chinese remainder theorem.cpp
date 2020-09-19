#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 25;

int n;
LL a[N], m[N], M[N] = {1};

void exgcd(LL a, LL b, LL &x, LL &y){
	if(b == 0){
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, x, y);
	LL t = x;
	x = y;
	y = t - (a / b) * y;
}

inline LL inv(LL x, LL MOD){
	LL res, y;
	exgcd(x, MOD, res, y);
	((res %= MOD) += MOD) %= MOD;
	return res;
}

LL CRT(){
	LL x = 0;
	for(int i = 1; i <= n; i++){
		(x += a[i] * M[i] % M[0] * inv(M[i], m[i]) % M[0]) %= M[0];
	}
	return x;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld%lld", &m[i], &a[i]);
		M[0] *= m[i];
	}
	for(int i = 1; i <= n; i++)	M[i] = M[0] / m[i];
	printf("%lld\n", CRT());
	return 0;
}