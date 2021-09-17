#include<algorithm>
#include<cstdio>
#include<cstring>
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
Vector operator + (Vector A, Vector B){ return Vector{A.x + B.x, A.y + B.y}; }
Vector operator - (Vector A, Vector B){ return Vector{A.x - B.x, A.y - B.y}; }
Vector operator * (double k, Vector A){ return Vector{k * A.x, k * A.y}; }
Vector operator * (Vector A, double k){ return k * A; }
Vector operator / (Vector A, double k){ return Vector{A.x / k, A.y / k}; }
bool operator < (const Vector &A, const Vector &B){ return cmp(A.x, B.x) == 0 ? cmp(A.y, B.y) < 0 : cmp(A.x, B.x) < 0; }
bool operator > (const Vector &A, const Vector &B){ return B < A; }
bool operator == (const Vector &A, const Vector &B){ return (cmp(A.x, B.x) == 0) && (cmp(A.y, B.y) == 0); }
bool operator != (const Vector &A, const Vector &B){ return !(A == B); }
double operator * (Vector A, Vector B){ return A.x * B.x + A.y * B.y; } // dot product
double operator ^ (Vector A, Vector B){ return A.x * B.y - A.y * B.x; } // cross product
double Length(Vector A){ return sqrt(A * A); }
double Angle(Vector A, Vector B){ return acos(A * B / Length(A) / Length(B)); }
double ParallelogramArea(Point A, Point B, Point C){ return (B - A) ^ (C - A); } // calculate the signed area of the parallelogram formed by vector(AB) and vector(AC)
double ParallelogramArea(Vector v1, Vector v2){ return v1 ^ v2; } // calculate the signed area of the parallelogram formed by vector v1 and v2
Vector Rotate(Vector A, double rad){ // rotate rad counterclockwise
	return Vector{A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)};
}
Vector Normal(Vector A){ // get the normal vector of A
	double L = Length(A);
	return Vector{-A.y/L, A.x/L};
}
Vector Symmetry(Vector A, Vector B){ // get the symmetry vector of A about B
	return 2 * B * (A * B / (B * B)) - A;
}
bool ToTheLeft(Point A, Point B, Point C){ return sgn((B - A) ^ (C - B)) > 0; } // test if vector(bc) is to the left of (ab)
bool ToTheLeft(Vector A, Vector B){ return sgn(A ^ B) > 0; } // test if vector B is to the left of vector A
double DistancePointToPoint(Point A, Point B){ return Length(A-B); }

double TriangleArea(Point A, Point B, Point C){ return (B - A) ^ (C - A) / 2; }

const int N = 50005;

int n;
Point coo[N];
Point res[N]; int resn;

void ConvexHull(int n, Point p[], Point sta[], int &staid){
	sort(p+1, p+n+1);
	n = unique(p+1, p+n+1) - (p+1);
	staid = 0;
	for(int i = 1; i <= n; i++){
//      while(staid > 1 && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid-1])) < 0) staid--;  // points on edge
		while(staid > 1 && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid-1])) <= 0) staid--; // no points on edge
		sta[++staid] = p[i];
	}
	int k = staid;
	for(int i = n-1; i >= 1; i--){
//      while(staid > k && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid-1])) < 0) staid--;  // points on edge
		while(staid > k && sgn((sta[staid]-sta[staid-1]) ^ (p[i]-sta[staid-1])) <= 0) staid--; // no points on edge
		sta[++staid] = p[i];
	}
	if(n > 1)   staid--;
}

int ans;
void RotatingCalipers(int m, Point p[]){ // p[] = sta[], m = staid in ConvexHull()
	if(m == 2){
		ans = (int)( (p[1] - p[2]) * (p[1] - p[2]) );
		return;
	}
	p[m+1] = p[1];
	int ver = 2;
	for(int i = 1; i <= m; i++){
		while(TriangleArea(p[i], p[i+1], p[ver]) < TriangleArea(p[i], p[i+1], p[ver+1])){
			ver++;
			if(ver == m+1)    ver = 1;
			ans = max(ans, (int)max((p[ver] - p[i]) * (p[ver] - p[i]), (p[ver] - p[i+1]) * (p[ver] - p[i+1])));
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lf%lf", &coo[i].x, &coo[i].y);
	ConvexHull(n, coo, res, resn);
	RotatingCalipers(resn, res);
	printf("%d\n", ans);
	return 0;
}
