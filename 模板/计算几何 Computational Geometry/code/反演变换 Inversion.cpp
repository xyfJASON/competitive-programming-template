#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1);
const double INF = 1e10;
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
Vector Normal(Vector A){ // get the normal vector of A
	double L = Length(A);
	return Vector{-A.y/L, A.x/L};
}
struct Line{
	Point p;
	Vector v;
	double ang;
	Line() {}
	Line(Point p, Vector v):p(p), v(v){ ang = atan2(v.y, v.x); }
	Point getPoint(double t){ return p + v * t; }
	bool operator < (const Line &L) const{ return ang < L.ang; }
};
Point PointLineProjection(Point p, Line l){ return l.p + l.v * ((l.v * (p - l.p)) / (l.v * l.v)); }
struct Circle{
	Point p;
	double r;
	Circle() {}
	Circle(Point p, double r):p(p), r(r) {}
	Point getPoint(double alpha){
		return Point(p.x + cos(alpha) * r, p.y + sin(alpha) * r);
	}
};
void getTangents(Circle C1, Circle C2, Point c1[], Point c2[], int &resn){
	// resn is the number of tangent lines
	// c1[] and c2[] are relevant points on C1 and C2
	resn = 0;
	if(cmp(C1.r, C2.r) < 0)   swap(C1, C2), swap(c1, c2);
	double d = Length(C1.p - C2.p);
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

int T, id, ansid;
Circle C1, C2, ans[10], t1, t2;
Point p, c1[10], c2[10];

Circle getInversionC2C(Point O, double R, Circle A){
	double OA = Length(A.p - O);
	double rB = R * R / 2 * (1 / (OA - A.r) - 1 / (OA + A.r));
	double xB = O.x + rB / A.r * (A.p.x - O.x);
	double yB = O.y + rB / A.r * (A.p.y - O.y);
	return Circle(Point(xB, yB), rB);
}
Circle getInversionL2C(Point O, double R, Line L){
	Point P = PointLineProjection(O, L);
	double d = Length(P - O);
	double r = R * R / d / 2;
	Vector v = (P - O) / Length(P - O) * r;
	return Circle(O + v, r);
}
Line getInversionC2L(Point O, double R, Circle A){
	Point P = (A.p - O) / Length(A.p - O) * R * R / A.r / 2;
	Vector v = Normal(A.p - O);
	return Line(P, v);
}

int main(){
	scanf("%d", &T);
	while(T--){
		id = ansid = 0;
		C1.p.read(); scanf("%lf", &C1.r);
		C2.p.read(); scanf("%lf", &C2.r);
		p.read();
		t1 = getInversionC2C(p, 1, C1);
		t2 = getInversionC2C(p, 1, C2);
		getTangents(t1, t2, c1, c2, id);
		for(int i = 1; i <= id; i++){
			Circle C = getInversionL2C(p, 1, Line(c1[i], c2[i] - c1[i]));
			if(cmp(Length(C.p - C1.p), C.r + C1.r) == 0 && cmp(Length(C.p - C2.p), C.r + C2.r) == 0)
				ans[++ansid] = C;
		}
		printf("%d\n", ansid);
		for(int i = 1; i <= ansid; i++)
			printf("%.8f %.8f %.8f\n", ans[i].p.x, ans[i].p.y, ans[i].r);
	}
	return 0;
}
