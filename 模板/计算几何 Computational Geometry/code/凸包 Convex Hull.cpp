#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

const double eps = 1e-6;
inline int sgn(double x){
	if(fabs(x) < eps)	return 0;
	else if(x > 0)	return 1;
	else	return -1;
}
inline int cmp(double x, double y){
	if(fabs(x-y) < eps)	return 0;
	else if(x > y)	return 1;
	else	return -1;
}


//------------------------------------ Vector & Point ------------------------------------//
struct Vector{
	double x, y;
	Vector(double x = 0, double y = 0):x(x), y(y){}
};
typedef Vector Point;
Vector operator - (Vector A, Vector B){ return Vector{A.x - B.x, A.y - B.y}; }
bool operator < (const Vector &A, const Vector &B){ return cmp(A.x, B.x) == 0 ? cmp(A.y, B.y) < 0 : cmp(A.x, B.x) < 0; }
bool operator == (const Vector &A, const Vector &B){
	return (cmp(A.x, B.x) == 0) && (cmp(A.y, B.y) == 0);
}
bool operator != (const Vector &A, const Vector &B){ return !(A == B); }
double operator * (Vector A, Vector B){ return A.x * B.x + A.y * B.y; } // dot product
double operator ^ (Vector A, Vector B){ return A.x * B.y - A.y * B.x; } // cross product
double Length(Vector A){ return sqrt(A * A); }
bool ToTheLeft(Point A, Point B, Point C){ return sgn(((B - A) ^ (C - B))) > 0; } // test if vector(bc) is to the left of (ab)
bool ToTheLeft(Vector A, Vector B){ return sgn(A ^ B) > 0; } // test if vector B is to the left of vector A

const int N = 10005;

int n, resn;
Point coo[N];
Point res[N];

void ConvexHull(int n, Point p[], Point sta[], int &staid){
	sort(p+1, p+n+1);
	n = unique(p+1, p+n+1) - (p+1);
	staid = 0;
	for(int i = 1; i <= n; i++){
//        while(staid > 1 && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid])) < 0) staid--;
		while(staid > 1 && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid])) <= 0) staid--;
		sta[++staid] = p[i];
	}
	int k = staid;
	for(int i = n-1; i >= 1; i--){
//        while(staid > k && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid])) < 0) staid--;
		while(staid > k && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid])) <= 0) staid--;
		sta[++staid] = p[i];
	}
	if(n > 1)   staid--;
}

double ans;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lf%lf", &coo[i].x, &coo[i].y);
	ConvexHull(n, coo, res, resn);
	res[resn+1] = res[1];
	for(int i = 1; i <= resn; i++)
		ans += Length(res[i+1] - res[i]);
	printf("%.2f\n", ans);
	return 0;
}
