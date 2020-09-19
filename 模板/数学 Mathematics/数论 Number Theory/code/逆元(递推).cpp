#include<cstdio>

using namespace std;

typedef long long LL;

const int N = 3000005;

LL n, p, inv[N];

int main(){
	scanf("%lld%lld", &n, &p);
	inv[1] = 1;
	printf("%lld\n", inv[1]);
	for(int i = 2; i <= n; i++){
		inv[i] = -(p / i) * inv[p % i];
		((inv[i] %= p) += p) %= p;
		printf("%lld\n", inv[i]);
	}
	return 0;
}
