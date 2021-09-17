#include<bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, x[N], y[N], w[N];

double ansx, ansy, ans;

#define T0 3000
#define Tk 1e-15
#define cool 0.996
#define MAX_TIME 0.75
inline double Rand(){ return (double)rand() / RAND_MAX; }
inline double calc(double xx, double yy){
	double res = 0;
	for(int i = 1; i <= n; i++)
		res += sqrt((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i])) * w[i];
	if(res < ans)	ans = res, ansx = xx, ansy = yy;
	return res;
}
void simulateAnneal(){
	double T = T0;
	double nowx = ansx, nowy = ansy;
	while(T > Tk){
		double nxtx = nowx + T * (rand()*2-RAND_MAX);
		double nxty = nowy + T * (rand()*2-RAND_MAX);
		double deltaE = calc(nxtx, nxty) - calc(nowx, nowy);
		if(Rand() < exp(-deltaE / T))	nowx = nxtx, nowy = nxty;
		T *= cool;	
	}
	for(int i = 1; i <= 1000; i++){
		double nxtx = ansx + T * (2*Rand()-1);
		double nxty = ansy + T * (2*Rand()-1);
		calc(nxtx, nxty);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", &x[i], &y[i], &w[i]);
		ansx += x[i], ansy += y[i];
	}
	ansx /= n, ansy /= n, ans = calc(ansx, ansy);
	while((double)clock()/CLOCKS_PER_SEC < MAX_TIME)
		simulateAnneal();
	printf("%.3f %.3f\n", ansx, ansy);
	return 0;
}