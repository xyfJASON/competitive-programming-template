#include<cstdio>

using namespace std;

const double eps = 1e-8;
const int N = 20;

int n;
double l, r, a[N];

double func(double x){
	double res = 0, xx = 1;
	for(int i = 0; i <= n; i++){
		res += a[i] * xx;
		xx *= x;
	}
	return res;
}

double tripartition(double l, double r){
	double mid1 = l, mid2 = r;
	while(mid2 - mid1 >= eps){
		mid1 = l + (r - l) / 3;
		mid2 = r - (r - l) / 3;
		if(func(mid1) <= func(mid2))	l = mid1;
		else	r = mid2;
	}
	return l;
}

/*     interger version
int tripartition(int l, int r){
	int mid1 = l, mid2 = r;
	while(mid1 < mid2){
		mid1 = l + (r - l) / 3;
		mid2 = r - (r - l) / 3;
		if(func(mid1) < func(mid2))	l = mid1 + 1;
		else	r = mid2 - 1;
	}
	return l;
}
*/

int main(){
	scanf("%d%lf%lf", &n, &l, &r);
	for(int i = n; i >= 0; i--)
		scanf("%lf", &a[i]);
	printf("%.5f\n", tripartition(l, r));
	return 0;
}
