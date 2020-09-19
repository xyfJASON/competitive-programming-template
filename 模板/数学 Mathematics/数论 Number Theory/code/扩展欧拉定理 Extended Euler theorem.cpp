#include<cstdio>
#include<cmath>

using namespace std;

typedef long long LL;

LL a, m, b, p;
bool flag = 0;

LL getPhi(LL x){
	LL sqr = sqrt(x);
	LL res = x;
	for(LL i = 2; i <= sqr; i++){
		if(x % i == 0){
			res = res / i * (i - 1);
			while(x % i == 0)
				x /= i;
		}
	}
	if(x > 1)
		res = res / x * (x - 1);
	return res;
}

LL scan(){
	char ch = getchar();
	LL res = 0;
	while(1){
		ch = getchar();
		if(ch > '9' || ch < '0')
			break;
		(res *= 10) += (ch - '0');
		if(res >= p){
			flag = 1;
			res %= p;
		}
	}
	return res;
}

LL fpow(LL base, LL idx, LL MOD){
	LL res = 1;
	base %= MOD;
	while(idx){
		if(idx & 1)	(res *= base) %= MOD;
		idx >>= 1;
		(base *= base) %= MOD;
	}
	return res;
}

int main(){							// solve a^b mod m, where b is damn big
	scanf("%lld%lld", &a, &m);
	p = getPhi(m);
	b = scan();
	b += flag * p;
	printf("%lld\n", fpow(a, b, m));
	return 0;
}
