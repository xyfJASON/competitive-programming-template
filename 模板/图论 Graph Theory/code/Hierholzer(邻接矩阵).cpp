#include<cstdio>
#include<stack>

using namespace std;

template<typename T>void read(T&x){x=0;int fl=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')
fl=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}x*=fl;}
template<typename T,typename...Args>inline void read(T&t,Args&...args){read(t);read(args...);}

const int N = 510;

int m, n, u, v, st = N, g[N][N], deg[N];

stack<int> sta;
void dfs(int x){
	for(int j = 1; j <= n; j++){
		if(g[x][j]){
			g[x][j]--;
			g[j][x]--;
			dfs(j);
		}
	}
	sta.push(x);
}

int main(){
	n = 500;
	read(m);
	for(int i = 1; i <= m; i++){
		read(u, v);
		g[u][v]++;
		g[v][u]++;
		deg[u]++;
		deg[v]++;
		st = min(st, u);
		st = min(st, v);
	}
	for(int i = 1; i <= n; i++){
		if(deg[i] % 2 == 1){
			st = i;
			break;
		}
	}
	dfs(st);
	while(!sta.empty()){
		printf("%d\n", sta.top());
		sta.pop();
	}
	return 0;
}
