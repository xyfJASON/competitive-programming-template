#include<cstdio>

using namespace std;

int a, b;

int gcd(int a, int b){
	if(b == 0)	return a;
	return gcd(b, a % b);
}

int lcm(int a, int b){
	return a / gcd(a, b) * b;
}

int main(){
	scanf("%d%d", &a, &b);
	printf("%d %d\n", gcd(a, b), lcm(a, b));
	return 0;
}
