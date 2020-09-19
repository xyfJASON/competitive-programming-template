#include<cstdio>

using namespace std;

int a, b, c, x, y; // solve ax+by=c

int exgcd(int a, int b, int &x, int &y){ // solve ax+by=gcd(a,b)
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
	scanf("%d%d%d", &a, &b, &c);
	int GCD = exgcd(a, b, x, y);
	if(c % GCD){
		puts("No solution!");
		return 0;
	}
	printf("%d %d\n", x, y);
	return 0;
}
