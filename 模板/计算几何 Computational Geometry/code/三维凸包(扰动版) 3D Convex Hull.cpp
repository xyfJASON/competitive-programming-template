#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1);
const int N = 2005;
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
double rand01(){ return rand() / (double)RAND_MAX; }
double randeps(){ return (rand01() - 0.5) * eps; }

struct Point3{
	double x, y, z;
	Point3(double x=0, double y=0, double z=0):x(x), y(y), z(z) {}
	void read(){ scanf("%lf%lf%lf", &x, &y, &z); }
};
typedef Point3 Vector3;
Vector3 operator + (Vector3 A, Vector3 B){ return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (Vector3 A, Vector3 B){ return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector3 operator * (double k, Vector3 A){ return Vector3(A.x * k, A.y * k, A.z * k); }
Vector3 operator * (Vector3 A, double k){ return k * A; }
Vector3 operator / (Vector3 A, double k){ return Vector3(A.x / k, A.y / k, A.z / k); }
bool operator == (Vector3 A, Vector3 B){ return cmp(A.x, B.x) == 0 && cmp(A.y, B.y) == 0 && cmp(A.z, B.z) == 0; }
bool operator != (Vector3 A, Vector3 B){ return !(A == B); }
double operator * (Vector3 A, Vector3 B){ return A.x * B.x + A.y * B.y + A.z * B.z; }
Vector3 operator ^ (Vector3 A, Vector3 B){ return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Length(Vector3 A){ return sqrt(A * A); }
double Angle(Vector3 A, Vector3 B){ return acos(A * B / Length(A) / Length(B)); }
double ParallelogramArea(Point3 A, Point3 B, Point3 C){ return Length((B - A) ^ (C - A)); }
double ParallelepipedVolume(Point3 A, Point3 B, Point3 C, Point3 D){ return ((B - A) ^ (C - A)) * (D - A); }
double TriangleArea(Point3 A, Point3 B, Point3 C){ return Length((B - A) ^ (C - A)) / 2; }
double TetrahedronVolume(Point3 A, Point3 B, Point3 C, Point3 D){ return ((B - A) ^ (C - A)) * (D - A) / 6.0; }
double DistancePointToPoint(Point3 A, Point3 B){ return Length(A-B); }
bool PointInTriangle(Point3 P, Point3 A, Point3 B, Point3 C){
	double area1 = TriangleArea(P, A, B);
	double area2 = TriangleArea(P, B, C);
	double area3 = TriangleArea(P, C, A);
	return sgn(area1 + area2 + area3 - TriangleArea(A, B, C)) == 0;
}

void addNoise(Point3 &P){ P.x += randeps(), P.y += randeps(), P.z += randeps(); }

struct Face{
	int v[3]; // the index of original points
	Vector3 Normal(Point3 P[]) const { return (P[v[1]] - P[v[0]]) ^ (P[v[2]] - P[v[0]]); }
	bool cansee(Point3 P[], int i){ return (P[i] - P[v[0]]) * Normal(P) > 0; }
};

bool vis[N][N];
vector<Face> ConvexHull3D(Point3 P[], int n){
	// P[] are points after adding noise and deleting multiple points
	memset(vis, 0, sizeof vis);
	vector<Face> cur;
	cur.push_back((Face){{1, 2, 3}});
	cur.push_back((Face){{3, 2, 1}});
	for(int i = 4; i <= n; i++){
		vector<Face> next;
		for(int j = 0; j < cur.size(); j++){ // add non-seen part into new convex hull
			Face &f = cur[j];
			bool res = f.cansee(P, i);
			if(!res)    next.push_back(f);
			for(int k = 0; k < 3; k++)  vis[f.v[k]][f.v[(k+1)%3]] = res;
		}
		for(int j = 0; j < cur.size(); j++){
			for(int k = 0; k < 3; k++){
				int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
				if(vis[a][b] != vis[b][a] && vis[a][b]) // segment ab is a boundary
					next.push_back((Face){{a, b, i}}); // add new faces into convex hull
			}
		}
		cur = next;
	}
	return cur;
}

int n, tn;
Point3 p[N], t[N];
double ans;

int main(){
	srand(20010130);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		p[i].read();
		bool same = false;
		for(int j = 1; j <= tn; j++){
			if(p[i] == t[j]){
				same = true;
				break;
			}
		}
		if(!same)   t[++tn] = p[i];
	}
	for(int i = 1; i <= tn; i++)    addNoise(t[i]);
	vector<Face> res = ConvexHull3D(t, tn);
	for(int i = 0; i < res.size(); i++)
		ans += Length( (t[res[i].v[1]] - t[res[i].v[0]]) ^ (t[res[i].v[2]] - t[res[i].v[0]]) ) / 2;
	printf("%.3f\n", ans);
	return 0;
}
