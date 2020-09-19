#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

double a, b, c, d;
double f(double x){ // the function
	return (c * x + d) / (a * x + b);
}
double simpson(double l, double r){
	double mid = (l + r) / 2;
	return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6;
}
double solve(double l, double r, double _eps, double I){
	double mid = (l + r) / 2;
	double Il = simpson(l, mid), Ir = simpson(mid, r);
	if(fabs(Il + Ir - I) <= 15 * _eps)   return Il + Ir + (Il + Ir - I) / 15;
	return solve(l, mid, _eps / 2, Il) + solve(mid, r, _eps / 2, Ir);
}

int main(){
	double l, r;
	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
	printf("%.6f\n", solve(l, r, 1e-7, simpson(l, r)));
	return 0;
}