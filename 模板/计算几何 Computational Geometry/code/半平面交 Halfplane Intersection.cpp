#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

const double eps = 1e-6;
const double PI = acos(-1);
const double INF = 1e10;
const int N = 105;
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
bool operator == (const Vector &A, const Vector &B){
	return (cmp(A.x, B.x) == 0) && (cmp(A.y, B.y) == 0);
}
bool operator != (const Vector &A, const Vector &B){ return !(A == B); }
double operator * (Vector A, Vector B){ return A.x * B.x + A.y * B.y; } // dot product
double operator ^ (Vector A, Vector B){ return A.x * B.y - A.y * B.x; } // cross product

//------------------------------------ Line ------------------------------------//
struct Line{
	Point p;
	Vector v;
	double ang;
	Line() {}
	Line(Point p, Vector v):p(p), v(v){ ang = atan2(v.y, v.x); }
	Point getPoint(double t){ return p + v * t; }
	bool operator < (const Line &L) const{ return ang < L.ang; }
};
bool PointOnRight(Point p, Line l){ return sgn(l.v ^ (p-l.p)) < 0; }
Point GetLineIntersection(Line l1, Line l2){
	Vector u = l1.p - l2.p;
	double t = (l2.v ^ u) / (l1.v ^ l2.v);
	return l1.p + l1.v * t;
}
double PolygonArea(int n, Point p[]){
	double S = 0;
	for(int i = 2; i < n; i++)
		S += ((p[i] - p[1]) ^ (p[i+1] - p[1])) / 2;
	return S;
}

Point P[N]; // p[i] is the intersection of line q[i] and q[i+1]
Line Q[N]; // deque
void HalfplaneIntersection(Line L[], int n, Point res[], int &m){
	// L[] are the lines, n is the number of lines, res[] stores the result of the intersection (a polygon)
	// m is the number of points of the intersection (which is a polygon)
	sort(L + 1, L + n + 1);
	int head, tail;
	Q[head = tail = 0] = L[1];
	for(int i = 2; i <= n; i++){
		while(head < tail && PointOnRight(P[tail - 1], L[i]))   tail--;
		while(head < tail && PointOnRight(P[head], L[i]))   head++;
		Q[++tail] = L[i];
		if(sgn(Q[tail].v ^ Q[tail - 1].v) == 0){ // parallel, the inner one remains
			tail--;
			if(!PointOnRight(L[i].p, Q[tail]))    Q[tail] = L[i];
		}
		if(head < tail) P[tail - 1] = GetLineIntersection(Q[tail-1], Q[tail]);
	}
	while(head < tail && PointOnRight(P[tail - 1], Q[head])) tail--; // delete useless plane
	P[tail] = GetLineIntersection(Q[tail], Q[head]);

	m = 0;
	for(int i = head; i <= tail; i++)   res[++m] = P[i];
}

int T, n, resn;
Point p[N], res[N];
Line L[N];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		if(sgn(PolygonArea(n, p)) < 0)
			for(int i = 1; i <= n / 2; i++)
				swap(p[i], p[n+1-i]);
		for(int i = 1; i <= n; i++)
			L[i] = (Line){p[i], p[i==n ? 1 : i+1] - p[i]};
		HalfplaneIntersection(L, n, res, resn);
		puts(resn >= 3 ? "YES" : "NO");
	}
	return 0;
}
