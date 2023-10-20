#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const double INF = 1e18;
const int N = 200005;

int n, pt;

struct Point{
	double x, y;
	bool operator < (const Point& A) const{
		return x < A.x;
	}
}p[N], t[N];

inline double dis(Point A, Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

double solve(int l, int r){
	if(l >= r)	return INF;
	int mid = (l + r) >> 1;
	double midx = p[mid].x;
	double d = min(solve(l, mid), solve(mid+1, r));
	// merge and sort by y
	pt = 0;
	int lpt = l, rpt = mid + 1;
	while(lpt <= mid && rpt <= r){
		if(p[lpt].y < p[rpt].y)	t[++pt] = p[lpt++];
		else	t[++pt] = p[rpt++];
	}
	while(lpt <= mid)	t[++pt] = p[lpt++];
	while(rpt <= r)		t[++pt] = p[rpt++];
	for(int i = l; i <= r; i++)	p[i] = t[i-l+1];
	// update answer
	pt = 0;
	for(int i = l; i <= r; i++)
		if(fabs(p[i].x - midx) < d)
			t[++pt] = p[i];
	for(int i = 1; i <= pt; i++)
		for(int j = i+1; j <= pt && t[j].y - t[i].y <= d; j++)
			d = min(d, dis(t[i], t[j]));
	return d;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p+1, p+n+1);
	printf("%.4f\n", solve(1, n));
	return 0;
}