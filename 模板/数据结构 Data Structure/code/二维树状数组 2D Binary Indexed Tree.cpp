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
inline void add(int x, int y, int val, int c[][N]){
	for(int i = x; i <= n; i += lowbit(i))
		for(int j = y; j <= m; j += lowbit(j))
			c[i][j] += val;
}
inline int sum(int x, int y, int c[][N]){
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		for(int j = y; j; j -= lowbit(j))
			res += c[i][j];
	return res;
}

inline void Add(int x, int y, int val){
	add(x, y, val, c1), add(x, y, val * x, c2), add(x, y, val * y, c3), add(x, y, val * x * y, c4);
}
inline int Sum(int x, int y){
	return sum(x, y, c1) * (x+1) * (y+1) - sum(x, y, c2) * (y+1) - sum(x, y, c3) * (x+1) + sum(x, y, c4);
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