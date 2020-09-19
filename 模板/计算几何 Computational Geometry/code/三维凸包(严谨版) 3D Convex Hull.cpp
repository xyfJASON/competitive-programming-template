#include<algorithm>
#include<cstring>
#include<cstdio>
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

struct ConvexHull3D{
	struct Face{
		int v[3]; // the index of original points
		bool inres; // is this face on the convex hull
		Vector3 Normal(Point3 P[]) const { return (P[v[1]] - P[v[0]]) ^ (P[v[2]] - P[v[0]]); }
		bool cansee(Point3 P[], int i){ return (P[i] - P[v[0]]) * Normal(P) > 0; }
	};

	int n; // number of original points
	Point3 P[N]; // original points
	Face F[N<<3]; int fid; // store faces on convex hull
	int belong[N][N]; // belong[i][j] store which face is vector (ij) on

	void dfs(int i, int a, int b){
		int f = belong[a][b];
		if(F[f].inres == false)  return;
		if(F[f].cansee(P, i)){
			F[f].inres = false;
			dfs(i, F[f].v[1], F[f].v[0]);
			dfs(i, F[f].v[2], F[f].v[1]);
			dfs(i, F[f].v[0], F[f].v[2]);
		}
		else{
			Face tmp;
			tmp.v[0] = b, tmp.v[1] = a, tmp.v[2] = i;
			tmp.inres = true;
			belong[b][a] = belong[a][i] = belong[i][b] = ++fid;
			F[fid] = tmp;
		}
	}
	void deal(int i, int j){
		F[j].inres = false;
		dfs(i, F[j].v[1], F[j].v[0]);
		dfs(i, F[j].v[2], F[j].v[1]);
		dfs(i, F[j].v[0], F[j].v[2]);
	}
	void solve(){
		if(n < 4)   return;
		fid = 0;

		//---------------------- get P[1],P[2],P[3],P[4] right ----------------------//
		bool flag = false;
		for(int i = 2; i <= n; i++){
			if(P[i] != P[1]){
				swap(P[i], P[2]);
				flag = true;
				break;
			}
		}
		if(!flag)   return;
		flag = false;
		for(int i = 3; i <= n; i++){
			if(sgn(Length((P[2]-P[1]) ^ (P[i]-P[1]))) != 0){
				swap(P[i], P[3]);
				flag = true;
				break;
			}
		}
		if(!flag)   return;
		flag = false;
		for(int i = 4; i <= n; i++){
			if(sgn(((P[3]-P[1]) ^ (P[2]-P[1])) * (P[i]-P[1])) != 0){
				swap(P[i], P[4]);
				flag = true;
				break;
			}
		}
		if(!flag)   return;

		//------------------------ store P[1],P[2],P[3],P[4] ------------------------//
		Face tmp;
		for(int i = 1; i <= 4; i++){
			tmp.v[0] = i % 4 + 1;
			tmp.v[1] = (i + 1) % 4 + 1;
			tmp.v[2] = (i + 2) % 4 + 1;
			tmp.inres = true;
			if(tmp.cansee(P, i))    swap(tmp.v[1], tmp.v[2]);
			belong[tmp.v[0]][tmp.v[1]] = belong[tmp.v[1]][tmp.v[2]] = belong[tmp.v[2]][tmp.v[0]] = ++fid;
			F[fid] = tmp;
		}

		//---------------------------- add in new points ----------------------------//
		for(int i = 5; i <= n; i++){
			for(int j = 1; j <= fid; j++){
				if(F[j].inres == true && F[j].cansee(P, i)){
					deal(i, j);
					break;
				}
			}
		}

		int tid = fid; fid = 0;
		for(int i = 1; i <= tid; i++) if(F[i].inres) F[++fid] = F[i];
	}


	inline double SurfaceArea(){
		double res = 0;
		for(int i = 1; i <= fid; i++)
			res += TriangleArea(P[F[i].v[0]], P[F[i].v[1]], P[F[i].v[2]]);
		return res;
	}
	inline double Volume(){
		double res = 0;
		Point3 O(0, 0, 0);
		for(int i = 1; i <= fid; i++)
			res += TetrahedronVolume(O, P[F[i].v[0]], P[F[i].v[1]], P[F[i].v[2]]);
		return res;
	}
	inline int cntTriangleFaces(){
		return fid;
	}
	bool sameFace(int i, int j){
		return sgn(TetrahedronVolume(P[F[j].v[0]], P[F[i].v[0]], P[F[i].v[1]], P[F[i].v[2]])) == 0
			&& sgn(TetrahedronVolume(P[F[j].v[1]], P[F[i].v[0]], P[F[i].v[1]], P[F[i].v[2]])) == 0
			&& sgn(TetrahedronVolume(P[F[j].v[2]], P[F[i].v[0]], P[F[i].v[1]], P[F[i].v[2]])) == 0;
	}
	inline int cntPolygonFaces(){
		int res = 0;
		for(int i = 1; i <= fid; i++){
			bool same = false;
			for(int j = 1; j < i; j++){
				if(sameFace(i, j)){
					same = true;
					break;
				}
			}
			if(!same)   res++;
		}
		return res;
	}
};

ConvexHull3D ch;

int main(){
	scanf("%d", &ch.n);
	for(int i = 1; i <= ch.n; i++)  ch.P[i].read();
	ch.solve();
	printf("%.3f\n", ch.SurfaceArea());
	return 0;
}
