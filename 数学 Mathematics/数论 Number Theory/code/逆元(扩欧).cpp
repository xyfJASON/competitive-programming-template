#include<cstdio>

using namespace std;

int a, b, x, y;

int exgcd(int a, int b, int &x, int &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return d;
}

int main(){
	scanf("%d%d", &a, &b);
	int GCD = exgcd(a, b, x, y);
	if(GCD != 1){
		puts("No inverse!");
		return 0;
	}
	((x %= b) += b) %= b;
	printf("%d\n", x);
	return 0;
}
