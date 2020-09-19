#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

const int N = 20005;
const int INF = 1e9;

int n;
vector<int> edge[N];

int rt, size[N], mxson[N]; // rt is the id of centroid
void getCentroid(int x, int f){
	mxson[x] = 0, size[x] = 1;
	for(auto &to : edge[x]){
		if(to == f)	continue;
		getCentroid(to, x);
		size[x] += size[to];
		mxson[x] = max(mxson[x], size[to]);
	}
	mxson[x] = max(mxson[x], n - size[x]);
	if(rt == 0 || mxson[rt] > mxson[x])	rt = x;
}

inline void init(){
	rt = 0;
	for(int i = 1; i <= n; i++){
		edge[i].clear();
		size[i] = 0, mxson[i] = 0;
	}
}

int main(){
	int T; for(scanf("%d", &T); T; T--){
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++){
			int u, v; scanf("%d%d", &u, &v);
			edge[u].push_back(v), edge[v].push_back(u);
		}
		getCentroid(1, 0);
		printf("%d %d\n", rt, mxson[rt]);
	}
	return 0;
}