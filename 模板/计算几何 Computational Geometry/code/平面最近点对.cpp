#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

const double INF = 1e16;
const int N = 200005;

int n, pt;

struct Point{
	double x, y;
}p[N], t[N];
bool cmpx(Point A, Point B){
	if(A.x == B.x)	return A.y < B.y;
	return A.x < B.x;
}
bool cmpy(Point A, Point B){
	if(A.y == B.y)	return A.x < B.x;
	return A.y < B.y;
}

inline double dis(Point A, Point B){ return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }

double solve(int l, int r){
	if(l == r)	return INF;
	if(r - l == 1)	return dis(p[l], p[r]);
	int mid = (l + r) >> 1;
	double d = min(solve(l, mid), solve(mid+1, r));
	pt = 0;
	for(int i = l; i <= r; i++)
		if(fabs(p[i].x - p[mid].x) <= d)
			t[++pt] = p[i];
	sort(t+1, t+pt+1, cmpy);
	for(int i = 1; i <= pt; i++)
		for(int j = i+1; j <= pt && t[j].y - t[i].y <= d; j++)
			d = min(d, dis(t[i], t[j]));
	return d;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p+1, p+n+1, cmpx);
	printf("%.4f\n", solve(1, n));
	return 0;
}
