#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>

using namespace std;

const double eps = 1e-12;
const double PI = acos(-1);
const double INF = 1e16;
const int N = 100005;
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
Point GetLineIntersection(Line l1, Line l2){
	Vector u = l1.p - l2.p;
	double t = (l2.v ^ u) / (l1.v ^ l2.v);
	return l1.p + l1.v * t;
}

struct Circle{
	Point p;
	double r;
	Circle() {}
	Circle(Point p, double r):p(p), r(r) {}
	Point getPoint(double alpha){
		return Point(p.x + cos(alpha) * r, p.y + sin(alpha) * r);
	}
};

Point getO(Point a, Point b, Point c){
	Point mab = (a + b) / 2, mbc = (b + c) / 2;
	Vector vab = Normal(b - a), vbc = Normal(c - b);
	return GetLineIntersection(Line(mab, vab), Line(mbc, vbc));
}
Circle minEnclosingCircle(int n, Point p[]){
	random_shuffle(p+1, p+n+1);
	Point o = p[1]; double r = 0;
	for(int i = 1; i <= n; i++){
		if(cmp(Length(o - p[i]), r) <= 0)   continue;
		o = (p[i] + p[1]) / 2;
		r = Length(p[i] - p[1]) / 2;
		for(int j = 1; j < i; j++){
			if(cmp(Length(o - p[j]), r) <= 0)   continue;
			o = (p[j] + p[i]) / 2;
			r = Length(p[j] - p[i]) / 2;
			for(int k = 1; k < j; k++){
				if(cmp(Length(o - p[k]), r) <= 0)   continue;
				o = getO(p[i], p[j], p[k]);
				r = Length(p[i] - o);
			}
		}
	}
	return Circle(o, r);
}

int n;
Point p[N];

int main(){
	srand(time(NULL));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) p[i].read();
	Circle C = minEnclosingCircle(n, p);
	printf("%.10f\n%.10f %.10f\n", C.r, C.p.x, C.p.y);
	return 0;
}
