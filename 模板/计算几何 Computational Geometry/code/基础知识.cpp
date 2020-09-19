#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1);
const double INF = 1e16;
const int N = 10005;
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
double rand01(){ return rand() / (double)RAND_MAX; }
double randeps(){ return (rand01() - 0.5) * eps; }

//------------------------------------ Vector & Point ------------------------------------//
struct Vector{
	double x, y;
	Vector(double x = 0, double y = 0):x(x), y(y){}
	void read(){ scanf("%lf%lf", &x, &y); }
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
double Angle(Vector A){ return atan2(A.y, A.x); } // polar angle of vector A
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
bool PointOnLine(Point p, Line l){ return sgn(l.v ^ (p-l.p)) == 0; }
bool PointOnRight(Point p, Line l){ return sgn(l.v ^ (p-l.p)) < 0; }
bool LineParallel(Line l1, Line l2){ return sgn(l1.v ^ l2.v) == 0; }
bool LineSame(Line l1, Line l2){ return LineParallel(l1, l2) && sgn((l1.p-l2.p) ^ l1.v) == 0; }
Point GetLineIntersection(Line l1, Line l2){
	Vector u = l1.p - l2.p;
	double t = (l2.v ^ u) / (l1.v ^ l2.v);
	return l1.p + l1.v * t;
}
double DistancePointToLine(Point p, Line l){ return fabs(((p - l.p) ^ l.v) / Length(l.v)); }
double DistancePointToLine(Point p, Point A, Point B){ return fabs(((B - A) ^ (p - A)) / Length(B - A)); }
double DistancePointToSegment(Point p, Point A, Point B){
	if(A == B)
		return DistancePointToPoint(p, A);
	Vector v1 = p - A, v2 = p - B, v3 = A - B; // v1:vector(Ap), v2:vector(Bp), v3:vector(BA)
	if(sgn(v1 * v3) > 0)
		return DistancePointToPoint(p, A);
	if(sgn(v2 * v3) < 0)
		return DistancePointToPoint(p, B);
	return DistancePointToLine(p, A, B);
}
Point PointLineProjection(Point p, Line l){ return l.p + l.v * ((l.v * (p - l.p)) / (l.v * l.v)); }
bool PointOnSegment(Point p, Point A, Point B){ return sgn((p - A) * (p - B)) <= 0 && sgn((p - A) ^ (p - B)) == 0; }
bool PointOnSegmentEndExcluded(Point p, Point A, Point B){ return sgn((p - A) * (p - B)) < 0 && sgn((p - A) ^ (p - B)) == 0; }
bool SegmentIntersectedEndExcluded(Point A1, Point A2, Point B1, Point B2){
	return (sgn((A1 - B1) ^ (B1 - B2)) * sgn((A2 - B1) ^ (B1 - B2)) < 0) && (sgn((B1 - A1) ^ (A1 - A2)) * sgn((B2 - A1) ^ (A1 - A2)) < 0);
}
bool SegmentIntersected(Point A1, Point A2, Point B1, Point B2){
	if(SegmentIntersectedEndExcluded(A1, A2, B1, B2))   return true;
	return PointOnSegment(A1, B1, B2) || PointOnSegment(A2, B1, B2) || PointOnSegment(B1, A1, A2) ||
		   PointOnSegment(B2, A1, A2) ? true : false;
}
bool LineSegmentIntersected(Line L, Point A, Point B){
	Point p_1 = L.p, p_2 = L.getPoint(1);
	return sgn(((p_2 - p_1) ^ (A - p_1))) * sgn(((p_2 - p_1) ^ (B - p_1))) <= 0;
}
bool LineSegmentIntersectedEndExcluded(Line L, Point A, Point B){
	Point p_1 = L.p, p_2 = L.getPoint(1);
	return sgn(((p_2 - p_1) ^ (A - p_1))) * sgn(((p_2 - p_1) ^ (B - p_1))) < 0;
}

//------------------------------------ Polygon ------------------------------------//
typedef vector<Point> Polygon;
double TriangleArea(Point A, Point B, Point C){ return ((B - A) ^ (C - A)) / 2; }
double PolygonArea(int n, Point p[]){
	double S = 0;
	for(int i = 2; i < n; i++)
		S += ((p[i] - p[1]) ^ (p[i+1] - p[1])) / 2;
	return S;
}
double PolygonArea(Polygon poly){
	double S = 0;
	for(int i = 1; i < poly.size() - 1; i++)
		S += ((poly[i] - poly[0]) ^ (poly[i+1] - poly[0])) / 2;
	return S;
}
int PointInPolygon(Point A, int n, Point p[]){ // 0: outside; 1: inside; -1: on edge
	int wn = 0; // winding number
	for(int i = 1; i <= n; i++){
		int nxt = i + 1 > n ? 1 : i + 1;
		if(PointOnSegment(A, p[i], p[nxt]))	return -1;
		int k = sgn((p[nxt] - p[i]) ^ (A - p[i]));
		int d1 = sgn(p[i].y - A.y);
		int d2 = sgn(p[nxt].y - A.y);
		if(k > 0 && d1 <= 0 && d2 > 0)	wn++;
		if(k < 0 && d2 <= 0 && d1 > 0)	wn--;
	}
	if(wn != 0)	return 1;
	return 0;
}
int PointInPolygon(Point A, Polygon poly){ // 0: outside; 1: inside; -1: on edge
	int wn = 0; // winding number
	int n = poly.size();
	for(int i = 0; i < n; i++){
		int nxt = (i + 1) % n;
		if(PointOnSegment(A, poly[i], poly[nxt]))	return -1;
		int k = sgn((poly[nxt] - poly[i]) ^ (A - poly[i]));
		int d1 = sgn(poly[i].y - A.y);
		int d2 = sgn(poly[nxt].y - A.y);
		if(k > 0 && d1 <= 0 && d2 > 0)	wn++;
		if(k < 0 && d2 <= 0 && d1 > 0)	wn--;
	}
	if(wn != 0)	return 1;
	return 0;
}
Polygon cutPolygon(Line l, Polygon poly){
	Polygon newpoly;
	int n = poly.size();
	for(int i = 0; i < n; i++){
		Point C = poly[i], D = poly[(i+1)%n];
		if(sgn(l.v ^ (C - l.p)) >= 0)	newpoly.push_back(C);
		if(sgn(l.v ^ (C - D)) != 0){
			Point q = GetLineIntersection(l, Line(C, C - D));
			if(PointOnSegmentEndExcluded(q, C, D))	newpoly.push_back(q);
		}
	}
	return newpoly;
}

//------------------------------------ Circle ------------------------------------//
struct Circle{
	Point p;
	double r;
	Circle() {}
	Circle(Point p, double r):p(p), r(r) {}
	Point getPoint(double alpha){
		return Point(p.x + cos(alpha) * r, p.y + sin(alpha) * r);
	}
};
void getLineCircleIntersection(Line L, Circle C, Point res[], int &resn){
	// resn is the number of intersecton points
	// intersection points are stored in res[]
	resn = 0;
	Point q = PointLineProjection(C.p, L);
	double d = DistancePointToPoint(C.p, q);
	if(cmp(d, C.r) > 0)   return;                           // separated
	else if(cmp(d, C.r) == 0){ res[++resn] = q; return; }   // tangent
	Vector u = L.v / Length(L.v);
	double dd = sqrt(C.r * C.r - d * d);
	res[++resn] = q - dd * u, res[++resn] = q + dd * u;     // intersected
}
void getCircleCircleIntersection(Circle C1, Circle C2, Point res[], int &resn){
	// resn is the number of intersection points (-1 if two circles coincide)
	// intersection points are stored in res[]
	resn = 0;
	double d = DistancePointToPoint(C1.p, C2.p);
	if(sgn(d) == 0) {
		if (cmp(C1.r, C2.r) == 0)   resn = -1;              // two circles are the same
		return;                                             // or concentric
	}
	if(cmp(C1.r + C2.r, d) < 0) return;                 // separated
	if(cmp(fabs(C1.r - C2.r), d) > 0)   return;         // contained
	double a = Angle(C2.p - C1.p);
	double da = acos((d * d + C1.r * C1.r - C2.r * C2.r) / (2 * d * C1.r));
	Point p1 = C1.getPoint(a - da), p2 = C1.getPoint(a + da);
	res[++resn] = p1;
	if(p1 != p2)    res[++resn] = p2;                       // tangent or intersected
}
void getTangents(Point p, Circle C, Line L[], int &lid){
	// lid is the number of tangent lines
	// tangent lines are stored in L[]
	lid = 0;
	Vector u = C.p - p;
	double d = Length(u);
	if(cmp(d, C.r) < 0)	return;
	else if(cmp(d, C.r) == 0)   L[++lid] = Line(p, Rotate(u, PI / 2));
	else if(cmp(d, C.r) > 0){
		double ang = asin(C.r / d);
		L[++lid] = Line(p, Rotate(u, -ang));
		L[++lid] = Line(p, Rotate(u, ang));
	}
}
void getTangents(Point p, Circle C, Point P[], int &pid){
	// pid is the number of tangent points
	// tangent points are stored in P[]
	pid = 0;
	Vector u = p - C.p;
	double d = Length(u);
	if(cmp(d, C.r) < 0)	return;
	else if(cmp(d, C.r) == 0)   P[++pid] = p;
	else if(cmp(d, C.r) > 0){
		double ang = acos(C.r / d);
		P[++pid] = C.p + Rotate(u, -ang) / d * C.r;
		P[++pid] = C.p + Rotate(u, ang) / d * C.r;
	}
}
void getTangents(Circle C1, Circle C2, Point c1[], Point c2[], int &resn){
	// resn is the number of tangent lines
	// c1[] and c2[] are relevant points on C1 and C2
	resn = 0;
	if(cmp(C1.r, C2.r) < 0)   swap(C1, C2), swap(c1, c2);
	double d = DistancePointToPoint(C1.p, C2.p);
	if(sgn(d) == 0 && cmp(C1.r, C2.r) == 0){ resn = -1; return; }  // two circles are the same
	if(cmp(C1.r - C2.r, d) > 0) return;                         // contained
	double base = Angle(C2.p - C1.p);
	if(cmp(C1.r - C2.r, d) == 0){                               // internally tangent
		c1[++resn] = C1.getPoint(base), c2[resn] = C2.getPoint(base);
		return;
	}
	double ang = acos((C1.r - C2.r) / d);
	c1[++resn] = C1.getPoint(base - ang), c2[resn] = C2.getPoint(base - ang);
	c1[++resn] = C1.getPoint(base + ang), c2[resn] = C2.getPoint(base + ang);
	if(cmp(C1.r + C2.r, d) == 0)                                // externally tangent
		c1[++resn] = C1.getPoint(base), c2[resn] = C2.getPoint(base + PI);
	else if(cmp(C1.r + C2.r, d) < 0){							// separated
		ang = acos((C1.r + C2.r) / d);
		c1[++resn] = C1.getPoint(base - ang), c2[resn] = C2.getPoint(base - ang + PI);
		c1[++resn] = C1.getPoint(base + ang), c2[resn] = C2.getPoint(base + ang + PI);
	}
}


int main(){
	;
}
