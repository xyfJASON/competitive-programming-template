#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 100005;

int n;
LL a[N], m[N], M;

LL fmul(LL x, LL y, LL MOD){
	x %= MOD;
	y %= MOD;
	LL res = 0;
	while(y){
		if(y & 1)	(res += x) %= MOD;
		y >>= 1;
		(x <<= 1) %= MOD;
	}
	return res;
}

LL exgcd(LL a, LL b, LL &x, LL &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	LL gcd = exgcd(b, a % b, x, y);
	LL t = x;
	x = y;
	y = t - (a / b) * y;
	return gcd;
}

LL exCRT(int n, LL a[], LL m[]){
	LL M = m[1], x = a[1];
	LL k, y;
	for(int i = 2; i <= n; i++){
		LL c = ((a[i] - x) % m[i] + m[i]) % m[i];
		LL g = exgcd(M, m[i], k, y);
		((k %= m[i]) += m[i]) %= m[i];
		k = fmul(k, c / g, m[i] / g);
		x += k * M;
		M = M / g * m[i];
		((x %= M) += M) %= M;
	}
	((x %= M) += M) %= M;
	return x;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &m[i], &a[i]);
	printf("%lld\n", exCRT(n, a, m));
	return 0;
}