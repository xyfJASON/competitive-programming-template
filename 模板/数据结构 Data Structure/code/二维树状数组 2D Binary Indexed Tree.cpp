#include<algorithm>
#include<cstdio>

using namespace std;

template<typename T>void read(T&x){x=0;int fl=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')
fl=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}x*=fl;}
template<typename T,typename...Args>inline void read(T&t,Args&...args){read(t);read(args...);}

const int N = 2055;

int n, m;
char s[10];

int c1[N][N], c2[N][N], c3[N][N], c4[N][N];
inline int lowbit(int x){ return x & -x; }
inline void addy(int x, int y, int val, int c[][N]){ while(y <= m){ c[x][y] += val; y += lowbit(y); } }
inline void addx(int x, int y, int val, int c[][N]){ while(x <= n){ addy(x, y, val, c); x += lowbit(x); } }
inline int sumy(int x, int y, int c[][N]){ int res = 0; while(y){ res += c[x][y]; y -= lowbit(y); } return res; }
inline int sumx(int x, int y, int c[][N]){ int res = 0; while(x){ res += sumy(x, y, c); x -= lowbit(x); } return res; }

inline void Add(int x, int y, int val){
	addx(x, y, val, c1), addx(x, y, val * x, c2), addx(x, y, val * y, c3), addx(x, y, val * x * y, c4);
}
inline int Sum(int x, int y){
	return sumx(x, y, c1) * (x+1) * (y+1) - sumx(x, y, c2) * (y+1) - sumx(x, y, c3) * (x+1) + sumx(x, y, c4);
}

int main(){
	scanf("X %d%d", &n, &m);
	while(scanf("%s", s) != EOF){
		int qa, qb, qc, qd, qx;
		read(qa, qb, qc, qd);
		if(s[0] == 'L'){
			read(qx);
			Add(qa, qb, qx), Add(qa, qd+1, -qx), Add(qc+1, qb, -qx), Add(qc+1, qd+1, qx);
		}
		else    printf("%d\n", Sum(qc, qd) - Sum(qa-1, qd) - Sum(qc, qb-1) + Sum(qa-1, qb-1));
	}
	return 0;
}
