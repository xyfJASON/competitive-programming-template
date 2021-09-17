#include<cstdio>
#include<cmath>

using namespace std;

int n;

int getPhi(int n){
	int res = n;
	for(int i = 2; i * i <= n; i++){
		if(n % i == 0){
			res = res / i * (i - 1);
			while(n % i == 0)
				n /= i;
		}
	}
	if(n > 1)	res = res / n * (n - 1);
	// Fantastic! the only reason n > 1 here is n now is the biggest prime divisor of the original n. Think about it!
	return res;
}

int main(){
	scanf("%d", &n);
	printf("%d\n", getPhi(n));
	return 0;
}
